#ifndef ABOUTSCENE_H_INCLUDED
#define ABOUTSCENE_H_INCLUDED

#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

typedef struct _AboutScene {
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
} AboutScene;

Scene *New_AboutScene(int label);
void about_scene_update(Scene *self);
void about_scene_draw(Scene *self);
void about_scene_destroy(Scene *self);

#endif
