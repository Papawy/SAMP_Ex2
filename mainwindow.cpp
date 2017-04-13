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
	}

	MainWindow::~MainWindow()
	{
		delete ui;
	}

}

