#include "charater.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
#include "floor.h"
#include <allegro5/allegro_primitives.h>

#define true 1
#define false 0

#define GRAVITY 1        //跳躍重力和跳躍高度
#define JUMP_STRENGTH -30
#define FALL_SPEED 15
/*
   [Character function]
*/
void Character_on_Floor(Elements *self);
void load_map_data();

Elements *New_Character(int label)
{
    bool map_loaded = false;
    load_map_data();
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[2][10] = {"stop", "move"};
    for (int i = 0; i < 2; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // Load the heart gif
    pDerivedObj->heart_gif = algif_load_animation("assets/image/heart.gif");
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    //health
    pDerivedObj->max_health = 100.0;
    pDerivedObj->health = 100.0;

    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 100;
    pDerivedObj->y = HEIGHT - 140 - pDerivedObj->height; // 假設地面高度為 HEIGHT - 60
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->game_over = false;
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


int stop_y;
int next_stop_y,last_stop_y;
int map_data[15][27];
int left_speed,right_speed;
float section;
int sec;
int X;

void Character_update(Elements *self) {
    Character *chara = ((Character *)(self->pDerivedObj));
    Character_on_Floor(self);  // 去算地面高度
    
    CheckDeath(self); // 檢查角色是否死亡
    // 如果有跳就去做重力
    //printf("%d %d  ", X,sec); // 地面y高度
    
    if (chara->is_jumping) {
        chara->jump_speed += GRAVITY;
        _Character_update_position(self, 0, chara->jump_speed);
        if ((chara->y + chara->height >= stop_y) && (chara->y + chara->height < stop_y+50)) {
            chara->y = stop_y - chara->height;
            chara->is_jumping = false;
            chara->state = STOP;
        }
    } else if (chara->y + chara->height < stop_y) {
        chara->jump_speed += GRAVITY; // 加上重力
        _Character_update_position(self, 0, chara->jump_speed);
        if (chara->y + chara->height >= stop_y) {
            chara->y = stop_y - chara->height;
            chara->jump_speed = 0; // 重置跳躍速度
        }
    } else if (chara->y+20 >= stop_y+70) {
        chara->jump_speed += GRAVITY; // 加上重力
        _Character_update_position(self, 0, chara->jump_speed);
    
    } else {
        chara->jump_speed = 0; // 重置跳躍速度
    }
    bool on_ground = (chara->y + chara->height >= stop_y) && (chara->y + chara->height < stop_y + 50);
    //printf("%d\n",on_ground);
    if (key_state[ALLEGRO_KEY_W] && !chara->is_jumping && on_ground) {
        chara->is_jumping = true;
        chara->jump_speed = JUMP_STRENGTH;
        chara->state = JUMP;
    }

    
    if (key_state[ALLEGRO_KEY_S] && chara->is_jumping) {
        chara->jump_speed += FALL_SPEED;
        chara->state = STOP;
        chara->is_jumping = false;
    }

    if (chara->state == STOP || chara->state == MOVE) {
        if (key_state[ALLEGRO_KEY_W] && !chara->is_jumping  && on_ground) {
            chara->is_jumping = true;
            chara->jump_speed = JUMP_STRENGTH;
            chara->state = JUMP;
        } else if (key_state[ALLEGRO_KEY_A]) {
            chara->dir = false;
            chara->state = MOVE;
            _Character_update_position(self, left_speed, 0);
        } else if (key_state[ALLEGRO_KEY_D]) {
            chara->dir = true;
            chara->state = MOVE;
            _Character_update_position(self, right_speed, 0);
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
    } else if (chara->state == JUMP) {
        if (key_state[ALLEGRO_KEY_A]) {
            chara->dir = false;
            chara->state = MOVE;
            _Character_update_position(self, left_speed, 0);
        } else if (key_state[ALLEGRO_KEY_D]) {
            chara->dir = true;
            chara->state = MOVE;
            _Character_update_position(self, right_speed, 0);
        }
    }
}

void Character_draw(Elements *self) {
    Character *chara = ((Character *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[1], al_get_time());
    if (frame) {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (chara->state == ATK && chara->gif_status[chara->state]->display_index == 2) {
        al_play_sample_instance(chara->atk_Sound);
    }
    // 繪製 heart GIF
    ALLEGRO_BITMAP *heart_frame = algif_get_bitmap(chara->heart_gif, al_get_time());
    if (heart_frame) {
        int heart_x = 1450;  // 替換為 heart gif 的 x 坐標
        int heart_y = 5;  // 替換為 heart gif 的 y 坐標
        al_draw_bitmap(heart_frame, heart_x, heart_y, 0);
    }
    
    // 繪製血條
    draw_health_bar(chara);
}
//血條邏輯
void draw_health_bar(Character *chara) {
    // 繪製血條背景
    float bar_width = 300; // 血條的寬度
    float bar_height = 40; // 血條的高度
    float health_percentage = chara->health / chara->max_health;
    float health_bar_width = bar_width * health_percentage;
    
    // 血條背景方框（灰色）
    al_draw_filled_rectangle(1550, 30, 1550 + bar_width, 30 + bar_height, al_map_rgb(128, 128, 128));

    // 當前健康狀態的血條（紅色）
    al_draw_filled_rectangle(1550, 30, 1550 + health_bar_width, 30 + bar_height, al_map_rgb(255, 20, 20));
    
    // 血條邊框（黑色）
    al_draw_rectangle(1550, 30, 1550 + bar_width, 30 + bar_height, al_map_rgb(0, 0, 0), 4.0);
}


void Character_destory(Elements *self) {
    Character *Obj = ((Character *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 2; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    algif_destroy_animation(Obj->heart_gif); // Destroy the heart gif
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



void Character_interact(Elements *self, Elements *tar) { }

bool map_loaded = false;

void load_map_data() {
    if (!map_loaded) {
        FILE *data = fopen("assets/map/gamescene_map.txt", "r");
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 27; j++) {
                fscanf(data, "%d", &map_data[i][j]);
            }
        }
        fclose(data);
        map_loaded = true;
    }
}

//讀取地面高度、阻擋等
void Character_on_Floor(Elements *self) {
    Character *chara = (Character *)(self->pDerivedObj);
    int floor_y[100] = {0};  //紀錄floor_y[第幾直排] = 有地板的橫排

    for (int i = 0; i < 27; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (map_data[j][i] == 1) {
                floor_y[i] = j;
                break;
            }
            if (j == 14) floor_y[i] = 30;
            
        }
    }

    int per_width = 70;
    int per_height = 70;
    int Y = chara->y + chara->height;  //角色腳底的y
    X = chara->x + chara->width - 15;  //角色右下角的x
    
    section = X/per_width;
    sec = section;
    //現在的地面高度
    if (sec < 27 && sec > 0)  stop_y = floor_y[sec-1]*per_height;
    else stop_y = floor_y[0]*per_height;
    //下個block的地面高度
    if (sec < 27)  next_stop_y = floor_y[sec]*per_height;
    else next_stop_y = stop_y;
    //上個block的地面高度
    if (sec > 1)  last_stop_y = floor_y[sec-2]*per_height;
    else last_stop_y = stop_y;
    
    if (chara->dir == true) {    //向右去檢查下一個
        if (((chara->y+20 >= next_stop_y && chara->y+20 < next_stop_y+70) || (Y > next_stop_y && Y < next_stop_y+70)) && (X <= (sec+1)*70 && X > (sec+1)*70-50)) { //頭頂y在下一個地板的y之間
            
            right_speed = 0;
        } else right_speed = 5;
    } 
    if (chara->dir == false) {
        if (((chara->y+20 >= last_stop_y && chara->y+20 < last_stop_y+70) || (Y > last_stop_y && Y < last_stop_y+70)) && (X >= (sec)*70+20 && X < (sec)*70+50)) {
            left_speed = 0;
        } else left_speed = -5;
    }
    
    return;
}

void CheckDeath(Elements *self) {
    Character *chara = ((Character *)(self->pDerivedObj));

    // 檢查 y 座標是否超過最大值 or 沒血了
    if (chara->y >= 1080-70 || chara->health <= 0) {
        chara->game_over = true; 
    } else chara -> game_over = false;
}