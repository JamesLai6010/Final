#include <allegro5/allegro_primitives.h>
#include "menu.h"
#include <stdbool.h>
/*
   [Menu function]
*/
Scene *New_Menu(int label)
{
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/mario_menu.mp3");
    // load image
    pDerivedObj->menu = al_load_bitmap("assets/image/menu.png");
    
    pDerivedObj->click_sound = al_load_sample("assets/sound/click.mp3");

    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.05);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}
void menu_update(Scene *self)
{
    printf("%f  %f\n",mouse.x,mouse.y);
    //left click
    if (mouse_state[1] && mouse.x >= 813 && mouse.x <= 1112 && mouse.y >= 497 && mouse.y <= 574) //start
    {
        al_play_sample(((Menu *)(self->pDerivedObj))->click_sound, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // 播放點擊聲音
        al_rest(0.15);
        self->scene_end = true;
        window = 10;
    } else if (mouse_state[1] && mouse.x >= 813 && mouse.x <= 1112 && mouse.y >= 652 && mouse.y <= 730) //about
    {   
        al_play_sample(((Menu *)(self->pDerivedObj))->click_sound, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // 播放點擊聲音
        al_rest(0.15);
        self->scene_end = true;
        window = 2;
    } else if (mouse_state[1] && mouse.x >= 860 && mouse.x <= 1061 && mouse.y >= 810 && mouse.y <= 889)
    {
        al_play_sample(((Menu *)(self->pDerivedObj))->click_sound, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // 播放點擊聲音
        al_rest(0.1);
        self->scene_end = true;
        window = 3;
    } else if (mouse_state[1] && mouse.x >= 1540 && mouse.x <= 1830 && mouse.y >= 950 && mouse.y <= 1010) {
        al_play_sample(((Menu *)(self->pDerivedObj))->click_sound, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // 播放點擊聲音
        al_rest(0.1);
        self->scene_end = true;
        window = 12;  //menu
    }
    return;
}
void menu_draw(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    // 先繪製背景
    al_draw_bitmap(Obj->menu, 0, 0, 0);
    // 再繪製其他元素
    
    al_play_sample_instance(Obj->sample_instance);
}

void menu_destroy(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    if (Obj->click_sound) { // 銷毀點擊聲音
        al_destroy_sample(Obj->click_sound);
    }
    free(Obj);
    free(self);
}
