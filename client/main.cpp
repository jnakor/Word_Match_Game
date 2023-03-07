#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>
#include "Risker.h"
#include "MD_FIVE.h"
#include<iostream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiApplication1 *w = new QtGuiApplication1();
	w->setAttribute(Qt::WA_DeleteOnClose, true);
	w->show();
	return a.exec();
}
