#include "../headers/cserverlist.hpp"

namespace SAMP_Ex2
{
	CServerList::CServerList()
	{
		m_socket = new QUdpSocket(this);
		m_socket->bind();

		m_servers = QHash<QPair<QHostAddress,int>, CServer*>();

		connect(m_socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
	}

	CServerList::~CServerList()
	{

	}

	void CServerList::readPendingDatagrams()
	{
		while(m_socket->hasPendingDatagrams())
		{
			/*QNetworkDatagram datagram = m_socket->receiveDatagram();
			QPair<QHostAddress,int> servAddr;
			servAddr.first = datagram.senderAddress();
			servAddr.second = datagram.senderPort();
			auto it = m_servers.find(servAddr);
			if(it != m_servers.end())
				it.value()->processDatagram(datagram);
			else
			*/
		}
	}
}
