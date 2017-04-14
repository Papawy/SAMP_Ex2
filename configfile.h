#ifndef CONFIGFILE_H
#define CONFIGFILE_H


#include <QString>
#include <QtXml>
#include <QWidget>
#include <QtGui>
#include <QMessageBox>
#include <QDomDocument>

namespace SAMP_Ex2
{
	class ConfigFile
	{
	public:
		ConfigFile();
		_ConfigFile();
		static bool Load(QString filePath);
		static QString GetConfValue(QString conftype, QString confname);

	protected:
		bool m_loaded;
		QString m_filePath;
	};
}


#endif // CONFIGFILE_H
