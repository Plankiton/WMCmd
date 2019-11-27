#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h>
#include <X11/Xproto.h>
#include <X11/Xmu/WinUtil.h>

typedef struct {
    int x, y, button;
} mouse_location;

char *key_name[] = {
    "first",
    "second (or middle)",
    "third",
    "fourth",  // :D
    "fivth"    // :|
};

#define open_mouse_listenner(display, window)\
    XAllowEvents(display, AsyncBoth, CurrentTime);\
    XGrabPointer(display,\
                 window,\
                 1,\
                 PointerMotionMask | ButtonPressMask | ButtonReleaseMask , \
                 GrabModeAsync,\
                 GrabModeAsync,\
                 None,\
                 None,\
                 CurrentTime)

Window get_window_id(Display *dpy, int screen)
{
    Cursor cursor;        /* cursor to use when selecting */
    Window root;        /* the current root */
    Window retwin = None;    /* the window that got selected */
    int pressed = 0;        /* count of number of buttons pressed */

#define MASK (ButtonPressMask | ButtonReleaseMask)

    root = RootWindow (dpy, screen);
    cursor = XCreateFontCursor (dpy, XC_arrow);
    if (cursor == None)
        exit(1);
    XSync (dpy, 0);            /* give xterm a chance */

    if (XGrabPointer (dpy, root, False, MASK, GrabModeSync, GrabModeAsync,
                None, cursor, CurrentTime) != GrabSuccess)
        exit(1);

    /* from dsimple.c in xwininfo */
    while (retwin == None || pressed != 0) {
        XEvent event;

        XAllowEvents (dpy, SyncPointer, CurrentTime);
        XWindowEvent (dpy, root, MASK, &event);
        switch (event.type) {
            case ButtonPress:
                if (retwin == None) {
                    retwin = ((event.xbutton.subwindow != None) ?
                            event.xbutton.subwindow : root);
                }
                pressed++;
                continue;
            case ButtonRelease:
                if (pressed > 0) pressed--;
                continue;
        }                    /* end switch */
    }                        /* end for */

    XUngrabPointer (dpy, CurrentTime);
    XFreeCursor (dpy, cursor);
    XSync (dpy, 0);

    return retwin;
}


mouse_location get_mouse_location(XEvent * xevent, Display * display, int button) {
    while(1) {
        XNextEvent(display, xevent);

        if (xevent->type==ButtonRelease && xevent->xbutton.button == button){
            mouse_location local = {xevent->xmotion.x_root, xevent->xmotion.y_root, xevent->xbutton.button};
            return local;
        }
    }
}

int logger (XEvent * xevent, Display * display){
    while(1) {
        XNextEvent(display, xevent);

        switch (xevent->type) {
            case MotionNotify:
                printf("Mouse move      : [%d, %d]\n", xevent->xmotion.x_root, xevent->xmotion.y_root);
                break;
            case ButtonPress:
                printf("Button pressed  : %s\n", key_name[xevent->xbutton.button - 1]);
                break;
            case ButtonRelease:
                printf("Button released : %s\n", key_name[xevent->xbutton.button - 1]);
                break;
        }
    }

    return 0;
}

static long get_window_pid(Window focuswin, Display * dpy){
    Atom nameAtom = XInternAtom(dpy, "_NET_WM_PID", 1);
    Atom type;
    int format, status;
    long pid = -1;
    unsigned long nitems, after;
    unsigned char *data;

    status = XGetWindowProperty(dpy, focuswin, nameAtom, 0, 1024, 0,
            XA_CARDINAL, &type, &format, &nitems, &after, &data);
    if (status == Success && data) {
        pid = *((long*)data);
        XFree(data);
    }

    return pid;
}
