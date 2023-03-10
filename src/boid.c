#include "boid.h"
#include "vector.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

local void rotate_boid_point(float rot, short* x, short* y);

local XPoint BOID_STRUCTURE[] = {
    {1*BOID_SCALE, 0*BOID_SCALE},
    {2*BOID_SCALE, 2*BOID_SCALE},
    {1*BOID_SCALE, 3*BOID_SCALE},
    {0*BOID_SCALE, 2*BOID_SCALE},
    {1*BOID_SCALE, 0*BOID_SCALE}};



void boid_update(boid* boid, Display* dpy, Window* win, GC* g) {
    boid->rotation += 0.3;
    if (boid->rotation > 2*PI) {
        boid->rotation = 0;
    }

    short delta_x = cosf(boid->rotation - PI/2) * BOID_SPEED;
    short delta_y = sinf(boid->rotation - PI/2) * BOID_SPEED;

    boid->position.x += delta_x;
    boid->position.y += delta_y;
}

void boid_draw(boid *boid, Display *dpy, Window *win, GC *g) {
    XDrawPoint(dpy, *win, *g, boid->position.x, boid->position.y);
    XPoint real_pos[5] = {0};
    memcpy(real_pos, BOID_STRUCTURE, 5*sizeof(XPoint));
    for (int i=0; i < 5; i++) {
        // nasty rotation maths
        float st_x = (float) real_pos[i].x - (BOID_WIDTH / 2.0);
        float st_y = (float) real_pos[i].y - (BOID_HEIGHT / 2.0);
        real_pos[i].x = (short) ((st_x * cosf(boid->rotation)) - (st_y * sinf(boid->rotation)));
        real_pos[i].y = (short) ((st_y * cosf(boid->rotation)) + (st_x * sinf(boid->rotation)));

        // position the point
        real_pos[i].x += boid->position.x;
        real_pos[i].y += boid->position.y;
    }
    XDrawLines(dpy, *win, *g, real_pos, 5, CoordModeOrigin);
}
