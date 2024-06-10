#ifndef SLOWTRAP_H_INCLUDED
#define SLOWTRAP_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include <allegro5/allegro_audio.h>
#include "charater.h"
#include <stdbool.h>
#include <allegro5/allegro_acodec.h>

typedef struct _SlowTrap {
    ALLEGRO_BITMAP *img;
    int width, height;
    bool picked;
    float x, y;
    bool activate;
} SlowTrap;

Elements *New_SlowTrap(int label);
void SlowTrap_update(Elements *self);
void SlowTrap_interact(Elements *self, Elements *tar);
void SlowTrap_draw(Elements *self);
void SlowTrap_destroy(Elements *self);

#endif
