#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "charater.h"
#include <stdbool.h>
#include "../global.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct _Key {
    int x, y;          // 鑰匙的座標
    int width, height; // 鑰匙的寬度和高度
    ALLEGRO_BITMAP *img;
    ALLEGRO_SAMPLE *mp3;
    bool dele;
} Key;

Elements *New_Key(int label, int x, int y);
void Key_update(Elements *self);
void Key_interact(Elements *self, Elements *tar);
void Key_draw(Elements *self);
void Key_destroy(Elements *self);

#endif
