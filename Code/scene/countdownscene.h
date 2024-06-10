#ifndef COUNTDOWNSCENE_H_INCLUDED
#define COUNTDOWNSCENE_H_INCLUDED

#include "scene.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "../global.h"

typedef struct _CountdownScene
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    double countdown_time;
} CountdownScene;

Scene *New_CountdownScene(int label);
void countdown_scene_update(Scene *self);
void countdown_scene_draw(Scene *self);
void countdown_scene_destroy(Scene *self);

#endif // COUNTDOWNSCENE_H_INCLUDED
