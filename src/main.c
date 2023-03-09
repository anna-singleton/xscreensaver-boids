#include <X11/X.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <stdio.h>
#include "vroot.h"
#include "boid.h"

int main() {
    Display *dpy = XOpenDisplay(getenv("DISPLAY"));

    Window root = DefaultRootWindow(dpy);

    GC g = XCreateGC(dpy, root, 0, NULL);

    XWindowAttributes wa;
    XGetWindowAttributes(dpy, root, &wa);

    unsigned int screen_num = DefaultScreen(dpy);

    unsigned int width = DisplayWidth(dpy, screen_num);
    unsigned int height = DisplayHeight(dpy, screen_num);
    XClearWindow(dpy, root);
    XFlush(dpy);

    XSetForeground(dpy, g, XWhitePixelOfScreen(DefaultScreenOfDisplay(dpy)));

    while(1) {
        boid_draw(NULL, dpy, &root, &g);

        if(random()%500 < 1) {
            XClearWindow(dpy, root);
        }

        XFlush(dpy);
        usleep(1000*500);
    }
}
