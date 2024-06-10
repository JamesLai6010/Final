#include "key.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Elements *New_Key(int label, int x, int y) {
    Key *pDerivedObj = (Key *)malloc(sizeof(Key));
    Elements *pObj = New_Elements(label);

    pDerivedObj->img = al_load_bitmap("assets/image/key.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->mp3 = al_load_sample("assets/sound/key.mp3");

    pDerivedObj->x = rand() % 1920; // 隨機生成x座標
    pDerivedObj->y = 0;             // 鑰匙從頂部掉落
    pDerivedObj->dele = false;

    pObj->inter_obj[pObj->inter_len++] = Character_L;

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Key_update;
    pObj->Interact = Key_interact;
    pObj->Draw = Key_draw;
    pObj->Destroy = Key_destroy;

    return pObj;
}

void Key_update(Elements *self) {
    Key *Obj = ((Key *)(self->pDerivedObj));
    Obj->y += 5; // 鑰匙下落速度

    if (Obj->y > 1080) {
        self->dele = true; // 超出螢幕就刪除
    }
}

void Key_interact(Elements *self, Elements *tar) {
    if (tar->label == Character_L) {
        Character *chara = (Character *)(tar->pDerivedObj);
        Key *Obj = (Key *)(self->pDerivedObj);

        // 判斷鑰匙與角色的碰撞
        if (chara->x <= Obj->x && chara->x + 70 >= Obj->x &&
            chara->y + 20 <= Obj->y + 70 && chara->y + chara->height >= Obj->y) {
                al_play_sample(Obj->mp3, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            // 角色獲得鑰匙的處理邏輯
            // 這裡可以添加角色獲得鑰匙後的處理，例如增加鑰匙計數
            keys_collected += 1; // 假設角色有一個 keys_collected 變量
            self->dele = true;   // 鑰匙消失
        }
    }
}

void Key_draw(Elements *self) {
    Key *Obj = ((Key *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}

void Key_destroy(Elements *self) {
    Key *Obj = ((Key *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
