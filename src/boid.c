#include <math.h>
#include "boid.h"

local void rotate_boid_point(float rot, short* x, short* y);

local XPoint BOID_STRUCTURE[] = {
    {1*BOID_SCALE, 0*BOID_SCALE},
    {2*BOID_SCALE, 2*BOID_SCALE},
    {1*BOID_SCALE, 3*BOID_SCALE},
    {0*BOID_SCALE, 2*BOID_SCALE},
    {1*BOID_SCALE, 0*BOID_SCALE}};



void boid_update(boid* boid, int win_width, int win_height) {
    short delta_x = cosf(boid->rotation - PI/2) * BOID_SPEED;
    short delta_y = sinf(boid->rotation - PI/2) * BOID_SPEED;

    if (boid->position.x + delta_x < 0 || boid->position.x + delta_x > win_width) {
        delta_x *= -1;
    }

    if (boid->position.y + delta_y < 0 || boid->position.y + delta_y > win_height) {
        delta_y *= -1;
    }

    boid->rotation = atan2(delta_y, delta_x) + PI/2;

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
