#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QLayout>

namespace Ui {
class MainWindow;
}

namespace SAMP_Ex2
{

	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private:
		Ui::MainWindow *ui;

		QCheckBox* m_chkBoxDefaultNick;
		QLabel* m_lblDefaultNick;
		QLineEdit* m_lnDefaultNick;
	};
}


#endif // MAINWINDOW_H
