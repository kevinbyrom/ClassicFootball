#include <stdlib.h>
#include <time.h>
#include <Allegro.h>
#include "Display.h"
#include "Player.h"
#include "Game.h"


int main(void)
    {
    // Randomize the timer //

    srandom((int)time(NULL));


    // Initialize //

    allegro_init();
    install_keyboard();
    install_mouse();
    show_mouse(NULL);
    init_display();

    GameSpeed = 8;

    load_team(&Home, DL, 1);
    load_team(&Away, SF, 0);


    // Game loop //

    game_loop();


    // Exit allegro and the program //

    destroy_display();
    allegro_exit();

    return 1;
    }

