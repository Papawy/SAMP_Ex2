#include "gtautils.hpp"

#include <exception>
#include <sstream>

#include <Windows.h>
#include <WinBase.h>

namespace SAMP_Ex2
{
	std::string GTAUtils::GetGTADir()
	{
		HKEY key;
		if(RegOpenKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\SAMP\\"), &key) != ERROR_SUCCESS)
		{
			throw std::exception("Could not open SAMP registry key !");
		}

		char gtaDir[512];
		DWORD gtaDirLength = 512;
		RegQueryValueEx(key, TEXT("gta_sa_exe"), NULL, NULL, (LPBYTE)&gtaDir, &gtaDirLength);
		RegCloseKey(key);
		return std::string(gtaDir);
	}

	void GTAUtils::SetGTADir(std::string dir)
	{
		HKEY key;
		if(RegOpenKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\SAMP\\"), &key) != ERROR_SUCCESS)
		{
			throw std::exception("Could not open SAMP registry key !");
		}

		if(RegSetValueEx(key, TEXT("gta_sa_exe"), 0, REG_SZ, (LPBYTE)dir.c_str(), strlen(dir.c_str())*sizeof(char)) != ERROR_SUCCESS)
		{
			RegCloseKey(key);
			throw std::exception("Could not write in SAMP registry key !");
		}

		RegCloseKey(key);
	}

	bool GTAUtils::LaunchGTAInjected(QHostAddress ip, quint16 port, std::string nickname, std::string password, bool debug, std::string sampdll)
	{
		std::string gtaPath = "M:\\Games\\Rockstar Games\\GTA San Andreas"; /* ConfigFile.GetUserConfig("gtapath") + */
		std::string gtaExeLocation = gtaPath + "\\gta_sa.exe";

		std::string gtaDir;
		try
		{
			gtaDir = GetGTADir();
		}
		catch(std::exception e)
		{
			return false;
		}

		/* if(ConfigFile.GetUserConfig("gtapath").length() == 0)
		 *		gtaExeLocation = gtaDir + "\\gta_sa.exe";
		 */

		std::string gtaExeArgs;

		PROCESS_INFORMATION ProcessInfo;
		LPSTARTUPINFOA StartupInfo;



		std::stringstream ss;
		if (debug == false)
			ss << "-c -h " << ip.toString().toStdString() << " -p " << port << " -n " << nickname;
		else
			ss << "-d -h " << ip.toString().toStdString() << " -p " << port << " -n " << nickname;

		if(password.length() != 0)
			ss << " -z " << password;

		gtaExeArgs = ss.str();

		LPSTR cString = strdup(gtaExeArgs.c_str());
		if(CreateProcessA(gtaExeLocation.c_str(), cString, NULL, NULL, false, DETACHED_PROCESS | CREATE_SUSPENDED, NULL, gtaDir.c_str(), StartupInfo, &ProcessInfo))
		{
			SIZE_T * bWritten;
			LPDWORD hThread;

			ss.str("");
			ss.clear();
			ss << gtaDir << sampdll;
			std::string DLLName = ss.str();

			HMODULE hKernel = LoadLibraryA("kernel32.dll");
			FARPROC LoadLib = GetProcAddress(hKernel, "LoadLibraryA");
			FreeLibrary(hKernel);

			if(LoadLib == NULL)
				return false;

			HANDLE ProcHandle = ProcessInfo.hProcess;
			if(ProcHandle == NULL)
				return false;

			LPVOID arg = VirtualAllocEx(ProcHandle, NULL, DLLName.length(), 0x1000 | 0x2000, 0x04);
			if(arg == NULL)
				return false;

			bool WPM = WriteProcessMemory(ProcHandle, arg, DLLName.c_str(), DLLName.length(), bWritten);
			if(WPM == NULL)
				return false;

			HANDLE hThr = CreateRemoteThread(ProcHandle, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLib, arg, CREATE_SUSPENDED, hThread);
			if(hThr == NULL)
				return false;

			ResumeThread(hThr);
			WaitForSingleObject(hThr, (int)INFINITY);
			VirtualFreeEx(ProcessInfo.hProcess, arg, NULL, MEM_RELEASE);
			ResumeThread(ProcessInfo.hThread);
			CloseHandle(ProcessInfo.hProcess);
		}
		return true;
	}
}
