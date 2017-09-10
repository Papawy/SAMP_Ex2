#ifndef CSERVERLIST_HPP
#define CSERVERLIST_HPP

#include <QUdpSocket>
#include <QHash>
#include <QNetworkDatagram>

#include "cserver.hpp"

namespace SAMP_Ex2
{
	class CServer;

	/*struct ServerAddress
	{
		QHostAddress address;
		int port;
	};*/

	class CServerList : public QObject
	{
		Q_OBJECT

	public:
		CServerList();
		~CServerList();

	public slots:
		void readPendingDatagrams();

	private:
		QUdpSocket* m_socket;
		QHash<QPair<QHostAddress,int>, CServer*> m_servers;
	};
}

#endif // CSERVERLIST_HPP
