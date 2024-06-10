#include "global.h"
#include "shapes/Shape.h"
#include <stdbool.h>
// variables for global usage
const double FPS = 60.0;
const int WIDTH = 1890;
const int HEIGHT = 1050;
int window = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
Point mouse;
bool debug_mode = true;
double end_time = 0;
double game_time = 0;          //time
bool game_over = false;
int map_data[15][27] = {0};
int chara_x = 0;               //x
int chara_y = HEIGHT-140-160;  //y
float chara_health = 100;      //health

int immortal = 1;
bool speed = false;
bool heal = false;
bool jump = false;
float speed_timer = 5.0;
bool jump_boost = false;
float jump_timer = 3.0;
float slow_timer = 5;  // 設置減速時間
bool slow = false;
int meteor_fall_speed = 5;
int meteor_spawn_timer = 0;
int next_meteor_time = 0;
int keys_collected = 0;
int key_spawn_timer = 0;
int next_key_time = 240;
bool finish = false;
//int speed_x = 0;
//int speed_y = 0;