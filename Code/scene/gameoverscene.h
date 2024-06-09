// gameoverscene.h
#ifndef GAMEOVERSCENE_H_INCLUDED
#define GAMEOVERSCENE_H_INCLUDED

#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

typedef struct _GameOverScene
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE *click_sound;
    ALLEGRO_SAMPLE *song;
} GameOverScene;

Scene *New_GameOverScene(int label);
void game_over_update(Scene *self);
void game_over_draw(Scene *self);
void game_over_destroy(Scene *self);

#endif // GAMEOVERSCENE_H_INCLUDED
