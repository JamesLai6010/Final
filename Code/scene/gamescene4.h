#ifndef GAMESCENE4_H_INCLUDED
#define GAMESCENE4_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor4.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [game scene object]
*/
typedef enum EleType4
{
    Floor_L4,
    Teleport_L4,
    Tree_L4,
    Character_L4,
    Projectile_L4,
    Speed_L4,
    Healer_L4
} EleType4;
typedef struct _GameScene4
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;
    double game_time;
    ALGIF_ANIMATION *heart_gif;    //心臟跳動
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;

} GameScene4;
Scene *New_GameScene4(int label);
void game_scene4_update(Scene *self);
void game_scene4_draw(Scene *self);
void game_scene4_destroy(Scene *self);

#endif
