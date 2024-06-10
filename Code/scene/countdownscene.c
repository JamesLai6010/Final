#include "countdownscene.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>

/*
   [CountdownScene function]
*/
Scene *New_CountdownScene(int label)
{
    CountdownScene *pDerivedObj = (CountdownScene *)malloc(sizeof(CountdownScene));
    Scene *pObj = New_Scene(label);

    // 設定衍生對象成員
    //pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 90, 0);
    pDerivedObj->song = al_load_sample("assets/sound/countdown.mp3");
    pDerivedObj->background = al_load_bitmap("assets/image/countdown.jpg");
    pDerivedObj->font = al_load_ttf_font("assets/font/SuperMarioBros.ttf", 200, 0);

    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);

    pObj->pDerivedObj = pDerivedObj;

    pDerivedObj->countdown_time = 3.0; // 3秒倒數計時

    // 設定衍生對象函數
    pObj->Update = countdown_scene_update;
    pObj->Draw = countdown_scene_draw;
    pObj->Destroy = countdown_scene_destroy;

    return pObj;
}

void countdown_scene_update(Scene *self)
{
    CountdownScene *Obj = (CountdownScene *)(self->pDerivedObj);

    // 減少倒數時間
    Obj->countdown_time -= 1.0 / 60; // 假設60 FPS

    // 當倒數時間小於等於0時，切換場景
    if (Obj->countdown_time <= -0.5) {
        self->scene_end = true;
        chara_health = 100;
        game_time = 0;
        speed = false;
        jump_boost = false;
        chara_x = 0;
        chara_y = HEIGHT-140-160;
        speed_timer = 5;
        jump_timer = 5;
        slow_timer = 5;  // 設置減速時間
        slow = false;
        keys_collected = 0;
        window = 1;  // 下一個場景的代碼（例如1表示遊戲主場景）
    }
}

void countdown_scene_draw(Scene *self)
{
    CountdownScene *Obj = (CountdownScene *)(self->pDerivedObj);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    
    // 顯示倒數計時
    char countdown_text[10];
    sprintf(countdown_text, "%d", (int)ceil(Obj->countdown_time));
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), 960, 450, ALLEGRO_ALIGN_CENTER, countdown_text);

    al_play_sample_instance(Obj->sample_instance);
}

void countdown_scene_destroy(Scene *self)
{
    CountdownScene *Obj = (CountdownScene *)(self->pDerivedObj);
    if (Obj->font) {
        al_destroy_font(Obj->font);
    }
    if (Obj->background) {
        al_destroy_bitmap(Obj->background);
    }
    if (Obj->song) {
        al_destroy_sample(Obj->song);
    }
    if (Obj->sample_instance) {
        al_destroy_sample_instance(Obj->sample_instance);
    }
    free(Obj);
    free(self);
}
