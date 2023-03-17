#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "vroot.h"
#include "state.h"
#include <time.h>
#include "boid.h"

static int is_standalone = 0;

int main(int argc, char** argv) {
    static struct option long_options[] = {
        {"standalone", no_argument, &is_standalone, 1},
        {"boid-count", optional_argument, NULL, 'c'},
        {"boid-scale", optional_argument, NULL, 's'},
        {"boid-speed", optional_argument, NULL, 'v'}
    };

    srand((unsigned int)time(NULL));

    int boid_count = 10;
    int boid_scale = 10;
    int boid_speed = 10;

    int opt;
    int option_index;
    while ((opt = getopt_long(argc, argv, "", long_options, &option_index)) != -1){
        if(optarg) {
            printf("%s has optarg of %s\n", long_options[option_index].name, optarg);
            switch (option_index) {
            case 1:
                boid_count = atoi(optarg);
                break;
            case 2:
                boid_scale = atoi(optarg);
                break;
            case 3:
                boid_speed = atoi(optarg);
                break;
            }
        }
    }

    Display *dpy = XOpenDisplay(getenv("DISPLAY"));
    Window root;

    switch (is_standalone) {
    case 1:
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
    case 0:
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

    state s = state_init(boid_count, boid_scale, boid_speed, wa.width, wa.height);

    while(1) {
        XClearWindow(dpy, root);
        state_update(&s);
        state_draw(&s, dpy, &root, &g);
        XFlush(dpy);
        usleep(1000 * 50);
    }
}
