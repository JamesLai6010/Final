#include "charater.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>

#define GRAVITY 1        //跳躍重力和跳躍高度
#define JUMP_STRENGTH -15 

/*
   [Character function]
*/
Elements *New_Character(int label)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[3][10] = {"stop", "move", "attack"};
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 300;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 60; // 假設地面高度為 HEIGHT - 60
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pDerivedObj->jump_speed = 0;
    pDerivedObj->is_jumping = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}


void Character_update(Elements *self) {
    Character *chara = ((Character *)(self->pDerivedObj));
    //如果有跳就去做重力
    if (chara->is_jumping) {
        chara->jump_speed += GRAVITY;
        _Character_update_position(self, 0, chara->jump_speed);
        if (chara->y + chara->height >= HEIGHT - 60) { // 地面目前是人身高-60後續要跟著改
            chara->y = HEIGHT - chara->height - 60;
            chara->is_jumping = false;
            chara->state = STOP;
        }
    } else {
        if (key_state[ALLEGRO_KEY_SPACE] && !chara->is_jumping) {
            chara->is_jumping = true;
            chara->jump_speed = JUMP_STRENGTH;
            chara->state = JUMP;
        }
    }

    if (chara->state == STOP || chara->state == MOVE) {
        if (key_state[ALLEGRO_KEY_SPACE] && !chara->is_jumping) {
            chara->is_jumping = true;
            chara->jump_speed = JUMP_STRENGTH;
            chara->state = JUMP;
        } else if (key_state[ALLEGRO_KEY_A]) {
            chara->dir = false;
            chara->state = MOVE;
            _Character_update_position(self, -5, 0);
        } else if (key_state[ALLEGRO_KEY_D]) {
            chara->dir = true;
            chara->state = MOVE;
            _Character_update_position(self, 5, 0);
        } else {
            chara->state = STOP;
        }
    } else if (chara->state == ATK) {
        if (chara->gif_status[chara->state]->done) {
            chara->state = STOP;
            chara->new_proj = false;
        }
        if (chara->gif_status[ATK]->display_index == 2 && !chara->new_proj) {
            Elements *pro;
            if (chara->dir) {
                pro = New_Projectile(Projectile_L,
                                     chara->x + chara->width - 100,
                                     chara->y + 10,
                                     5);
            } else {
                pro = New_Projectile(Projectile_L,
                                     chara->x - 50,
                                     chara->y + 10,
                                     -5);
            }
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }
    }
}

void Character_draw(Elements *self) {
    Character *chara = ((Character *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame) {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (chara->state == ATK && chara->gif_status[chara->state]->display_index == 2) {
        al_play_sample_instance(chara->atk_Sound);
    }
}

void Character_destory(Elements *self) {
    Character *Obj = ((Character *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Character_update_position(Elements *self, int dx, int dy) {
    Character *chara = ((Character *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Character_interact(Elements *self, Elements *tar) {
    Character *chara = (Character *)(self->pDerivedObj);
    if (tar->label == Floor_L) {
        Floor *floor = (Floor *)(tar->pDerivedObj);
        if (chara->y + chara->height >= floor->y) {
            chara->y = floor->y - chara->height;
            chara->is_jumping = false;
            chara->state = STOP;
        }
    }
}
