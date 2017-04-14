#include "../headers/configfile.h"

namespace SAMP_Ex2
{
	bool ConfigFile::m_loaded = false;
	QString ConfigFile::m_filePath = "";

	ConfigFile::ConfigFile()
	{

	}

	ConfigFile::~ConfigFile()
	{

	}

	bool ConfigFile::Load(QString filePath)
	{
		m_filePath = filePath;
		m_loaded = true;
		return true;
	}

	QString ConfigFile::GetConfValue(QString conftype, QString confname)
	{
		QString ret = "";
		QFile file("config.xml");
		if (file.open(QFile::ReadOnly | QFile::Text))
		{
			QXmlStreamReader reader;
			reader.setDevice(&file); //(file);
			reader.readNext();
			while (!reader.atEnd())
			{
				if (reader.name() == "configuration" && reader.isStartElement())
				{
					reader.readNext();
					while (!reader.atEnd())
					{
						if (reader.name() == conftype && reader.isStartElement())
						{
							reader.readNext();
							while (!reader.atEnd())
							{
								if (reader.name() == confname && reader.isStartElement())
									return reader.readElementText();
								reader.readNext();
							}
						}
						reader.readNext();
					}
				}
				reader.readNext();
			}
		}
		else
			qDebug() << qPrintable(file.errorString());
		return ret;
	}
}
