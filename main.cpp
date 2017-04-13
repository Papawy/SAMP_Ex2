#include "mainwindow.h"
#include <QApplication>

#include "gtautils.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SAMP_Ex2::MainWindow w;
	w.show();

	SAMP_Ex2::GTAUtils::LaunchGTAInjected(QHostAddress("127.0.0.1"), 7777, "Megalo_Sucre");

	return a.exec();
}
