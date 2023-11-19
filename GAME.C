#include <stdio.h>
#include <allegro.h>
#include "Game.h"
#include "Player.h"
#include "Display.h"
#include "Input.h"


// Global variables //

TEAM Home, Away;
BALL Ball;

int possession;
int YardLine;
int Down;
int ToGo;

int GameSpeed;

PALETTE GamePalette;
BITMAP * Background;
BITMAP * buffer;
BITMAP * Messages;

int EndGame;

// Team gfx files //

char * TeamGfx[3] = {"SF", "GB", "DL"};


int pick_teams()
     {
     }


void load_team(TEAM * t, int teamnum, int usepal)
     {
     char filename[10];

     sprintf(filename, "%sPLAY.PCX", TeamGfx[teamnum]);


     if (usepal)
          t->PlayerBmp = load_bitmap(filename, GamePalette);
     else
          t->PlayerBmp = load_bitmap(filename, NULL);


     if (!t->PlayerBmp)
        {
        printf("COULD NOT LOAD GRAPHIC FILE %s\n", filename);
        while(!key[KEY_ESC]){}
        }
     }


// Intermission functions //


void coin_toss(void)
     {
     Home.score = 0;
     Away.score = 0;

     possession = random() % 2;
     kick_off();
     }


void kick_off(void)
     {
     YardLine = 20 + ((random() % 30) - (random() % 15));
     firstdown();
     }


void half_time(void)
     {
     }


void end_game(void)
     {
     }


// Game time functions //


void game_loop(void)
     {
     // Set all flags //

     EndGame = 0;


     // Set the palette //

     set_palette(GamePalette);


     coin_toss();

     while(!EndGame)
        {
        show_info();
        do_play();
        }

     end_game();
     }


void show_info(void)
     {
     draw_info();
     wait_for_key();
     }


void do_play(void)
     {
     int retval;

     place_players();
     create_background();

     while((retval = check_playersposition()) == 0)
          {
          keep_game_speed();
          move_players();
          draw_background();
          draw_players(buffer);

          if (!Ball.thrown)
             {
             rect(buffer, mouse_x - 10, mouse_y - 10, mouse_x + 10, mouse_y + 10, 15);
             line(buffer, mouse_x - 1, mouse_y, mouse_x + 1, mouse_y, 15);
             line(buffer, mouse_x, mouse_y - 1, mouse_x, mouse_y + 1, 15);
             }

          draw_screen();

          if (key[KEY_ESC]) EndGame = 1;
          }

     end_play(retval);
     }


void keep_game_speed(void)
     {
     delay(GameSpeed);
     }


void end_play(int playval)
     {
     Ball.thrown = 0;

     // Incomplete pass //

     if (playval == 999)
        {
        Down++;
        if (Down > 4)
           turnover();
        }

     // Loss of yards //

     if (playval < 0 && playval != -20)
        {
        YardLine += playval;
        ToGo -= playval;

        Down++;
        if (Down > 4)
           turnover();
        }

     // Interception //

     if (playval == -20)
        {
        turnover();
        }

     // Gain of yards //

     if (playval > 0 && playval < 999)
        {
        YardLine += playval;
        ToGo -= playval;

        if (YardLine >= 100)
           {
           touchdown();
           }
        else
           {
           if (ToGo <= 0)
               firstdown();
           else
               {
               Down++;
               if (Down > 4)
                   turnover();
               }
           }
        }
     }


// End of play functions //


void turnover(void)
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

     for (index = 0; index < 11; index++)
         {
         p1->Player[index].speed = 0;
         p1->Player[index].dir   = BEATUP;
         p2->Player[index].speed = 0;
         p2->Player[index].dir   = STOPPED;
         }

     draw_background();
     draw_players(buffer);
     draw_screen();

     wait_for_key();

     possession = !possession;
     Down = 1;
     ToGo = 10;
     YardLine = 100 - YardLine;
     }


void firstdown(void)
     {
     Down = 1;
     ToGo = 10;
     }


void touchdown(void)
     {
     if (possession == HOME)
        Home.score += 7;
     else
        Away.score += 7;

     possession = !possession;
     kick_off();
     }


// Misc functions //

int convert_yardline(int y)
    {
    if (y > 50)
       return (100 - y);
    else
       return y;
    }
