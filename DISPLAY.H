#ifndef __Display_H
#define __Display_H

#define MSG_TURNOVER    0
#define MSG_TOUCHDOWN   1
#define MSG_FIRSTDOWN   2

BITMAP * buffer, * background;

void init_display(void);
void destroy_display(void);
void draw_screen(void);
void draw_info(void);
void create_background(void);
void draw_background(void);
void draw_message(int msg);

#endif
