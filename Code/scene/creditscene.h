#ifndef CREDITSCENE_H_INCLUDED
#define CREDITSCENE_H_INCLUDED

#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

typedef struct _CreditScene {
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE *click_sound;
} CreditScene;

Scene *New_CreditScene(int label);
void credit_scene_update(Scene *self);
void credit_scene_draw(Scene *self);
void credit_scene_destroy(Scene *self);

#endif // CREDITSCENE_H_INCLUDED
