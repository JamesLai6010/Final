#include "jump.h"
#include <stdbool.h>
#include <stdio.h>

Elements *New_Jump(int label, int x, int y) {
    Jump *pDerivedObj = (Jump *)malloc(sizeof(Jump));
    Elements *pObj = New_Elements(label);
    //printf("/n kkkkkkkk/n");
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/gemGreen.png");
    pDerivedObj->mp3 = al_load_sample("assets/sound/bubble.mp3");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);

    pDerivedObj->picked = false;
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->activate = false;

    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Jump_update;
    pObj->Interact = Jump_interact;
    pObj->Draw = Jump_draw;
    pObj->Destroy = Jump_destroy;

    return pObj;
}

void Jump_update(Elements *self) {
    Jump *Obj = ((Jump *)(self->pDerivedObj));
    if (key_state[ALLEGRO_KEY_SPACE]) {
        Obj->activate = true;
    } else {
        Obj->activate = false;
    }
}

void Jump_interact(Elements *self, Elements *tar) {
    if (tar->label == Character_L) {
        Character *chara = (Character *)(tar->pDerivedObj);
        Jump *Obj = (Jump *)(self->pDerivedObj);
        
        if (chara->x >= Obj->x - 70 && chara->x <= Obj->x && 
            chara->y >= Obj->y - 100 && chara->y <= Obj->y + 70 && 
            Obj->picked == false) {
            al_play_sample(Obj->mp3, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            jump_timer = 3;  // 設置跳躍增強時間
            jump_boost = true;
            Obj->picked = true;
            self->dele = true;  // 讓道具消失
        }
    }
}

void Jump_draw(Elements *self) {
    Jump *Obj = ((Jump *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}

void Jump_destroy(Elements *self) {
    Jump *Obj = ((Jump *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
