#ifndef METEOR_H_INCLUDED
#define METEOR_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "charater.h"
#include <stdbool.h>
#include "../global.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct _Meteor {
    int x, y;          // 隕石的座標
    int width, height; // 隕石的寬度和高度
    ALLEGRO_BITMAP *img1;
    ALLEGRO_BITMAP *img2;
    ALLEGRO_SAMPLE *mp3;
    bool dele;
    int timer;         // 計時器
    bool showImg1;     // 當前顯示圖片的標誌
} Meteor;

Elements *New_Meteor(int label, int x, int y);
void Meteor_update(Elements *self);
void Meteor_interact(Elements *self, Elements *tar);
void Meteor_draw(Elements *self);
void Meteor_destroy(Elements *self);

#endif
