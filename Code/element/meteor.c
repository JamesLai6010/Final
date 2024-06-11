#include "meteor.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Elements *New_Meteor(int label, int x, int y) {
    Meteor *pDerivedObj = (Meteor *)malloc(sizeof(Meteor));
    Elements *pObj = New_Elements(label);

    pDerivedObj->img1 = al_load_bitmap("assets/image/bomb.png");
    pDerivedObj->img2 = al_load_bitmap("assets/image/bombFlash.png");
    pDerivedObj->mp3 = al_load_sample("assets/sound/bomb.mp3");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img1);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img1);

    pDerivedObj->x = rand() % 1920; // 隨機生成x座標
    pDerivedObj->y = 0;             // 隕石從屏幕頂部掉落
    pDerivedObj->dele = false;
    pDerivedObj->timer = 0;         // 初始化計時器
    pDerivedObj->showImg1 = true;   // 初始化顯示圖片標誌

    pObj->inter_obj[pObj->inter_len++] = Character_L;

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Meteor_update;
    pObj->Interact = Meteor_interact;
    pObj->Draw = Meteor_draw;
    pObj->Destroy = Meteor_destroy;

    return pObj;
}

void Meteor_update(Elements *self) {
    Meteor *Obj = ((Meteor *)(self->pDerivedObj));
    if (window == 1) meteor_fall_speed = 3;
    else if (window == 4) meteor_fall_speed = 5;
    else if (window == 6) meteor_fall_speed = 7;
    else if (window == 7) meteor_fall_speed = 9;
    else if (window == 8) meteor_fall_speed = 11;
    Obj->y += meteor_fall_speed; // 隕石下落速度

    // 依時間切換圖片
    Obj->timer++;
    if (Obj->timer >= 15) {
        Obj->showImg1 = !Obj->showImg1;
        Obj->timer = 0;
    }

    if (Obj->y > 1080) {
        self->dele = true; // 超出螢幕就刪除
    }
}

void Meteor_interact(Elements *self, Elements *tar) {
    if (tar->label == Character_L) {
        Character *chara = (Character *)(tar->pDerivedObj);
        Meteor *Obj = (Meteor *)(self->pDerivedObj);

        // 判斷隕石與角色的碰撞
        if (chara->x <= Obj->x && chara->x + 70 >= Obj->x &&
            chara->y + 20 <= Obj->y + 70 && chara->y + chara->height >= Obj->y) {
            al_play_sample(Obj->mp3, 0.1, 0.0, 0.5, ALLEGRO_PLAYMODE_ONCE, NULL);
            chara_health -= 10; // 碰撞後扣除角色血量
            self->dele = true;   // 隕石消失
        }
    }
}

void Meteor_draw(Elements *self) {
    Meteor *Obj = ((Meteor *)(self->pDerivedObj));
    if (Obj->showImg1) {
        al_draw_bitmap(Obj->img1, Obj->x, Obj->y, 0);
    } else {
        al_draw_bitmap(Obj->img2, Obj->x, Obj->y, 0);
    }
}

void Meteor_destroy(Elements *self) {
    Meteor *Obj = ((Meteor *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img1);
    al_destroy_bitmap(Obj->img2);
    al_destroy_sample(Obj->mp3);
    free(Obj);
    free(self);
}
