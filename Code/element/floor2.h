#ifndef FLOOR2_H_INCLUDED
#define FLOOR2_H_INCLUDED
#include "element.h"
#include "charater.h"
#include "../scene/gamescene2.h" // for element label
/*
   [floor object]
*/
typedef struct _Floor2
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    int map_data[15][27];
} Floor2;

Elements *New_Floor2(int label);
void _Floor2_load_map(Floor2 *floor);
void Floor2_update(Elements *self);
void Floor2_interact(Elements *self, Elements *tar);
void Floor2_draw(Elements *self);
void Floor2_destory(Elements *self);

#endif