#include "state.h"

#define EDGE_BUFFER 10

state state_init(int boid_count, int boid_scale, int boid_speed, int window_width, int window_height){
    state s = {0};
    s.boid_count = boid_count;

    s.boid_scale = boid_scale;
    s.boid_width = BOID_WIDTH_FACTOR * boid_scale;
    s.boid_height = BOID_HEIGHT_FACTOR * boid_scale;

    s.boid_speed = boid_speed;

    s.boids = calloc(boid_count, sizeof(boid));

    for (int i=0; i < boid_count; i++) {
        s.boids[i].rotation = (float) (float)rand()/(float)(RAND_MAX/(PI*2));
        s.boids[i].position.x = (short) EDGE_BUFFER + (rand()%(window_width - (EDGE_BUFFER/2)));
        s.boids[i].position.y = (short) EDGE_BUFFER + (rand()%(window_height - (EDGE_BUFFER/2)));
    }
    return s;
}

void state_update(state* s){
    for (int i=0; i < s->boid_count; i++) {
        boid_update(&s->boids[i]);
    }
}

void state_draw(state* s, Display* dpy, Window* win, GC* g){
    for (int i=0; i < s->boid_count; i++) {
        boid_draw(&s->boids[i], dpy, win, g);
    }
}
