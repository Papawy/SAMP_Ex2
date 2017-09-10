#include "../headers/cconfigfile.h"

namespace SAMP_Ex2
{
	bool CConfigFile::m_loaded = false;
	QString CConfigFile::m_filePath = "";

	CConfigFile::CConfigFile()
	{

	}

	CConfigFile::~CConfigFile()
	{

	}

	bool CConfigFile::Load(QString filePath)
	{
		m_filePath = filePath;
		m_loaded = true;
		return true;
	}

	QString CConfigFile::GetConfValue(QString conftype, QString confname)
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
