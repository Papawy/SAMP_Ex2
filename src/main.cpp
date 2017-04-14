#include "../headers/mainwindow.h"
#include <QApplication>

#include "../headers/gtautils.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SAMP_Ex2::MainWindow w;
	w.show();

	return a.exec();
}
