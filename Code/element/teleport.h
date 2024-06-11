#ifndef TELEPORT_H_INCLUDED
#define TELEPORT_H_INCLUDED
#include "element.h"
#include "../scene/gamescene5.h" // for element label
#include "charater.h"
#include <stdbool.h>
/*
   [teleport object]
*/
typedef struct _Teleport
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    bool activate; // If the teleport be activated
} Teleport;
Elements *New_Teleport(int label, int x, int y);
void Teleport_update(Elements *self);
void Teleport_interact(Elements *self, Elements *tar);
void Teleport_draw(Elements *self);
void Teleport_destory(Elements *self);

#endif