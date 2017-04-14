#include "../headers/gtautils.hpp"

#include <exception>
#include <sstream>
#include <iostream>

#include <Windows.h>
#include <WinBase.h>

#include <QSettings>
#include <QDir>

#include "../headers/configfile.h"

namespace SAMP_Ex2
{
	QString GTAUtils::GetGTADir()
	{
		/*HKEY key;
		if(RegOpenKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\SAMP\\"), &key) != ERROR_SUCCESS)
		{
			throw std::exception("Could not open SAMP registry key !");
		}

		char gtaExeDir[512];
		DWORD gtaExeDirLength = 512;
		RegQueryValueEx(key, TEXT("gta_sa_exe"), NULL, NULL, (LPBYTE)&gtaExeDir, &gtaExeDirLength);
		RegCloseKey(key);
		QDir gtaDir = QDir(gtaExeDir);
		QString gtaDirStr = gtaDir.absolutePath();
		std::cout << gtaExeDir;*/

		QString gtaDirStr;

		try
		{
			QSettings sampKey("HKEY_CURRENT_USER\\SOFTWARE\\SAMP", QSettings::NativeFormat);
			gtaDirStr = sampKey.value("gta_sa_exe").toString();
		}
		catch(std::exception e)
		{
			gtaDirStr = "";
		}

		return QDir::toNativeSeparators(QFileInfo(gtaDirStr).absoluteDir().absolutePath());
	}

	void GTAUtils::SetGTADir(QString dir)
	{
		HKEY key;
		if(RegOpenKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\SAMP\\"), &key) != ERROR_SUCCESS)
		{
			throw std::exception("Could not open SAMP registry key !");
		}

		if(RegSetValueEx(key, TEXT("gta_sa_exe"), 0, REG_SZ, (LPBYTE)dir.toStdString().c_str(), strlen(dir.toStdString().c_str())*sizeof(char)) != ERROR_SUCCESS)
		{
			RegCloseKey(key);
			throw std::exception("Could not write in SAMP registry key !");
		}

		RegCloseKey(key);
	}

	bool GTAUtils::LaunchGTAInjected(QHostAddress ip, quint16 port, QString nickname, QString password, bool debug, QString sampdll)
	{
		QString gtaPath = ConfigFile::GetConfValue("user", "gtapath");
		QString gtaExeLocation = gtaPath + "\\gta_sa.exe";

		QString gtaDir;
		try
		{
			gtaDir = GetGTADir();
		}
		catch(std::exception e)
		{
			return false;
		}

		if(gtaPath.length() == 0)
			gtaExeLocation = gtaDir + "\\gta_sa.exe";

		QString gtaExeArgs /*= "\"" + gtaExeLocation + "\" "*/;

		PROCESS_INFORMATION ProcessInfo;
		ZeroMemory( &ProcessInfo, sizeof(ProcessInfo) );

		STARTUPINFO StartupInfo;
		ZeroMemory( &StartupInfo, sizeof(StartupInfo) );
		StartupInfo.cb = sizeof(StartupInfo);

		if (debug == false)
			gtaExeArgs += "-c -h " + ip.toString() + " -p " + port + " -n " + nickname;
		else
			gtaExeArgs += "-d -h " + ip.toString() + " -p " + port + " -n " + nickname;

		if(password.length() != 0)
			gtaExeArgs += " -z " + password;

		if(CreateProcess((LPCWSTR)gtaExeLocation.utf16(), (LPTSTR)gtaExeArgs.utf16(), NULL, NULL, false, DETACHED_PROCESS | CREATE_SUSPENDED, NULL, (LPCTSTR)gtaDir.utf16(), &StartupInfo, &ProcessInfo))
		{
			QString DLLName = gtaDir + sampdll;

			HMODULE hKernel = GetModuleHandle(L"kernel32.dll");
			LPVOID LoadLib = GetProcAddress(hKernel, "LoadLibraryA");

			if(LoadLib == NULL)
				return false;

			if(ProcessInfo.hProcess == NULL)
				return false;

			char * dllName = strdup(DLLName.toStdString().c_str());
			LPVOID arg = VirtualAllocEx(ProcessInfo.hProcess, NULL, strlen(dllName), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			if(arg == NULL)
				return false;

			SIZE_T bWritten;
			bool WPM = WriteProcessMemory(ProcessInfo.hProcess, arg, dllName, strlen(dllName), &bWritten);
			if(WPM == NULL)
				return false;


			HANDLE hThr = CreateRemoteThread(ProcessInfo.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLib, arg, CREATE_SUSPENDED, NULL);
			if(hThr == NULL)
				return false;


			ResumeThread(hThr);
			WaitForSingleObject(hThr, INFINITE);
			VirtualFreeEx(ProcessInfo.hProcess, arg, NULL, MEM_RELEASE);
			ResumeThread(ProcessInfo.hThread);
			CloseHandle(ProcessInfo.hProcess);
		}
		return true;
	}
}
