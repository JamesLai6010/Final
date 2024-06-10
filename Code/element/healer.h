#ifndef HEALER_H_INCLUDED
#define HEALER_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "charater.h"
#include <stdbool.h>

/*
   [heal object]
*/
typedef struct _Heal
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    bool activate; // If the heal item is activated
    bool dele;
    bool picked;
} Heal;

Elements *New_Heal(int label);
void Heal_update(Elements *self);
void Heal_interact(Elements *self, Elements *tar);
void Heal_draw(Elements *self);
void Heal_destory(Elements *self);

#endif
