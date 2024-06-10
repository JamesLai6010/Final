#include "trap.h"
#include <stdbool.h>
#include <stdio.h>

Elements *New_Trap(int label, int x, int y) {
    Trap *pDerivedObj = (Trap *)malloc(sizeof(Trap));
    Elements *pObj = New_Elements(label);
    
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/spikes.png");
    pDerivedObj->mp3 = al_load_sample("assets/sound/hurt.mp3");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);

    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->active = true;
    
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Trap_update;
    pObj->Interact = Trap_interact;
    pObj->Draw = Trap_draw;
    pObj->Destroy = Trap_destroy;
    
    return pObj;
}

void Trap_update(Elements *self) {
    // No specific update logic for the trap
}

void Trap_interact(Elements *self, Elements *tar) {
    if (tar->label == Character_L) {
        Character *chara = (Character *)(tar->pDerivedObj);
        Trap *Obj = (Trap *)(self->pDerivedObj);
        
        if (chara->x >= Obj->x - 70 && chara->x <= Obj->x && 
            chara->y >= Obj->y - 100 && chara->y <= Obj->y + Obj->height) {
            static double last_time = 0;
            double current_time = al_get_time();
            if (current_time - last_time >= 1.0) {
                al_play_sample(Obj->mp3, 0.1, 0.0, 0.5, ALLEGRO_PLAYMODE_ONCE, NULL);
                chara_health -= 10;  // Reduce character health
                last_time = current_time;
            }
        }
    }
}

void Trap_draw(Elements *self) {
    Trap *Obj = (Trap *)(self->pDerivedObj);
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}

void Trap_destroy(Elements *self) {
    Trap *Obj = (Trap *)(self->pDerivedObj);
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
