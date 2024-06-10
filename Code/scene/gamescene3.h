#ifndef GAMESCENE3_H_INCLUDED
#define GAMESCENE3_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor3.h"
#include "../element/speed.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../global.h"
#include "../element/healer.h"
#include "../element/trap.h"
#include "../element/jump.h"
#include "../element/slowtrap.h"
#include "../element/meteor.h"
/*
   [game scene object]
*/
typedef enum EleType3
{
    Floor_L3,
    Teleport_L3,
    Tree_L3,
    Character_L3,
    Projectile_L3,
    Speed_L3 = 11,
    Healer_L3 = 21,
    Trap_L3 = 31,
    Jump_L3 = 41,
    SlowTrap_L3 = 51,
    Meteor_L3 = 61
} EleType3;
typedef struct _GameScene3
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;
    double game_time;
    ALGIF_ANIMATION *heart_gif;    //心臟跳動
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;

} GameScene3;
Scene *New_GameScene3(int label);
void game_scene3_update(Scene *self);
void game_scene3_draw(Scene *self);
void game_scene3_destroy(Scene *self);

#endif
