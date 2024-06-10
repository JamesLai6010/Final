#include "gamescene4.h"
#include <stdlib.h>
#include <time.h>  
/*
   [GameScene function]
*/
bool registed;

Scene *New_GameScene4(int label)
{
    registed = false;
    game_over = 0;
    printf("GameScene4 creating\n");
    GameScene4 *pDerivedObj = (GameScene4 *)malloc(sizeof(GameScene4));
    Scene *pObj = New_Scene(label);
    // font
    pDerivedObj->font = al_load_ttf_font("assets/font/SuperMarioBros.ttf", 50, 0);
    pDerivedObj->game_time = 0; // 初始化時間
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/back.jpg");
    pDerivedObj->heart_gif = algif_load_animation("assets/image/heart.gif");
    pDerivedObj->song = al_load_sample("assets/sound/gamescene.mp3");
    
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Floor4(Floor_L4));
    //_Register_elements(pObj, New_Teleport(Teleport_L));
    //_Register_elements(pObj, New_Tree(Tree_L)); //先取消這些東西 之後改成道具 陷阱 傳送
    _Register_elements(pObj, New_Character(Character_L4));
    //_Register_elements(pObj, New_Speed(Speed_L4));
    //_Register_elements(pObj, New_Heal(Healer_L));
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.5);

    // setting derived object function
    pObj->Update = game_scene4_update;
    pObj->Draw = game_scene4_draw;
    pObj->Destroy = game_scene4_destroy;
    return pObj;
}
void game_scene4_update(Scene *self)
{
    //GameScene2 *gs = ((GameScene2 *)(self->pDerivedObj));
    if (!registed) {
        int k1 = 0;
        int k2 = 0;
        int k3 = 0;
        int k4 = 0;
        int k5 = 0;
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 27; j++) {
                if (map_data[i][j] == 2) {
                    _Register_elements(self, New_Speed(Speed_L4+k1, j*70, i*70));
                    k1++;
                } else if (map_data[i][j] == 3) {
                    _Register_elements(self, New_Heal(Healer_L4+k2, j*70, i*70));
                    k2++;
                } else if (map_data[i][j] == 4) {
                    _Register_elements(self, New_Jump(Jump_L4+k3, j*70, i*70));
                    k3++;
                } else if (map_data[i][j] == 5) {
                    _Register_elements(self, New_Trap(Trap_L4+k4, j*70, i*70));
                    k4++;
                } else if (map_data[i][j] == 6) {
                    _Register_elements(self, New_SlowTrap(SlowTrap_L4+k5, j*70, i*70));
                    k5++;
                }
            }
        }
        registed = true;
    }
    // 隕石生成邏輯
    meteor_spawn_timer++;
    int k0 = 0;
    if (meteor_spawn_timer >= next_meteor_time && k0 <= 30) {
        _Register_elements(self, New_Meteor(Meteor_L+k0, 0,0));
        k0++;
        meteor_spawn_timer = 0;
        if (window == 1) next_meteor_time = rand() % 200; // 隨機生成下一次隕石生成時間
        else if (window == 4) next_meteor_time = rand() % 180;
        else if (window == 6) next_meteor_time = rand() % 150;
        else if (window == 7) next_meteor_time = rand() % 100;
        else if (window == 8) next_meteor_time = rand() % 60;
    }
    key_spawn_timer++;
    int k6 = 0;
    if (key_spawn_timer >= next_key_time && k6 <= 9) {
        _Register_elements(self, New_Key(Key_L+k6, 0, 0));
        k6++;
        key_spawn_timer = 0;
    }
    // update every element
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->label == Character_L4)
        {
            Character *chara = (Character *)(ele->pDerivedObj);
            chara->current_map = 3;
            if(chara->x < -70){       //身體一半在牆內
                self->scene_end = true;
                chara_x = 1800;
                window = 6;
                printf("Change to scene 3\n");
                return;
            }
            if((chara->x >= 1850)){       //身體一半在牆內
                self->scene_end = true;
                chara_x = -50;
                window = 8;
                printf("Change to scene 5\n");
                return;
            }
        }
    }
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
    }
    if (game_over) {
        end_time = game_time;
        self->scene_end = true;
        window = 5;
        printf("Change to GameOverScene\n");
    }
    // 如果角色沒有死亡，更新遊戲時間
    if (!game_over) {
        game_time += 1.0 / 60; // 60 FPS + 1s
    } 
    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
    

}
void game_scene4_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene4 *gs = ((GameScene4 *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
    // show_time
    int minutes = (int)game_time / 60;
    int seconds = (int)game_time % 60;
    int speed_min = (int)speed_timer / 60;
    int speed_sec = (int)speed_timer % 60;
    int jump_min = (int)jump_timer / 60;
    int jump_sec = (int)jump_timer % 60;
    int slow_min = (int)slow_timer / 60;
    int slow_sec = (int)slow_timer % 60;
    char time_text[50],speed_time_text[50],jump_time_text[50],slow_time_text[50],key_text[50];
    sprintf(time_text, "Time: %02d:%02d", minutes, seconds);
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 40, 30, ALLEGRO_ALIGN_LEFT, time_text);
    if (speed) {
        sprintf(speed_time_text, "Speeded: %02d:%02d", speed_min, speed_sec);
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), 40, 80, ALLEGRO_ALIGN_LEFT, speed_time_text);
    }
    if (jump_boost) {
        sprintf(jump_time_text, "Jump Boosted: %02d:%02d", jump_min, jump_sec);
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), 40, 130, ALLEGRO_ALIGN_LEFT, jump_time_text);
    }
    if (slow) {
        sprintf(slow_time_text, "Slowed: %02d:%02d", slow_min, slow_sec);
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), 40, 180, ALLEGRO_ALIGN_LEFT, slow_time_text);
    }
    sprintf(key_text, "KEY: %d", keys_collected);
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 1600, 100, ALLEGRO_ALIGN_LEFT, key_text);
    ALLEGRO_BITMAP *heart_frame = algif_get_bitmap(gs->heart_gif, al_get_time());
    if (heart_frame) {
        int heart_x = 1450;  // 替換為 heart gif 的 x 坐標
        int heart_y = 5;  // 替換為 heart gif 的 y 坐標
        al_draw_bitmap(heart_frame, heart_x, heart_y, 0);
    }
    al_play_sample_instance(gs->sample_instance);
}

void game_scene4_destroy(Scene *self)
{
    printf("gameScene4 destroying\n");
    GameScene4 *Obj = ((GameScene4 *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    al_destroy_font(Obj->font);
    algif_destroy_animation(Obj->heart_gif);
    al_destroy_sample_instance(Obj->sample_instance);
    al_destroy_sample(Obj->song);
    free(Obj);
    free(self);
}