#include <QtWidgets/QApplication>
#include "usbcom.h"

usbCom::usbCom(void)
{
	_usbHandle = 0;
	_bus = 0;
    _dev = 0;
}

usbCom::~usbCom(void)
{
}

bool usbCom::open_dev(void)
{
	// Initialise libusb with default context
	usb_init();

	// Find Busses and Devices
	usb_find_busses(); /* find all busses */
    usb_find_devices(); /* find all connected devices */

	// Open Device
    for (_bus = usb_get_busses(); _bus; _bus = _bus->next)
    {
        for (_dev = _bus->devices; _dev; _dev = _dev->next)
        {
            if (_dev->descriptor.idVendor == MY_VID
                    && _dev->descriptor.idProduct == MY_PID)
            {
                _usbHandle =  usb_open(_dev);
				return true;
            }
        }
    }
		#ifdef useDEBUG
		{
			printf("error oben USB Device:\n%s\n", usb_strerror());
		}
		#endif
	
    return false;
}

bool usbCom::set_config(void)
{
	if (usb_claim_interface(_usbHandle, 0) < 0)
    {
		#ifdef useDEBUG
		{
			printf("error set config:\n%s\n", usb_strerror());
		}
		#endif
		
        usb_close(_usbHandle);
        return false;
    }
    
	return true;
}

bool usbCom::claim_interface(void)
{
	if (usb_claim_interface(_usbHandle, 0) < 0)
    {
		#ifdef useDEBUG
		{
			printf("error claim interface:\n%s\n", usb_strerror());
		}
		#endif
		
        usb_close(_usbHandle);
        return false;
    }

	return true;
}

int usbCom::transfer_bulk_async(int ep, char *bytes, int size, int timeout)
{
	// Each async transfer requires it's own context. A transfer
    // context can be re-used.  When no longer needed they must be
    // freed with usb_free_async().
    //
    void* async_context = NULL;
    int ret;

    // Setup the async transfer.  This only needs to be done once
    // for multiple submit/reaps. (more below)
    //
    ret = usb_bulk_setup_async(_usbHandle, &async_context, ep);
    if (ret < 0)
    {
		#ifdef useDEBUG
		{
			printf("error transfer:\n%s\n", usb_strerror());
		}
		#endif
		
        return ret;
    }

    // Submit this transfer.  This function returns immediately and the
    // transfer is on it's way to the device.
    //
    ret = usb_submit_async(async_context, bytes, size);
    if (ret < 0)
    {
		#ifdef useDEBUG
		{
			printf("error transfer:\n%s\n", usb_strerror());
		}
		#endif
		
        usb_free_async(&async_context);
        return ret;
    }

    // Wait for the transfer to complete.  If it doesn't complete in the
    // specified time it is cancelled.  see also usb_reap_async_nocancel().
    //
    ret = usb_reap_async(async_context, timeout);

    // Free the context.
    usb_free_async(&async_context);

	return ret;
}