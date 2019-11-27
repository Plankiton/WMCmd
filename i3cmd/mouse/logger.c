#include "./mouse.c"

int main(int argc, char *argv[])
{
    Window window;
    XEvent xevent;
    Display * display;

    if( (display = XOpenDisplay(NULL)) == NULL )
        return -1;
    window = DefaultRootWindow(display);
    open_mouse_listenner(display, window);
    int screen = DefaultScreen(display);

    // logging on terminal eternaly...
    // logger(&xevent, display);

    // getting mouse location on mouse left click...
    XID id = get_window_id(display, screen);
    printf("%lu\n", id);
    printf("%lu\n", get_window_pid(id, display));
    return 0;
}
