#ifndef JUMP_H_INCLUDED
#define JUMP_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "charater.h"
#include <stdbool.h>
#include "../global.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct _Jump {
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    ALLEGRO_SAMPLE *mp3;
    bool activate;     // If the jump boost is activated
    bool dele;
    bool picked;
} Jump;

Elements *New_Jump(int label);
void Jump_update(Elements *self);
void Jump_interact(Elements *self, Elements *tar);
void Jump_draw(Elements *self);
void Jump_destroy(Elements *self);

#endif
