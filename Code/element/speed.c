#include "speed.h"
#include <stdbool.h>
#include <stdio.h>

int speed[100] = {0};
/*
   [teleport function]
*/
Elements *New_Speed(int label)
{
    Speed *pDerivedObj = (Speed *)malloc(sizeof(Speed));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/gemBlue.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    //_Teleport_load_map(pDerivedObj);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    pDerivedObj->activate = false;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Speed_update;
    pObj->Interact = Speed_interact;
    pObj->Draw = Speed_draw;
    pObj->Destroy = Speed_destory;
    return pObj;
}

void _Speed_load_map(Speed *speed)
{

}

void Speed_update(Elements *self)
{
    Speed *Obj = ((Speed *)(self->pDerivedObj));
    if (key_state[ALLEGRO_KEY_SPACE])
    {
        Obj->activate = true;
    }
    else
    {
        Obj->activate = false;
    }
}
//要改
void Speed_interact(Elements *self, Elements *tar)
{
    if (tar->label == Character_L)
    {
        Character *chara = (Character *)(tar->pDerivedObj);
        Speed *Obj = (Speed *)(self->pDerivedObj);
        if (chara->x >= Obj->x &&
            chara->x <= Obj->x + Obj->width &&
            Obj->activate)
        {
            _Character_update_position(tar, 0 - chara->x, 0);
        }
    }
}

void Speed_draw(Elements *self)
{
    Speed *Obj = ((Speed *)(self->pDerivedObj));
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            if (map_data[i][j] == 3)
            {
                al_draw_bitmap(Obj->img, Obj->x + j * Obj->width, Obj->y + i * Obj->height, 0);
            }
        }
    }
}

void Speed_destory(Elements *self)
{
    Speed *Obj = ((Speed *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
