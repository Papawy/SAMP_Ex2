#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

#include "../headers/gtautils.hpp"

namespace SAMP_Ex2
{
	MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow)
	{
		ui->setupUi(this);

		m_lblDefaultNick = new QLabel(this);
		m_lblDefaultNick->setText("Nickname : ");

		m_lnDefaultNick = new QLineEdit(this);
		m_lnDefaultNick->setMaxLength(20);
		m_lnDefaultNick->setMaximumWidth(150);

		m_chkBoxDefaultNick = new QCheckBox(this);
		m_chkBoxDefaultNick->setText("Use it by default");

		QWidget* toolBarSpacer = new QWidget(this);
		toolBarSpacer->setMinimumWidth(10);

		ui->mainToolBar->addWidget(m_lblDefaultNick);
		ui->mainToolBar->addWidget(m_lnDefaultNick);
		ui->mainToolBar->addWidget(toolBarSpacer);
		ui->mainToolBar->addWidget(m_chkBoxDefaultNick);
	}
	
	void MainWindow::GetFavListServers()
	{
	    QFile file("favlist.xml");
	    file.open(QIODevice::ReadOnly);
	    QXmlStreamReader stream(&file);

	    QString Ip;
	    QString Name;
	    QString Pass;

	    try
	    {
		while(stream.readNext() && !stream.isEndDocument())
		{
		    if(stream.name() == "server")
		    {
			qDebug() << "server found";

			while(stream.readNext() && !stream.isEndElement())
			{
			    if(stream.name() == "ip")
			    {
				Ip = stream.readElementText();
				    
				    /* Configure le avec ta liste */
				//ui->listWidget->addItem("Ip: "+ Ip); 
			    }
			    if(stream.name() == "nickname")
			    {
				Name = stream.readElementText();
			    }
			    if(stream.name() == "password")
			    {
				Pass = stream.readElementText();
			    }
			}
			qDebug() << "IP: " + Ip;
		    }
		}
	    }
	    catch(QException &ex)
	    {
		qDebug() << "Bug In try";
	    }
	    stream.clear();
	    file.close();
	}
	
	MainWindow::~MainWindow()
	{
		delete ui;
	}

}

