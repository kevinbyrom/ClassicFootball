#include <Allegro.h>
#include "Input.h"
#include "Game.h"
#include "Player.h"


void wait_for_key(void)
     {
     delay(1000);
     clear_keybuf();
     while(!keypressed()){}
     clear_keybuf();
     }

