#ifndef UTILS_HPP
#define UTILS_HPP

#include <QString>

#include <QUdpSocket>

namespace SAMP_Ex2
{
	namespace GTAUtils
	{
		QString GetGTADir();
		void SetGTADir(QString dir);

		bool ConnectClientTo(); // TODO

		bool LaunchGTAInjected(QHostAddress ip, quint16 port, QString nickname, QString password = "", bool debug = false, QString sampdll = "\\samp.dll");
	}
}


#endif // UTILS_HPP
