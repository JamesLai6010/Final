#include "door.h"
#include <stdbool.h>
#include <stdio.h>
#include "../global.h"

bool draw;

Elements *New_Door(int label, int x, int y) {
    draw = false;
    Door *pDerivedObj = (Door *)malloc(sizeof(Door));
    Elements *pObj = New_Elements(label);

    pDerivedObj->img1 = al_load_bitmap("assets/image/door1.png");
    pDerivedObj->img2 = al_load_bitmap("assets/image/door2.png");
    pDerivedObj->mp3 = al_load_sample("assets/sound/click.mp3");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img1);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img2);

    pDerivedObj->isOpen = false;
    pDerivedObj->x = x;
    pDerivedObj->y = y;

    // 設置交互對象
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // 設置衍生對象的函數
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Door_update;
    pObj->Interact = Door_interact;
    pObj->Draw = Door_draw;
    pObj->Destroy = Door_destroy;

    return pObj;
}

void Door_update(Elements *self) {
    Door *Obj = ((Door *)(self->pDerivedObj));
    if (key_state[ALLEGRO_KEY_SPACE]) {
        Obj->isOpen = true;
    } else {
        Obj->isOpen = false;
    }
}

void Door_interact(Elements *self, Elements *tar) {
    if (tar->label == Character_L) {
        Character *chara = (Character *)(tar->pDerivedObj);
        Door *Obj = (Door *)(self->pDerivedObj);

        if (chara->x >= Obj->x - 70 && chara->x <= Obj->x && 
            chara->y >= Obj->y - 100 && chara->y <= Obj->y + 70) {
            if (keys_collected >= 3 && key_state[ALLEGRO_KEY_SPACE]) {
                al_play_sample(Obj->mp3, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                Obj->isOpen = true;
                finish = true;
                self->dele = true; // 門打開後消失
            }
        }
    }
}

void Door_draw(Elements *self) {
    Door *Obj = ((Door *)(self->pDerivedObj));
        al_draw_bitmap(Obj->img2, Obj->x, Obj->y, 0);
        al_draw_bitmap(Obj->img1, Obj->x, Obj->y-70, 0);
    
}

void Door_destroy(Elements *self) {
    Door *Obj = ((Door *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img1);
    al_destroy_bitmap(Obj->img2);
    al_destroy_sample(Obj->mp3);
    free(Obj);
    free(self);
}
