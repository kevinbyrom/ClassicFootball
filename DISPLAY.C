#include <Allegro.h>
#include "Display.h"
#include "Game.h"
#include "Player.h"

void init_display(void)
     {
     // Create our memory buffers //

     Messages = load_bitmap("Messages.pcx", NULL);
     buffer = create_bitmap(320, 200);
     Background = create_bitmap(320,200);

     // Set the graphics mode //

     set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0);
     }


void destroy_display(void)
     {
     // Destroy any created bitmaps //

     if (buffer)
        destroy_bitmap(buffer);

     if (Background)
        destroy_bitmap(Background);

     if (Home.PlayerBmp)
        destroy_bitmap(Home.PlayerBmp);

     if (Away.PlayerBmp)
        destroy_bitmap(Away.PlayerBmp);

     if (Messages)
        destroy_bitmap(Messages);
     }


void draw_screen(void)
     {
     vsync();
     blit(buffer, screen, 0, 0, 0, 0, 320, 200);
     }


void draw_info(void)
     {
     char string[50];

     rectfill(buffer, 0, 0, 320, 200, 0);

     sprintf(string, "%d and %d on the %d Yrd Line : %d - %d", Down, ToGo, convert_yardline(YardLine), Home.score, Away.score);
     textout(buffer, font, string, 5, 5, 15);

     draw_screen();
     }


void create_background(void)
     {
     int x, y;

     // Grass //

     for (y = 0; y < 10; y++)
         {
         for (x = 0; x < 16; x++)
             {
             blit(Home.PlayerBmp, Background, 64, 1, x * 20, y * 20, 20, 20);
             }
         }

     //rectfill(bm, 0, 0, 320, 10, 35);

     // Sidelines //

     rectfill(Background, 5, 0, 10, 200, 15);
     rectfill(Background, 310, 0, 315, 200, 15);
     }


void draw_background(void)
     {
     blit(Background, buffer, 0, 0, 0, 0, 320, 200);
     }


void draw_message(int msg)
     {
     int imgy;

     if (msg == MSG_TOUCHDOWN)
        imgy = 1;
     else if (msg == MSG_TURNOVER)
        imgy = 2;
     }

