#include "floor.h"
#include <stdio.h>
/*
   [floor function]
*/
Elements *New_Floor(int label)
{
    printf("Floor1 creating\n");
    Floor *pDerivedObj = (Floor *)malloc(sizeof(Floor));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/grassMid.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    _Floor_load_map(pDerivedObj);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Floor_draw;
    pObj->Update = Floor_update;
    pObj->Interact = Floor_interact;
    pObj->Destroy = Floor_destory;
    return pObj;
}
void _Floor_load_map(Floor *floor)
{
    FILE *data;
    data = fopen("assets/map/gamescene_map.txt", "r");
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            fscanf(data, "%d", &map_data[i][j]);
        }
    }
    fclose(data);
}

void Floor_update(Elements *ele) {}
void Floor_interact(Elements *self, Elements *tar)
{
   if (tar->label == Character_L)
    {
        Character *chara = (Character *)(tar->pDerivedObj);
        int right_limit = WIDTH - chara->width / 2;
        int left_limit = 0 - chara->width / 2;
        if (chara->x < left_limit)
        {
            _Character_update_position(tar, left_limit - chara->x, 0);
        }
        else if (chara->x > right_limit)
        {
            //_Character_update_position(tar, left_limit - right_limit, 0);
        }
        
    }
}

void Floor_draw(Elements *self)
{
    Floor *Obj = ((Floor *)(self->pDerivedObj));
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
void Floor_destory(Elements *self)
{
    Floor *Obj = ((Floor *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}