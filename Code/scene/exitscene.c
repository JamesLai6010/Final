#include <allegro5/allegro_primitives.h>
#include "exitscene.h"
#include <stdbool.h>

/*
   [ExitScene function]
*/
Scene *New_ExitScene(int label)
{
    ExitScene *pDerivedObj = (ExitScene *)malloc(sizeof(ExitScene));
    Scene *pObj = New_Scene(label);

    // 設定衍生對象成員
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);

    pDerivedObj->song = al_load_sample("assets/sound/exit.mp3");

    pDerivedObj->background = al_load_bitmap("assets/image/exit.png");

    pDerivedObj->click_sound = al_load_sample("assets/sound/click.mp3");

    pDerivedObj->exit_mp3 = al_load_sample("assets/sound/god.mp3");
    pDerivedObj->exit_gif = algif_load_animation("assets/image/god.gif");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);

    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);

    pObj->pDerivedObj = pDerivedObj;

    // 設定衍生對象函數
    pObj->Update = exit_scene_update;
    pObj->Draw = exit_scene_draw;
    pObj->Destroy = exit_scene_destroy;

    return pObj;
}

void exit_scene_update(Scene *self)
{
    //printf("%f  %f\n",mouse.x,mouse.y);
    if (mouse_state[1] && mouse.x >= 1233 && mouse.x <= 1356 && mouse.y >= 600 && mouse.y <= 674) //NO
    {   
        al_play_sample(((ExitScene *)(self->pDerivedObj))->click_sound, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // 播放點擊聲音
        al_rest(0.15);
        self->scene_end = true;
        window = 0;
    } else if (mouse_state[1] && mouse.x >= 513 && mouse.x <= 704 && mouse.y >= 598 && mouse.y <= 704) 
    {   //YES
        al_play_sample(((ExitScene *)(self->pDerivedObj))->click_sound, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // 播放點擊聲音
        al_rest(0.15);
        al_play_sample(((ExitScene *)(self->pDerivedObj))->exit_mp3, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        double start_time = al_get_time();
        double end_time = start_time + 7.0;
        while (al_get_time() < end_time) {

            // 绘制GIF动画
            ALLEGRO_BITMAP *gif_frame = algif_get_bitmap(((ExitScene *)(self->pDerivedObj))->exit_gif, al_get_time());
            if (gif_frame) {
                al_draw_bitmap(gif_frame, 660, 371, 0);
            }

            al_flip_display();
            al_rest(0.016); // 每帧延迟约 16 毫秒
        }
        exit(0);
    }
    return;
}

void exit_scene_draw(Scene *self)
{
    ExitScene *Obj = (ExitScene *)(self->pDerivedObj);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    al_play_sample_instance(Obj->sample_instance);
}

void exit_scene_destroy(Scene *self)
{
    ExitScene *Obj = (ExitScene *)(self->pDerivedObj);
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
    if (Obj->click_sound) { // 銷毀點擊聲音
        al_destroy_sample(Obj->click_sound);
    }
    if (Obj->exit_mp3) {
        al_destroy_sample(Obj->exit_mp3);
    }
    if (Obj->exit_gif) {
        algif_destroy_animation(Obj->exit_gif);
    }
    free(Obj);
    free(self);
}
