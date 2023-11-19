#ifndef __Player_H
#define __Player_H

#define RUN_ANIM_MAX 16

#define O_SPEED  3
#define D_SPEED  2
#define BALL_SPEED .5

#define BEATUP   -2
#define STOPPED  -1
#define LEFT      0
#define RIGHT     1
#define UP        2
#define CHASE     3
#define VICTORY   4
#define TOUCHDOWN 5

typedef struct
    {
    int x, y, speed, dir, minx, maxx;
    int * pImage;
    int img;
    } PLAYER;

#endif
