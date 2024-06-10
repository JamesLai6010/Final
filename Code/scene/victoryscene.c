#include <allegro5/allegro_primitives.h>
#include "victoryscene.h"
#include "../global.h"

Scene *New_VictoryScene(int label)
{
    VictoryScene *pDerivedObj = (VictoryScene *)malloc(sizeof(VictoryScene));
    Scene *pObj = New_Scene(label);
    // 設置衍生對象成員
    pDerivedObj->font = al_load_ttf_font("assets/font/SuperMarioBros.ttf", 100, 0);
    pDerivedObj->background = al_load_bitmap("assets/image/victory.png");
    pDerivedObj->click_sound = al_load_sample("assets/sound/click.mp3");
    pDerivedObj->song = al_load_sample("assets/sound/victory.mp3");
    al_play_sample(((pDerivedObj)->song), 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_reserve_samples(20);
    pObj->pDerivedObj = pDerivedObj;
    // 設置衍生對象函數
    pObj->Update = victory_update;
    pObj->Draw = victory_draw;
    pObj->Destroy = victory_destroy;
    return pObj;
}

void victory_update(Scene *self)
{
    printf("%lf %lf\n",mouse.x,mouse.y);
    if (mouse_state[1] && mouse.x >= 230 && mouse.x <= 640 && mouse.y >= 775 && mouse.y <= 825) { // yes
        al_play_sample(((VictoryScene *)(self->pDerivedObj))->click_sound, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // 播放點擊聲音
        al_rest(0.15);
        self->scene_end = true;
        window = 10;  // start
    } else if (mouse_state[1] && mouse.x >= 1270 && mouse.x <= 1650 && mouse.y >= 775 && mouse.y <= 825) { // no
        al_play_sample(((VictoryScene *)(self->pDerivedObj))->click_sound, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); // 播放點擊聲音
        al_rest(0.15);
        self->scene_end = true;
        window = 0;  // menu
    }

    return;
}

void victory_draw(Scene *self)
{
    VictoryScene *Obj = ((VictoryScene *)(self->pDerivedObj));
    // 繪製勝利背景
    al_draw_bitmap(Obj->background, 0, 0, 0);

    // 繪製通關時間
    char time_str[50];
    int min = (int)end_time / 60;
    int sec = (int)end_time % 60;
    sprintf(time_str, "End Time: %02d:%02d", min, sec);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), 980, 570, ALLEGRO_ALIGN_CENTER, time_str);
}

void victory_destroy(Scene *self)
{
    VictoryScene *Obj = ((VictoryScene *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_bitmap(Obj->background);
    al_destroy_sample(Obj->song);
    al_destroy_sample(Obj->click_sound);
    free(Obj);
    free(self);
}
