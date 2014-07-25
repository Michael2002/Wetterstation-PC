#include <QtWidgets/QApplication>
#include <QtCore/QTimer>
#include <QDateTime>
#include "wetterstation.h"

Wetterstation::Wetterstation(QWidget *parent)
	: QMainWindow(parent), usbCom()
{
	ui.setupUi(this);

	_timer = new QTimer( this );
	connect( _timer, SIGNAL( timeout() ), this, SLOT( slotTimer() ) );
	_timer->setInterval( 2000  );
	_timer->start();
}

Wetterstation::~Wetterstation()
{

}

void Wetterstation::slotTimer( void )
{	
	if (writeUsbASYNC() && readUsbASYNC())
		emit dataOut( _data );
}

bool Wetterstation::initUsb()
{

	if (usbCom::open_dev() && usbCom::set_config() && usbCom::claim_interface())
	{
		return true;
	}
	
	return false;
}

bool Wetterstation::writeUsbASYNC()
{
	int ret;
	char buffer[BUF_SIZE];

	memset(buffer,0,sizeof(buffer));

	QDateTime dateTime = QDateTime::currentDateTime();
	QString dateTimeString = dateTime.toString(Qt::ISODate);
	
	for(int i=0; (i<sizeof(buffer)-1) && (i<dateTimeString.length()); i++)
	{
		buffer[i] = dateTimeString.at(i).toLatin1();
	}
	buffer[sizeof(buffer)-1] = '\0';

	// Running an async write test
	ret = transfer_bulk_async(EP_OUT, buffer, sizeof(buffer), 5000);

	if (ret < 0)
    {
		#ifdef useDEBUG
		{
			printf("error write USB Async:\n%s\n", usb_strerror());
		}
		#endif
		
        return 0;
    }
    else
    {
        return 1;
    }
}

bool Wetterstation::readUsbASYNC()
{
	int ret;
	char buffer[BUF_SIZE];

	// Running an async write test
	ret = transfer_bulk_async(EP_IN, buffer, sizeof(buffer), 5000);

	if (ret < 0)
    {
		#ifdef useDEBUG
		{
			printf("error read USB Async:\n%s\n", usb_strerror());
		}
		#endif
		
        return 0;
    }
    else
    {
		ui._plainTextEdit->appendPlainText( tr( "dddd: %1" ).arg( buffer ) );
		
		#ifdef useDEBUG
		{
			printf("read USB Async:\n%s\n", buffer);
		}
		#endif
		
        return extractData(buffer);
    }
}

/*	In dieser Funktion wird der eingelesene String aus 
*	dem pSoc aufbereitet, und im Struct _data gespeichert. 
*	Folgende zusammensaetzung des Strings wurde vereinbart:
*	CR,LF,CR,LF				Startzeichenfolge
*	YYYY.MM.DD HH:MM:SS		Zeitstempel
*	
*	
*/
bool Wetterstation::extractData(char buffer[])
{
	// ACHTUNG 
	_data._temperatur = 32.1;
    _data._luftdruck = 1200;
    _data._luftfeuchte = 32;
    _data._taupunkt = 10;
    _data._windgeschwindigkeit = 70;
    _data._windrichtung[0] = 'N';
	_data._windrichtung[1] = 'N';
	_data._windrichtung[2] = 'O';

	return 1;
}