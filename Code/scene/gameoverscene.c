// gameoverscene.c
#include <allegro5/allegro_primitives.h>
#include "gameoverscene.h"
#include "../global.h"



Scene *New_GameOverScene(int label)
{
    GameOverScene *pDerivedObj = (GameOverScene *)malloc(sizeof(GameOverScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/SuperMarioBros.ttf", 100, 0);
    pDerivedObj->background = al_load_bitmap("assets/image/gameover.jpg");
    pDerivedObj->click_sound = al_load_sample("assets/sound/click.mp3");
    pDerivedObj->song = al_load_sample("assets/sound/gameover.mp3");
    al_play_sample(((pDerivedObj)->song), 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_reserve_samples(20);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = game_over_update;
    pObj->Draw = game_over_draw;
    pObj->Destroy = game_over_destroy;
    return pObj;
}

void game_over_update(Scene *self)
{
    //printf("%lf %lf\n",mouse.x,mouse.y);
    if (mouse_state[1] && mouse.x >= 830 && mouse.x <= 900 && mouse.y >= 770 && mouse.y <= 795) { //yes
        al_play_sample(((GameOverScene *)(self->pDerivedObj))->click_sound, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // 播放點擊聲音
        al_rest(0.15);
        self->scene_end = true;
        window = 10;  //start
    } else if (mouse_state[1] && mouse.x >= 1040 && mouse.x <= 1090 && mouse.y >= 770 && mouse.y <= 795) { //no
        al_play_sample(((GameOverScene *)(self->pDerivedObj))->click_sound, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // 播放點擊聲音
        al_rest(0.15);
        self->scene_end = true;
        window = 0;  //menu
    }
    
    return;
}

void game_over_draw(Scene *self)
{
    GameOverScene *Obj = ((GameOverScene *)(self->pDerivedObj));
    // Draw the game over background
    al_draw_bitmap(Obj->background, 0, 0, 0);

    // Draw the end time
    char time_str[50];
    int min = (int)end_time / 60;
    int sec = (int)end_time % 60;
    sprintf(time_str, "End Time: %02d:%02d", min,sec);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), 980, 270, ALLEGRO_ALIGN_CENTER, time_str);
}

void game_over_destroy(Scene *self)
{
    GameOverScene *Obj = ((GameOverScene *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_bitmap(Obj->background);
    al_destroy_sample(Obj->song);
    al_destroy_sample(Obj->click_sound);
    free(Obj);
    free(self);
}
