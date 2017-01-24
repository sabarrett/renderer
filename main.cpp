#include <stdio.h>
#include <assert.h>
#include <X11/Xlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  Display* dsp;
  int blackColor, whiteColor;

  dsp = XOpenDisplay(NULL);
  assert(dsp);

  blackColor = BlackPixel(dsp, DefaultScreen(dsp));
  whiteColor = WhitePixel(dsp, DefaultScreen(dsp));

  Window wnd;

  wnd = XCreateSimpleWindow(dsp, DefaultRootWindow(dsp), 0, 0,
			    200, 100, 0, blackColor, blackColor);

  XSelectInput(dsp, wnd, StructureNotifyMask | ButtonPressMask | KeyPressMask);
  // Calling XSelectInput again overrides previous input
  //XSelectInput(dsp, wnd, ButtonPressMask);

  XMapWindow(dsp, wnd);

  GC gc = XCreateGC(dsp, wnd, 0, (0));

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
	printf("Button Release\n");
	break;
      }
    

    if (e.type == MapNotify)
      {
	XDrawLine(dsp, wnd, gc, 10, 60, 180, 20);
	XFlush(dsp);
      }
  }

  sleep(3);

  XDestroyWindow(dsp, wnd);

  XCloseDisplay(dsp);

  return 0;
}
