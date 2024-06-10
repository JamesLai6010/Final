#ifndef VICTORYSCENE_H_INCLUDED
#define VICTORYSCENE_H_INCLUDED

#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

typedef struct _VictoryScene
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE *click_sound;
    ALLEGRO_SAMPLE *song;
} VictoryScene;

Scene *New_VictoryScene(int label);
void victory_update(Scene *self);
void victory_draw(Scene *self);
void victory_destroy(Scene *self);

#endif // VICTORYSCENE_H_INCLUDED
