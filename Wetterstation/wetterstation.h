#ifndef WETTERSTATION_H
#define WETTERSTATION_H

#include <QtWidgets/QMainWindow>
#include "ui_wetterstation.h"

class Wetterstation : public QMainWindow
{
	Q_OBJECT

public:
	Wetterstation(QWidget *parent = 0);
	~Wetterstation();

private:
	Ui::WetterstationClass ui;
};

#endif // WETTERSTATION_H
