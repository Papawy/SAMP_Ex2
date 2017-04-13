#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

#include <QUdpSocket>

namespace SAMP_Ex2
{
	namespace GTAUtils
	{
		std::string GetGTADir();
		void SetGTADir(std::string dir);

		bool ConnectClientTo(); // TODO

		bool LaunchGTAInjected(QHostAddress ip, quint16 port, std::string nickname, std::string password = "", bool debug = false, std::string sampdll = "\\samp.dll");
	}
}


#endif // UTILS_HPP
