#ifndef BOID_H
#define BOID_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include "anna-layer.h"
#include "vector.h"

#define BOID_SCALE 5

typedef struct {
    XPoint position;
    float rotation;
}Boid;

#endif

extern void boid_draw(Boid* boid, Display* dpy, Window* win, GC* g);
extern void boid_update(Boid* boid, Display* dpy, Window* win, GC* g);
