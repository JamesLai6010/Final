#ifndef SPEED_H_INCLUDED
#define SPEED_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "charater.h"
#include <stdbool.h>
/*
   [teleport object]
*/
typedef struct _Speed
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    bool activate; // If the teleport be activated
    bool dele;
    bool picked;
} Speed;
Elements *New_Speed(int label);
void Speed_update(Elements *self);
void Speed_interact(Elements *self, Elements *tar);
void Speed_draw(Elements *self);
void Speed_destory(Elements *self);

#endif
