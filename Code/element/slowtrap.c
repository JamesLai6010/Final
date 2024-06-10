#include "slowtrap.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


Elements *New_SlowTrap(int label) {
    SlowTrap *pDerivedObj = (SlowTrap *)malloc(sizeof(SlowTrap));
    Elements *pObj = New_Elements(label);

    pDerivedObj->img = al_load_bitmap("assets/image/plantPurple.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);

    pDerivedObj->picked = false;
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    pDerivedObj->activate = false;

    pObj->inter_obj[pObj->inter_len++] = Character_L;

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = SlowTrap_update;
    pObj->Interact = SlowTrap_interact;
    pObj->Draw = SlowTrap_draw;
    pObj->Destroy = SlowTrap_destroy;

    return pObj;
}

void SlowTrap_update(Elements *self) {
    SlowTrap *Obj = ((SlowTrap *)(self->pDerivedObj));
    // 如果需要的話，可以在這裡添加更新邏輯
}

void SlowTrap_interact(Elements *self, Elements *tar) {
    if (tar->label == Character_L) {
        Character *chara = (Character *)(tar->pDerivedObj);
        SlowTrap *Obj = (SlowTrap *)(self->pDerivedObj);
        
        if (chara->x >= Obj->x - 70 && chara->x <= Obj->x && 
            chara->y >= Obj->y - 100 && chara->y <= Obj->y + Obj->height) {
            
            slow_timer = 5;  // 設置減速時間
            slow = true;
            //Obj->picked = true;
            //self->dele = true;  // 讓陷阱消失
        }
    }
}

void SlowTrap_draw(Elements *self) {
    SlowTrap *Obj = ((SlowTrap *)(self->pDerivedObj));
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 27; j++) {
            if (map_data[i][j] == 31) {  // 用合適的地圖數據值來表示陷阱位置
                Obj->x = j * Obj->width;
                Obj->y = i * Obj->height;
                al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
            }
        }
    }
}

void SlowTrap_destroy(Elements *self) {
    SlowTrap *Obj = ((SlowTrap *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
