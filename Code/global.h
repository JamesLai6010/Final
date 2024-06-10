#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include <stdio.h>
#include <allegro5/allegro.h>
#define GAME_TERMINATE -1
#include "shapes/Point.h"
#define debug(x)                                                            \
    if (x)                                                                  \
    {                                                                       \
        printf("check at line number %d in file %s\n", __LINE__, __FILE__); \
    }
#define MAX_ELEMENT 100
#define min(x, y) ((x) > (y) ? (y) : (x))
#define max(x, y) ((x) < (y) ? (y) : (x))
// note that you can't assign initial value for extern variable!
extern const double FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern int window;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES];
extern Point mouse;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_TIMER *fps;
extern bool debug_mode;
extern double end_time;
extern bool game_over;
extern double game_time;
extern int map_data[15][27];
extern int chara_x;
extern int chara_y;
extern float chara_health;
extern int JUMP_STRENGTH;
extern int immortal;
extern bool speed;
extern bool heal;
extern bool jump_boost;
extern float speed_timer;
extern float jump_timer;
extern float slow_timer;
extern bool slow;
#endif
