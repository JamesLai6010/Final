#ifndef GAMESCENE2_H_INCLUDED
#define GAMESCENE2_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor2.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../element/healer.h"
#include "../element/trap.h"
#include "../element/jump.h"
#include "../element/speed.h"
#include "../element/slowtrap.h"
/*
   [game scene object]
*/
typedef enum EleType2
{
    Floor_L2,
    Teleport_L2,
    Tree_L2,
    Character_L2,
    Projectile_L2,
    Speed_L2,
    Healer_L2,
    Trap_L2,
    Jump_L2,
    SlowTrap_L2,
} EleType2;
typedef struct _GameScene2
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;
    double game_time;
    ALGIF_ANIMATION *heart_gif;    //心臟跳動
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;

} GameScene2;
Scene *New_GameScene2(int label);
void game_scene2_update(Scene *self);
void game_scene2_draw(Scene *self);
void game_scene2_destroy(Scene *self);

#endif
