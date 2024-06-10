#ifndef FLOOR5_H_INCLUDED
#define FLOOR5_H_INCLUDED
#include "element.h"
#include "charater.h"
#include "../scene/gamescene5.h" // for element label
/*
   [floor object]
*/
typedef struct _Floor5
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    int map_data[15][27];
} Floor5;

Elements *New_Floor5(int label);
void _Floor5_load_map(Floor5 *floor);
void Floor5_update(Elements *self);
void Floor5_interact(Elements *self, Elements *tar);
void Floor5_draw(Elements *self);
void Floor5_destory(Elements *self);

#endif