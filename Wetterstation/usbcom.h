#pragma once

#include <lusb0_usb.h>

// Device vendor and product id.
#define MY_VID	0x1111
#define MY_PID	0x2222

// Device endpoint(s)
#define EP_IN	0x81
#define EP_OUT	0x02

// Device of bytes to transfer.
#define BUF_SIZE 64

class usbCom
{
public:
	usbCom(void);
	~usbCom(void);

protected:
	bool open_dev(void);
	bool set_config(void);
	bool claim_interface(void);
	int transfer_bulk_async(int ep, char *bytes, int size, int timeout);
	
private:
	struct usb_bus *_bus;
    struct usb_device *_dev;
	usb_dev_handle *_usbHandle;    
};

