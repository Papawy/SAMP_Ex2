#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QString>
#include <QtXml>
#include <QWidget>
#include <QtGui>
#include <QMessageBox>
#include <QDomDocument>
#include <QFile>

namespace SAMP_Ex2
{
	class ConfigFile
	{
	public:
		ConfigFile();
		~ConfigFile();
		static bool Load(QString filePath);
		static QString GetConfValue(QString conftype, QString confname);

	protected:
		static bool m_loaded;
		static QString m_filePath;
	};
}


#endif // CONFIGFILE_H
