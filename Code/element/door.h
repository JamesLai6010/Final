#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // 為了 element label
#include "charater.h"
#include <stdbool.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct _Door {
    int x, y;          // 圖片的位置
    int width, height; // 圖片的寬度和高度
    ALLEGRO_BITMAP *img1;
    ALLEGRO_BITMAP *img2;
    ALLEGRO_SAMPLE *mp3;
    bool isOpen; // 判斷門是否打開
    bool dele;
} Door;

Elements *New_Door(int label, int x, int y);
void Door_update(Elements *self);
void Door_interact(Elements *self, Elements *tar);
void Door_draw(Elements *self);
void Door_destroy(Elements *self);

#endif
