#include "boid.h"
#include <X11/X.h>

local XPoint BOID_STRUCTURE[] = {
    {1*BOID_SCALE, 0*BOID_SCALE},
    {2*BOID_SCALE, 2*BOID_SCALE},
    {1*BOID_SCALE, 3*BOID_SCALE},
    {0*BOID_SCALE, 2*BOID_SCALE},
    {1*BOID_SCALE, 0*BOID_SCALE}};


void boid_update(Boid* boid, Display* dpy, Window* win, GC* g) {

}

void boid_draw(Boid *boid, Display *dpy, Window *win, GC *g) {
    XDrawLines(dpy, *win, *g, BOID_STRUCTURE, 5, CoordModeOrigin);
}

