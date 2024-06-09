#ifndef EXITSCENE_H_INCLUDED
#define EXITSCENE_H_INCLUDED

#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "../algif5/src/algif.h"

typedef struct _ExitScene {
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE *click_sound;
    ALLEGRO_SAMPLE *exit_mp3;
    ALGIF_ANIMATION *exit_gif;
} ExitScene;

Scene *New_ExitScene(int label);
void exit_scene_update(Scene *self);
void exit_scene_draw(Scene *self);
void exit_scene_destroy(Scene *self);

#endif