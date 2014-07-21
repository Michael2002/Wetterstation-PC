#include "wetterstation.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Wetterstation w;
	w.show();
	return a.exec();
}
