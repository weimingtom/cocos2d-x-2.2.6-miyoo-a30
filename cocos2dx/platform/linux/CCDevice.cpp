#include "platform/CCDevice.h"
#if USE_NO_GLFW
//skip
#else
#include <X11/Xlib.h>
#endif
#include <stdio.h>

NS_CC_BEGIN

int CCDevice::getDPI()
{
	static int dpi = -1;
	if (dpi == -1)
	{
#if USE_NO_GLFW
	    dpi = 160;
#else
		Display *dpy;
	    char *displayname = NULL;
	    int scr = 0; /* Screen number */
	    dpy = XOpenDisplay (displayname);
	    /*
	     * there are 2.54 centimeters to an inch; so there are 25.4 millimeters.
	     *
	     *     dpi = N pixels / (M millimeters / (25.4 millimeters / 1 inch))
	     *         = N pixels / (M inch / 25.4)
	     *         = N * 25.4 pixels / M inch
	     */
	    double xres = ((((double) DisplayWidth(dpy,scr)) * 25.4) / 
	        ((double) DisplayWidthMM(dpy,scr)));
	    dpi = (int) (xres + 0.5);
	    //printf("dpi = %d\n", dpi);
#endif	    
	}
	return dpi;
}

NS_CC_END
