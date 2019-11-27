#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/Xproto.h>

#include <X11/Xmu/WinUtil.h>

unsigned long get_window_id(Display *dpy, int screen, int button)
{
    Cursor cursor;        /* cursor to use when selecting */
    Window root;        /* the current root */
    Window retwin = None;    /* the window that got selected */
    int retbutton = -1;        /* button used to select window */
    int pressed = 0;        /* count of number of buttons pressed */

#define MASK (ButtonPressMask | ButtonReleaseMask)

    root = RootWindow (dpy, screen);
    cursor = XCreateFontCursor (dpy, XC_mouse);
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
                    retbutton = event.xbutton.button;
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

    printf("\nwindow: %li\n", ((button == -1 || retbutton == button) ? retwin : None));
    return ((button == -1 || retbutton == button) ? retwin : None);
}
