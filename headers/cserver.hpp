#ifndef SERVER_HPP
#define SERVER_HPP

#include <QNetworkDatagram>
#include <QMap>

namespace SAMP_Ex2
{
	class CServer : public QObject
	{
		Q_OBJECT

	public:
		CServer();

	public slots:
		void processDatagram(QNetworkDatagram datagram);
	};
}

#endif // SERVER_HPP
