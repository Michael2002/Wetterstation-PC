#ifndef WETTERSTATION_H
#define WETTERSTATION_H

#include <QtWidgets/QMainWindow>
#include "ui_wetterstation.h"
#include "usbcom.h"

class QTimer;

// DEBUG OUTPUT
#define useDEBUG

typedef struct{
	float _temperatur;
    int _luftdruck;
    int _luftfeuchte;
    float _taupunkt;
    int _windgeschwindigkeit;
    char _windrichtung[3];
} Data;

class Wetterstation : public QMainWindow, protected usbCom
{
	Q_OBJECT

public:
	Wetterstation(QWidget *parent = 0);
	~Wetterstation();

	bool initUsb();
	bool writeUsbASYNC();
	bool readUsbASYNC();
	bool extractData(char buffer[]);

signals:
	void dataOut(  Data );

protected:
	QTimer *_timer;
	Data _data;
	
	protected slots:
		void slotTimer( void );

private:
	Ui::WetterstationClass ui;
};

#endif // WETTERSTATION_H
