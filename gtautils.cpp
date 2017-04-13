#include "gtautils.hpp"

#include <exception>

#include <Windows.h>

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
		RegQueryValueEx(key, "gta_sa_exe", NULL, REG_SZ, (LPBYTE)&gtaDir, &gtaDirLength);
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

	bool GTAUtils::LaunchGTAInjected(QHostAddress ip, quint16 port, std::string nickname, std::string password, boo debug, string sampdll)
	{
		std::string gtaExeLocation = /* ConfigFile.GetUserConfig("gtapath") + */ "\\gta_sa.exe";
	}
}
