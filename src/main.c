#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "vroot.h"
#include "boid.h"

enum ProgramMode {
    STANDALONE,
    XSCREENSAVER,
};

int main(int argc, char** argv) {
    enum ProgramMode mode = XSCREENSAVER;

    int opt;
    while ((opt = getopt(argc,argv,"s")) != -1){
        switch (opt) {
        case 's':
            mode = STANDALONE;
            printf("Running in standalone mode\n");
            break;
        default:
            fprintf(stderr, "Unknown option.");
            return 1;
        }
    }

    Display *dpy = XOpenDisplay(getenv("DISPLAY"));
    Window root;

    switch (mode) {
    case STANDALONE:
        root = XCreateWindow(dpy, DefaultRootWindow(dpy), 0, 0, 1600, 900, 0, CopyFromParent,
                                   InputOutput, CopyFromParent, 0, NULL);
        XTextProperty p;
        char* name = "boids";
        XStringListToTextProperty(&name, 1, &p);
        XSetWMName(dpy, root, &p);
        XClassHint* ch = XAllocClassHint();
        ch->res_name = "boids";
        ch->res_class = "floating";
        XSetClassHint(dpy, root, ch);
        XMapWindow(dpy, root);
        break;
    case XSCREENSAVER:
        root = DefaultRootWindow(dpy);
        break;
    }

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
