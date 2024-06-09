#ifndef CHARATER_H_INCLUDED
#define CHARATER_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>

/*
   [character object]
*/
typedef enum CharacterType {
    STOP = 0,
    MOVE,
    ATK,
    JUMP
} CharacterType;

typedef struct _Character {
    int x, y;
    int width, height;              // The width and height of image
    bool dir;                       // True: face to right, false: face to left
    int state;                      // The state of character
    ALGIF_ANIMATION *gif_status[3]; // Gif for each state. 0: stop, 1: move, 2: attack, 3: jump
    ALGIF_ANIMATION *heart_gif;    //心臟跳動
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;       // Counting the time of animation
    int anime_time;  // Indicate how long the animation
    bool new_proj;
    Shape *hitbox;   // The hitbox of object
    int jump_speed;  // Jump speed
    bool is_jumping; // Is the character jumping
    float max_health;
    float health;
} Character;

Elements *New_Character(int label);
void _Character_update_position(Elements *self, int dx, int dy);
void Character_update(Elements *self);
void Character_interact(Elements *self, Elements *target);
void Character_draw(Elements *self);
void Character_destory(Elements *self);
void draw_health_bar(Character *chara);

#endif