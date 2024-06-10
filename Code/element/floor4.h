#ifndef FLOOR4_H_INCLUDED
#define FLOOR4_H_INCLUDED
#include "element.h"
#include "charater.h"
#include "../scene/gamescene4.h" // for element label
/*
   [floor object]
*/
typedef struct _Floor4
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    int map_data[15][27];
} Floor4;

Elements *New_Floor4(int label);
void _Floor4_load_map(Floor4 *floor);
void Floor4_update(Elements *self);
void Floor4_interact(Elements *self, Elements *tar);
void Floor4_draw(Elements *self);
void Floor4_destory(Elements *self);

#endif