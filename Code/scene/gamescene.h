#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
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
/*
   [game scene object]
*/
typedef enum EleType
{
    Floor_L,
    Teleport_L,
    Tree_L,
    Character_L,
    Projectile_L,
    Speed_L = 11, 
    Healer_L = 21,
    Trap_L = 31,
    Jump_L = 41,
    SlowTrap_L = 51,
} EleType;
typedef struct _GameScene
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;
    double game_time;
    bool game_over;
    ALGIF_ANIMATION *heart_gif;    //心臟跳動
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);

#endif