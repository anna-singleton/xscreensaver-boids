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
    XSetBackground(dpy, g, XBlackPixelOfScreen(DefaultScreenOfDisplay(dpy)));
    XSetWindowBackground(dpy, root, XBlackPixelOfScreen(DefaultScreenOfDisplay(dpy)));
    XSetForeground(dpy, g, XWhitePixelOfScreen(DefaultScreenOfDisplay(dpy)));
    XClearWindow(dpy, root);
    XFlush(dpy);

    boid test_boid = {0};
    test_boid.position.x = 500;
    test_boid.position.y = 500;
    test_boid.rotation = PI;


    while(1) {
        XClearWindow(dpy, root);
        boid_update(&test_boid, dpy, &root, &g);
        boid_draw(&test_boid, dpy, &root, &g);
        XFlush(dpy);
        usleep(1000 * 50);
    }
}
