#ifndef STATE_H
#define STATE_H

#include <stdlib.h>
#include <stdio.h>
#include "boid.h"

typedef struct {
    boid* boids;
    int boid_count;
    int boid_scale;
    int boid_width;
    int boid_height;
    int boid_speed;
}state;

extern state state_init(int boid_count, int boid_scale, int boid_speed, int window_width,
        int window_height);

extern void state_update(state* s);

extern void state_draw(state* s, Display* dpy, Window* win, GC* g);

#endif
