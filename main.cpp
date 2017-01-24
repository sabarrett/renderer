#include <stdio.h>
#include <assert.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <X11/keysymdef.h>

int main(int argc, char* argv[])
{
  Display* dsp;
  int blackColor, whiteColor;
  Window wnd;
  GC gc;

  dsp = XOpenDisplay(NULL);
  assert(dsp);

  blackColor = BlackPixel(dsp, DefaultScreen(dsp));
  whiteColor = WhitePixel(dsp, DefaultScreen(dsp));

  wnd = XCreateSimpleWindow(dsp, DefaultRootWindow(dsp), 0, 0,
			    200, 100, 0, blackColor, blackColor);

  XSelectInput(dsp, wnd, StructureNotifyMask | ButtonPressMask | KeyPressMask | KeyReleaseMask | PointerMotionMask);

  XMapWindow(dsp, wnd);

  gc = XCreateGC(dsp, wnd, 0, (0));

  XSetForeground(dsp, gc, whiteColor);

  for (;;) {
    XEvent e;
    XNextEvent(dsp, &e);
    
    switch (e.type)
      {
      case KeyPress:
	printf("Key press\n");
	break;
      case KeyRelease:
	printf("Key release\n");
	{
	  XKeyEvent b = e.xkey;
	  int keysym = (int)XLookupKeysym(&b, 0); // Why 0? I'm not sure...
	  printf(" Code %d\n", b.keycode);
	  printf(" keysym %c\n", (int)XLookupKeysym(&b, 0));
	  if (keysym == XK_Left)
	    printf("***** LEFT ARROW PRESSED *****\n");
	  if (keysym == XK_a)
	    printf("** A PRESSED **\n");
	}
	break;
      case FocusIn:
	printf("Focus in\n");
	break;
      case FocusOut:
	printf("Focus out\n");
	break;
      case ButtonPress:
	printf("Button Press\n");
	break;
      case ButtonRelease:
	printf("Button Release");
	break;
      case MotionNotify:
	printf("Mouse moved");
	{
	  XMotionEvent m = e.xmotion;
	  //printf("{%d, %d}\n", m.x, m.y);
	}
	break;
      case MapNotify:
	XDrawLine(dsp, wnd, gc, 10, 60, 180, 20);
	XFlush(dsp);
	break;
      }
  }

  sleep(3);

  XDestroyWindow(dsp, wnd);

  XCloseDisplay(dsp);

  return 0;
}
