#include "teleport.h"
#include <stdbool.h>
/*
   [teleport function]
*/
Elements *New_Teleport(int label,int x,int y)
{
    printf("Teleport creating\n");
    Teleport *pDerivedObj = (Teleport *)malloc(sizeof(Teleport));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/stoneMid.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->activate = false;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Teleport_update;
    pObj->Interact = Teleport_interact;
    pObj->Draw = Teleport_draw;
    pObj->Destroy = Teleport_destory;
    return pObj;
}
void Teleport_update(Elements *self)
{
    Teleport *Obj = ((Teleport *)(self->pDerivedObj));
    if (key_state[ALLEGRO_KEY_E])
    {
        Obj->activate = true;
    }
    else
    {
        Obj->activate = false;
    }
}
void Teleport_interact(Elements *self, Elements *tar)
{
    if (tar->label == Character_L)
    {
        Character *chara = (Character *)(tar->pDerivedObj);
        Teleport *Obj = (Teleport *)(self->pDerivedObj);
        if (chara->x >= Obj->x - 70 && chara->x <= Obj->x && 
            chara->y + chara->height >= Obj->y-20 && chara->y + chara->height <= Obj->y+20 &&
            Obj->activate)
        {
            _Character_update_position(tar, -17*70, -200);
        }
    }
}
void Teleport_draw(Elements *self)
{
    Teleport *Obj = ((Teleport *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Teleport_destory(Elements *self)
{
    Teleport *Obj = ((Teleport *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}