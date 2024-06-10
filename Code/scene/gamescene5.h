#ifndef GAMESCENE5_H_INCLUDED
#define GAMESCENE5_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor5.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [game scene object]
*/
typedef enum EleType5
{
    Floor_L5,
    Teleport_L5,
    Tree_L5,
    Character_L5,
    Projectile_L5,
    Speed_L5,
    Healer_L5
} EleType5;
typedef struct _GameScene5
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;
    double game_time;
    ALGIF_ANIMATION *heart_gif;    //心臟跳動
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;

} GameScene5;
Scene *New_GameScene5(int label);
void game_scene5_update(Scene *self);
void game_scene5_draw(Scene *self);
void game_scene5_destroy(Scene *self);

#endif
