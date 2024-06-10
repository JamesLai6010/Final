#ifndef FLOOR3_H_INCLUDED
#define FLOOR3_H_INCLUDED
#include "element.h"
#include "charater.h"
#include "../scene/gamescene3.h" // for element label
/*
   [floor object]
*/
typedef struct _Floor3
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    int map_data[15][27];
} Floor3;

Elements *New_Floor3(int label);
void _Floor3_load_map(Floor3 *floor);
void Floor3_update(Elements *self);
void Floor3_interact(Elements *self, Elements *tar);
void Floor3_draw(Elements *self);
void Floor3_destory(Elements *self);

#endif