#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gtautils.hpp"

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

	MainWindow::~MainWindow()
	{
		delete ui;
	}

}

