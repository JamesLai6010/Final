#ifndef TRAP_H_INCLUDED
#define TRAP_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include <allegro5/allegro_audio.h>
#include "charater.h"
#include <stdbool.h>
#include <allegro5/allegro_acodec.h>

typedef struct _Trap {
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    ALLEGRO_SAMPLE *mp3;
    bool active;       // If the trap is activated
} Trap;

Elements *New_Trap(int label);
void Trap_update(Elements *self);
void Trap_interact(Elements *self, Elements *tar);
void Trap_draw(Elements *self);
void Trap_destroy(Elements *self);

#endif
