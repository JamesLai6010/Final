#include "floor5.h"
#include <stdio.h>
/*
   [floor function]
*/
Elements *New_Floor5(int label)
{
    printf("Floor5 creating\n");
    Floor5 *pDerivedObj = (Floor5 *)malloc(sizeof(Floor5));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/grassMid.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    _Floor5_load_map(pDerivedObj);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Floor5_draw;
    pObj->Update = Floor5_update;
    pObj->Interact = Floor5_interact;
    pObj->Destroy = Floor5_destory;
    return pObj;
}
void _Floor5_load_map(Floor5 *floor)
{
    FILE *data;
    data = fopen("assets/map/gamescene_map5.txt", "r");
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            fscanf(data, "%d", &map_data[i][j]);
        }
    }
    fclose(data);
}

void Floor5_update(Elements *ele) {}
void Floor5_interact(Elements *self, Elements *tar)
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

void Floor5_draw(Elements *self)
{
    Floor5 *Obj = ((Floor5 *)(self->pDerivedObj));
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
void Floor5_destory(Elements *self)
{
    Floor5 *Obj = ((Floor5 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}