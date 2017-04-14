#ifndef CONFIGFILE_H
#define CONFIGFILE_H


#include <QString>
#include <QtXml>
#include <QWidget>
#include <QtGui>
#include <QMessageBox>
#include <QDomDocument>


class ConfigFile
{
public:
    ConfigFile();
    _ConfigFile();
    QString GetConfValue(QString conftype, QString confname);
};

#endif // CONFIGFILE_H
