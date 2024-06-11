#include <allegro5/allegro_primitives.h>
#include "creditscene.h"
#include <stdbool.h>

/*
   [CreditScene function]
*/
Scene *New_CreditScene(int label)
{
    CreditScene *pDerivedObj = (CreditScene *)malloc(sizeof(CreditScene));
    Scene *pObj = New_Scene(label);

    // 設定衍生對象成員
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);

    pDerivedObj->song = al_load_sample("assets/sound/credits.mp3");

    pDerivedObj->background = al_load_bitmap("assets/image/credit.png");

    pDerivedObj->click_sound = al_load_sample("assets/sound/click.mp3");

    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);

    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);

    pObj->pDerivedObj = pDerivedObj;

    // 設定衍生對象函數
    pObj->Update = credit_scene_update;
    pObj->Draw = credit_scene_draw;
    pObj->Destroy = credit_scene_destroy;

    return pObj;
}

void credit_scene_update(Scene *self)
{   
    printf("%f  %f\n",mouse.x,mouse.y);
    if (mouse_state[1] && mouse.x >= 1390 && mouse.x <= 1558 && mouse.y >= 780 && mouse.y <= 830) {
        al_play_sample(((CreditScene *)(self->pDerivedObj))->click_sound, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // 播放點擊聲音
        al_rest(0.15);
        self->scene_end = true;
        window = 0;  //menu
    }
}

void credit_scene_draw(Scene *self)
{
    CreditScene *Obj = (CreditScene *)(self->pDerivedObj);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    al_play_sample_instance(Obj->sample_instance);
}

void credit_scene_destroy(Scene *self)
{
    CreditScene *Obj = (CreditScene *)(self->pDerivedObj);
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
    if (Obj->click_sound) {
        al_destroy_sample(Obj->click_sound);
    }
    free(Obj);
    free(self);
}
