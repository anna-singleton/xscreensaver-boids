#ifndef STATE_H
#define STATE_H
#include "boid.h"

typedef struct {
    boid* boids;
    int boid_count;
    int boid_scale;
    int boid_width;
    int boid_height;
    int boid_speed;
}state;

state state_init(int boid_count, int boid_scale, int boid_speed, int window_width,
        int window_height);

void state_update(state* s);

void state_draw(state* s, Display* dpy, Window* win, GC* g);

#endif
