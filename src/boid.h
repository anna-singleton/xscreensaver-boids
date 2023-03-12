#ifndef BOID_H
#define BOID_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include "anna-layer.h"
#include "vector.h"

#define BOID_SCALE 10.0

// N.B. while vertical
#define BOID_WIDTH 2.0*BOID_SCALE
#define BOID_WIDTH_FACTOR 2

// N.B. while vertical
#define BOID_HEIGHT 3.0*BOID_SCALE
#define BOID_HEIGHT_FACTOR 3

#define BOID_SPEED 10

typedef struct {
    // unsigned int id;
    XPoint position;
    float rotation;
}boid;

#endif

extern void boid_draw(boid* boid, Display* dpy, Window* win, GC* g);
extern void boid_update(boid* boid);
