#include "teleport.h"
#include <stdbool.h>
#include <stdio.h>

// 地图数据数组
int teleport_map_data[15][27];

/*
   [teleport function]
*/
Elements *New_Teleport(int label)
{
    Teleport *pDerivedObj = (Teleport *)malloc(sizeof(Teleport));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/yellow_key.png");
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
    pObj->Update = Teleport_update;
    pObj->Interact = Teleport_interact;
    pObj->Draw = Teleport_draw;
    pObj->Destroy = Teleport_destory;
    return pObj;
}

void _Teleport_load_map(Teleport *teleport)
{

}

void Teleport_update(Elements *self)
{
    Teleport *Obj = ((Teleport *)(self->pDerivedObj));
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
void Teleport_interact(Elements *self, Elements *tar)
{
    if (tar->label == Character_L)
    {
        Character *chara = (Character *)(tar->pDerivedObj);
        Teleport *Obj = (Teleport *)(self->pDerivedObj);
        if (chara->x >= Obj->x &&
            chara->x <= Obj->x + Obj->width &&
            Obj->activate)
        {
            _Character_update_position(tar, 0 - chara->x, 0);
        }
    }
}

void Teleport_draw(Elements *self)
{
    Teleport *Obj = ((Teleport *)(self->pDerivedObj));
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            if (map_data[i][j] == 2)
            {
                al_draw_bitmap(Obj->img, Obj->x + j * Obj->width, Obj->y + i * Obj->height, 0);
            }
        }
    }
}

void Teleport_destory(Elements *self)
{
    Teleport *Obj = ((Teleport *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
