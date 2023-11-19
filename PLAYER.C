#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <allegro.h>
#include "Player.h"
#include "Game.h"

void place_players(void);
void move_players(void);
void draw_players(BITMAP * bm);
int check_playersposition(void);
int random_spot(int start, int buffer);
void increment_animation(TEAM * t, int index);


BITMAP * PlayerBmp;

unsigned long LastTime;
int SecsPassed;


int RUN_ANIM[18] = {0,0,0,0,1,1,1,1,0,0,0,0,2,2,2,2,-1,0};
int FALL_ANIM[] = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,-1,8};

void place_players(void)
     {
     TEAM * p1, * p2;

     // Keep track of the time started //

     LastTime = time(NULL);
     SecsPassed = 0;


     Ball.thrown = 0;

     if (possession == HOME)
        {
        p1 = &Home;
        p2 = &Away;
        }
     else
        {
        p1 = &Away;
        p2 = &Home;
        }


     // QB //

     p1->Player[0].x = 150;
     p1->Player[0].y = 180;
     p1->Player[0].dir = STOPPED;
     p1->Player[0].pImage = RUN_ANIM;
     p1->Player[0].img = 0;
     p1->Player[0].speed = O_SPEED;
     p1->Player[0].minx = 20;
     p1->Player[0].maxx = 280;

     // 2 Yard Receiver //

     p1->Player[1].x = random_spot(70, 30);
     p1->Player[1].y = 120;
     p1->Player[1].dir = random() % 2;
     p1->Player[1].pImage = RUN_ANIM;
     p1->Player[1].img = random() % 3;
     p1->Player[1].speed = O_SPEED;
     p1->Player[1].minx = 20;
     p1->Player[1].maxx = 280;

     // 4 Yard Receiver //

     p1->Player[2].x = random_spot(230, 30);
     p1->Player[2].y = 60;
     p1->Player[2].dir = random() % 2;
     p1->Player[2].pImage = RUN_ANIM;
     p1->Player[2].img = random() % 3;
     p1->Player[2].speed = O_SPEED;
     p1->Player[2].minx = 20;
     p1->Player[2].maxx = 280;

     // 10 Yard Receiver //

     p1->Player[3].x = random_spot(150, 30);
     p1->Player[3].y = 0;
     p1->Player[3].dir = random() % 2;
     p1->Player[3].pImage = RUN_ANIM;
     p1->Player[3].img = random() % 3;
     p1->Player[3].speed = O_SPEED;
     p1->Player[3].minx = 20;
     p1->Player[3].maxx = 280;

     // Left Blocker //

     p1->Player[4].x = 30;
     p1->Player[4].y = 180;
     p1->Player[4].dir = 0;
     p1->Player[4].pImage = RUN_ANIM;
     p1->Player[4].img = random() % 3;
     p1->Player[4].speed = 0;
     p1->Player[4].minx = 0;
     p1->Player[4].maxx = 320;


     // Right Blocker //

     p1->Player[5].x = 270;
     p1->Player[5].y = 180;
     p1->Player[5].dir = 1;
     p1->Player[5].pImage = RUN_ANIM;
     p1->Player[5].img = random() % 3;
     p1->Player[5].speed = 0;
     p1->Player[5].minx = 0;
     p1->Player[5].maxx = 320;



     // Front defenders //

     p2->Player[0].x = random_spot(100, 50);
     p2->Player[0].y = 140;
     p2->Player[0].dir = random() % 2;
     p2->Player[0].pImage = RUN_ANIM;
     p2->Player[0].img = random() % 3;
     p2->Player[0].speed = D_SPEED;
     p2->Player[0].minx = 20;
     p2->Player[0].maxx = 200;

     p2->Player[1].x = random_spot(150, 50);
     p2->Player[1].y = 140;
     p2->Player[1].dir = random() % 2;
     p2->Player[1].pImage = RUN_ANIM;
     p2->Player[1].img = random() % 3;
     p2->Player[1].speed = O_SPEED;
     p2->Player[1].minx = 20;
     p2->Player[1].maxx = 280;

     p2->Player[2].x = random_spot(200, 50);
     p2->Player[2].y = 140;
     p2->Player[2].dir = random() % 2;
     p2->Player[2].pImage = RUN_ANIM;
     p2->Player[2].img = random() % 3;
     p2->Player[2].speed = D_SPEED;
     p2->Player[2].minx = 120;
     p2->Player[2].maxx = 280;

     // Middle Defenders //

     p2->Player[3].x = random_spot(130, 50);
     p2->Player[3].y = 80;
     p2->Player[3].dir = random() % 2;
     p2->Player[3].pImage = RUN_ANIM;
     p2->Player[3].img = random() % 3;
     p2->Player[3].speed = D_SPEED;
     p2->Player[3].minx = 20;
     p2->Player[3].maxx = 240;

     p2->Player[4].x = random_spot(110, 70);
     p2->Player[4].y = 80;
     p2->Player[4].dir = random() % 2;
     p2->Player[4].pImage = RUN_ANIM;
     p2->Player[4].img = random() % 3;
     p2->Player[4].speed = O_SPEED;
     p2->Player[4].minx = 20;
     p2->Player[4].maxx = 280;

     p2->Player[5].x = random_spot(200, 50);
     p2->Player[5].y = 80;
     p2->Player[5].dir = random() % 2;
     p2->Player[5].pImage = RUN_ANIM;
     p2->Player[5].img = random() % 3;
     p2->Player[5].speed = D_SPEED;
     p2->Player[5].minx = 120;
     p2->Player[5].maxx = 280;

     // Back defenders //

     p2->Player[6].x = random_spot(70, 30);
     p2->Player[6].y = 20;
     p2->Player[6].dir = random() % 2;
     p2->Player[6].pImage = RUN_ANIM;
     p2->Player[6].img = random() % 3;
     p2->Player[6].speed = D_SPEED;
     p2->Player[6].minx = 20;
     p2->Player[6].maxx = random_spot(170, 30);

     p2->Player[7].x = random_spot(150, 50);
     p2->Player[7].y = 20;
     p2->Player[7].dir = random() % 2;
     p2->Player[7].pImage = RUN_ANIM;
     p2->Player[7].img = random() % 3;
     p2->Player[7].speed = O_SPEED;
     p2->Player[7].minx = 20;
     p2->Player[7].maxx = 280;

     p2->Player[8].x = random_spot(240, 30);
     p2->Player[8].y = 20;
     p2->Player[8].dir = random() % 2;
     p2->Player[8].pImage = RUN_ANIM;
     p2->Player[8].img = random() % 3;
     p2->Player[8].speed = D_SPEED;
     p2->Player[8].minx = random_spot(120, 30);
     p2->Player[8].maxx = 280;

     // Left Rusher //

     p2->Player[9].x = 10;
     p2->Player[9].y = 180;
     p2->Player[9].dir = RIGHT;
     p2->Player[9].pImage = RUN_ANIM;
     p2->Player[9].img = random() % 3;
     p2->Player[9].speed = 0;
     p2->Player[9].minx = 0;
     p2->Player[9].maxx = 320;

     // Right Rusher //

     p2->Player[10].x = 290;
     p2->Player[10].y = 180;
     p2->Player[10].dir = LEFT;
     p2->Player[10].pImage = RUN_ANIM;
     p2->Player[10].img = random() % 3;
     p2->Player[10].speed = 0;
     p2->Player[10].minx = 0;
     p2->Player[10].maxx = 320;
     }


void move_players(void)
     {
     TEAM * p1, * p2;
     int index;
     float hyp, adj;

     if (possession == HOME)
        {
        p1 = &Home;
        p2 = &Away;
        }
     else
        {
        p1 = &Away;
        p2 = &Home;
        }


     // Check to see if the rushers get through //

     if ((time(NULL) - LastTime) >= 1)
        {
        // Left rusher //

        if (p1->Player[4].dir != BEATUP)
            if (random() % 20 <= SecsPassed)
               {
               p2->Player[9].speed = D_SPEED;
               p1->Player[4].dir   = BEATUP;
               p1->Player[4].pImage = FALL_ANIM;
               p1->Player[4].img = 0;
               }

        // Right rusher //

        if (p1->Player[5].dir != BEATUP)
            if (random() % 20 <= SecsPassed)
               {
               p2->Player[10].speed = D_SPEED;
               p1->Player[5].dir    = BEATUP;
               p1->Player[5].pImage = FALL_ANIM;
               p1->Player[5].img = 0;
               }

        SecsPassed++;
        LastTime = time(NULL);
        }

     // Move the ball if it has been thrown //

     if (Ball.thrown)
        {
        Ball.x += (fcos(Ball.dir) * BALL_SPEED) / 7500;
        Ball.y += (fsin(Ball.dir) * BALL_SPEED) / 7500;

        if (Ball.y < 0)
            Ball.y = 0;
        if (Ball.x < 0)
            Ball.x = 0;
        if (Ball.x > 319)
            Ball.x = 319;
        }

     // Figure out the QB's movement //

     if (!key[KEY_LEFT] && !key[KEY_RIGHT] && p1->Player[0].dir != UP)
        {
        p1->Player[0].pImage = RUN_ANIM;
        p1->Player[0].img = 0;
        p1->Player[0].dir = STOPPED;
        }
     else if (key[KEY_LEFT] && p1->Player[0].dir != UP)
        p1->Player[0].dir = LEFT;
     else if (key[KEY_RIGHT] && p1->Player[0].dir != UP)
        p1->Player[0].dir = RIGHT;

     if (key[KEY_UP])
        p1->Player[0].dir = UP;

     if ((key[KEY_F] || (mouse_b & 1)) && !Ball.thrown && p1->Player[0].dir != UP)
        {
        Ball.x = p1->Player[0].x + 10;
        Ball.y = p1->Player[0].y;
        hyp = sqrt(((mouse_x - Ball.x) * (mouse_x - Ball.x)) + ((mouse_y - Ball.y) * (mouse_y - Ball.y)));
        adj = abs(mouse_x - Ball.x);
        Ball.dir = facos(ftofix(adj / hyp));

        if (mouse_x < Ball.x)
           Ball.dir = ftofix(128 + fixtof(Ball.dir));
        else
           Ball.dir = ftofix(255 - fixtof(Ball.dir));

        Ball.thrown = 1;
        }


     // QB & Receivers //

     for (index = 0; index < 6; index++)
         {
         if (p1->Player[index].dir == RIGHT)
             p1->Player[index].x += p1->Player[index].speed;
         else if (p1->Player[index].dir == LEFT)
             p1->Player[index].x -= p1->Player[index].speed;
         else if (p1->Player[index].dir == UP)
             p1->Player[index].y -= p1->Player[index].speed - 2;


         if (p1->Player[index].x < p1->Player[index].minx)
            {
            p1->Player[index].x = p1->Player[index].minx;
            p1->Player[index].dir = RIGHT;
            }


         if (p1->Player[index].x > p1->Player[index].maxx)
            {
            p1->Player[index].x = p1->Player[index].maxx;
            p1->Player[index].dir = LEFT;
            }

         // Increment the animation //

         increment_animation(p1, index);
         }


     // Defenders //

     for (index = 0; index < 11; index++)
         {
         if (p2->Player[index].dir == RIGHT)
             p2->Player[index].x += p2->Player[index].speed;
         else if (p2->Player[index].dir == LEFT)
             p2->Player[index].x -= p2->Player[index].speed;

         if (p2->Player[index].x < p2->Player[index].minx)
            {
            p2->Player[index].x = p2->Player[index].minx;
            p2->Player[index].dir = RIGHT;
            }

         if (p2->Player[index].x > p2->Player[index].maxx)
            {
            p2->Player[index].x = p2->Player[index].maxx;
            p2->Player[index].dir = LEFT;
            }

         // Increment the animation //

         increment_animation(p2, index);
         }
     }


void draw_players(BITMAP * bm)
     {
     char str[256];
     TEAM * p1, * p2;
     int index, imgx, imgy;

     if (possession == HOME)
        {
        p1 = &Home;
        p2 = &Away;
        }
     else
        {
        p1 = &Away;
        p2 = &Home;
        }

     for (index = 0; index < 6; index++)
         {
         if (p1->Player[index].dir == RIGHT || p1->Player[index].dir == STOPPED || p1->Player[index].dir == UP)
            imgy = 22;
         else if (p1->Player[index].dir == LEFT)
            imgy = 1;
         else if (p1->Player[index].dir == BEATUP)
            imgy = 43;

         imgx = p1->Player[index].pImage[p1->Player[index].img] * 20 + (p1->Player[index].pImage[p1->Player[index].img] + 1);

         masked_blit(p1->PlayerBmp, bm, imgx, imgy, p1->Player[index].x, p1->Player[index].y, 20, 20);
         }

     for (index = 0; index < 11; index++)
         {
         if (p2->Player[index].dir == RIGHT || p2->Player[index].dir == STOPPED)
            imgy = 22;
         else if (p2->Player[index].dir == LEFT)
            imgy = 1;
         else if (p2->Player[index].dir == BEATUP)
            imgy = 43;

         imgx = p2->Player[index].pImage[p2->Player[index].img] * 20 + (p2->Player[index].pImage[p2->Player[index].img] + 1);

         masked_blit(p2->PlayerBmp, bm, imgx, imgy, p2->Player[index].x, p2->Player[index].y, 20, 20);
         }

     // Draw the ball //

     if (Ball.thrown)
         {
         rectfill(bm, Ball.x, Ball.y, Ball.x + 1, Ball.y + 2, 6);
         }

     //sprintf(str, "%f", fixtof(Ball.dir));
     //textout(bm, font, str, 0, 0, 15);
     }


int check_playersposition(void)
     {
     TEAM * p1, * p2;
     int index;

     if (possession == HOME)
        {
        p1 = &Home;
        p2 = &Away;
        }
     else
        {
        p1 = &Away;
        p2 = &Home;
        }


     // Defenders //

     for (index = 0; index < 11; index++)
         {
         // Check if the defender intercepts the ball //

         if (Ball.x + 1 >= p2->Player[index].x + 5  &&
             Ball.x <= p2->Player[index].x + 16     &&
             Ball.y >= p2->Player[index].y + 4      &&
             Ball.y + 3 <= p2->Player[index].y + 18 &&
             Ball.thrown)
             return -20;

         // Check if the defender tackles the QB //

         if (p1->Player[0].x + 16 >= p2->Player[index].x + 5 &&
             p1->Player[0].x + 5 <= p2->Player[index].x + 16 &&
             p1->Player[0].y + 4 <= p2->Player[index].y + 18 &&
             p1->Player[0].y + 10 >= p2->Player[index].y + 4 &&
             !Ball.thrown)
             {
             // Front defender //

             if (index < 3)
                return -1;

             // Mid defender //

             else if (index >= 3 && index < 6)
                return 2;

             // Back defender //

             else if (index >= 6 && index < 9)
                return 5;

             // Rushers //

             else if (index >= 9)
                return -2;
             }
         }

     // Receivers //

     for (index = 1; index < 4; index++)
         {
         // Check if the defender intercepts the ball //

         if (Ball.x + 1 >= p1->Player[index].x + 5  &&
             Ball.x <= p1->Player[index].x + 16     &&
             Ball.y >= p1->Player[index].y + 4      &&
             Ball.y + 3 <= p1->Player[index].y + 18 &&
             Ball.thrown)
             {
             if (index == 1)
                return 2;
             else if (index == 2)
                return 4;
             else if (index == 3)
                return 20;
             }
         }


     // Check if the ball reached the end of the screen //

     if ((Ball.y <= 0 || Ball.x <= 0 || Ball.x >= 319) && Ball.thrown)
         return 999;

     // Check if the QB has made it to the end of the screen //

     if (p1->Player[0].y <= 0 && !Ball.thrown)
         return 10;


     return 0;
     }


int random_spot(int start, int buffer)
    {
    return (start + ((random() % (buffer * 2)) - buffer));
    }


void increment_animation(TEAM * t, int index)
    {
    t->Player[index].img++;
    if (t->Player[index].pImage[t->Player[index].img] == -1)
        t->Player[index].img = t->Player[index].pImage[t->Player[index].img + 1];
    }
