#ifndef __Game_H
#define __Game_H

#include "Player.h"

#define HOME    0
#define AWAY    1

#define SF      0
#define GB      1
#define DL      2

typedef struct
    {
    int runs, runyards;
    int passes, passyards, completions;
    int firstdowns, thirdconv, turnovers;
    } STATS;

typedef struct
    {
    PLAYER Player[11];
    BITMAP * PlayerBmp;

    int score;
    STATS GameStats;
    } TEAM;

typedef struct
    {
    float x, y;
    int thrown;
    fixed dir;
    } BALL;

extern TEAM Home, Away;
extern BALL Ball;

extern int possession;
extern int YardLine;
extern int Down;
extern int ToGo;

extern int GameSpeed;

extern PALETTE GamePalette;
extern BITMAP * Background;
extern BITMAP * buffer;
extern BITMAP * Messages;

void load_team(TEAM * t, int teamnum, int usepal);

// Intermissions //

void coin_toss(void);
void kick_off(void);
void half_time(void);
void end_game(void);

// Game time functions //

void game_loop(void);
void show_info(void);
void do_play(void);
void keep_game_speed(void);
void end_play(int playval);

// End play functions //

void turnover(void);
void firstdown(void);
void touchdown(void);

// Misc functions //

int convert_yardline(int y);

#endif
