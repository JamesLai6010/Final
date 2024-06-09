#include "floor2.h"
#include <stdio.h>
/*
   [floor function]
*/
Elements *New_Floor2(int label)
{
    printf("Floor2 creating\n");
    Floor2 *pDerivedObj = (Floor2 *)malloc(sizeof(Floor2));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/grassMid.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    _Floor2_load_map(pDerivedObj);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Floor2_draw;
    pObj->Update = Floor2_update;
    pObj->Interact = Floor2_interact;
    pObj->Destroy = Floor2_destory;
    return pObj;
}
void _Floor2_load_map(Floor2 *floor)
{
    FILE *data;
    data = fopen("assets/map/gamescene_map2.txt", "r");
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            fscanf(data, "%d", &map_data[i][j]);
        }
    }
    fclose(data);
}

void Floor2_update(Elements *ele) {}
void Floor2_interact(Elements *self, Elements *tar)
{
   /* if (tar->label == Character_L2)
    {
        Character *chara = (Character *)(tar->pDerivedObj);
        int right_limit = WIDTH - chara->width / 2;
        int left_limit = 0 - chara->width / 2;
        if (chara->x < left_limit)
        {
            _Character_update_position(tar, right_limit - left_limit, 0);
        }
        else if (chara->x > right_limit)
        {
            _Character_update_position(tar, left_limit - right_limit, 0);
        }
        
    }*/
}

void Floor2_draw(Elements *self)
{
    Floor2 *Obj = ((Floor2 *)(self->pDerivedObj));
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            if (map_data[i][j] == 1)
            {
                al_draw_bitmap(Obj->img, Obj->x + j * Obj->width, Obj->y + i * Obj->height, 0);
            }
        }
    }
}
void Floor2_destory(Elements *self)
{
    Floor2 *Obj = ((Floor2 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}