#include "wetterstation.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	// qt
	QApplication a(argc, argv);
	Wetterstation w;

	// Alloc Debug Output if Enabled
	#ifdef useDEBUG
	{
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}
	#endif
	
	// Init USB
	if( !w.initUsb() )
	{
		#ifdef useDEBUG
		{
		printf("error initialising device: \n%s\n", usb_strerror());
		}
		#endif
		return -1L;	// Abbruch mit Fehler
	}
	else
	{
		#ifdef useDEBUG
		{
			printf("success: device %04X:%04X Initialiesed\n", MY_VID, MY_PID);
		}
		#endif
	}

	// Show Class
	w.show();

	// Start qt
	return a.exec();
}
