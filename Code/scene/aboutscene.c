#include <allegro5/allegro_primitives.h>
#include "aboutscene.h"
#include <stdbool.h>

/*
   [AboutScene function]
*/
Scene *New_AboutScene(int label)
{
    AboutScene *pDerivedObj = (AboutScene *)malloc(sizeof(AboutScene));
    Scene *pObj = New_Scene(label);

    // 設定衍生對象成員
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    if (!pDerivedObj->font) {
        fprintf(stderr, "Failed to load font!\n");
        exit(1);
    }

    pDerivedObj->song = al_load_sample("assets/sound/about.mp3");
    if (!pDerivedObj->song) {
        fprintf(stderr, "Failed to load sound!\n");
        exit(1);
    }

    pDerivedObj->background = al_load_bitmap("assets/image/about.png");
    if (!pDerivedObj->background) {
        fprintf(stderr, "Failed to load background image!\n");
        exit(1);
    }

    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    if (!pDerivedObj->sample_instance) {
        fprintf(stderr, "Failed to create sample instance!\n");
        exit(1);
    }
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);

    pObj->pDerivedObj = pDerivedObj;

    // 設定衍生對象函數
    pObj->Update = about_scene_update;
    pObj->Draw = about_scene_draw;
    pObj->Destroy = about_scene_destroy;

    return pObj;
}

void about_scene_update(Scene *self)
{
    // 處理事件，例如按下 ESC 鍵返回菜單
    if (key_state[ALLEGRO_KEY_ESCAPE]) {
        self->scene_end = true;
        window = 0;  // 假設 0 是菜單窗口
    }
}

void about_scene_draw(Scene *self)
{
    AboutScene *Obj = (AboutScene *)(self->pDerivedObj);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    al_play_sample_instance(Obj->sample_instance);
}

void about_scene_destroy(Scene *self)
{
    AboutScene *Obj = (AboutScene *)(self->pDerivedObj);
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
