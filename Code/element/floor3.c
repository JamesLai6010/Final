#include "floor3.h"
#include <stdio.h>
/*
   [floor function]
*/
Elements *New_Floor3(int label)
{
    printf("Floor3 creating\n");
    Floor3 *pDerivedObj = (Floor3 *)malloc(sizeof(Floor3));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/grassMid.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    _Floor3_load_map(pDerivedObj);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Floor3_draw;
    pObj->Update = Floor3_update;
    pObj->Interact = Floor3_interact;
    pObj->Destroy = Floor3_destory;
    return pObj;
}
void _Floor3_load_map(Floor3 *floor)
{
    FILE *data;
    data = fopen("assets/map/gamescene_map3.txt", "r");
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            fscanf(data, "%d", &map_data[i][j]);
        }
    }
    fclose(data);
}

void Floor3_update(Elements *ele) {}
void Floor3_interact(Elements *self, Elements *tar)
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

void Floor3_draw(Elements *self)
{
    Floor3 *Obj = ((Floor3 *)(self->pDerivedObj));
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
void Floor3_destory(Elements *self)
{
    Floor3 *Obj = ((Floor3 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}