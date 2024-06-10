#include "healer.h"
#include <stdbool.h>
#include <stdio.h>

/*
   [heal function]
*/

Elements *New_Heal(int label)
{
    Heal *pDerivedObj = (Heal *)malloc(sizeof(Heal));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/gemRed.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);

    pDerivedObj->picked = false;
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    pDerivedObj->activate = false;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Heal_update;
    pObj->Interact = Heal_interact;
    pObj->Draw = Heal_draw;
    pObj->Destroy = Heal_destory;
    return pObj;
}

void _Heal_load_map(Heal *heal)
{
    // Implementation if needed
}

void Heal_update(Elements *self)
{
    Heal *Obj = ((Heal *)(self->pDerivedObj));
    if (key_state[ALLEGRO_KEY_SPACE])
    {
        Obj->activate = true;
    }
    else
    {
        Obj->activate = false;
    }
}

void Heal_interact(Elements *self, Elements *tar)
{
    if (tar->label == Character_L)
    {
        Character *chara = (Character *)(tar->pDerivedObj);
        Heal *Obj = (Heal *)(self->pDerivedObj);
        if (chara->x >= Obj->x-70 && chara->x <= Obj->x && chara->y >= Obj->y-100 && 
            chara->y <= Obj->y+70 && Obj->picked == false)
        {
            // Heal the character
            chara_health = chara->max_health;
            Obj->picked = true;
            self->dele = true;
            // Make the item disappear
        }
    }
}

void Heal_draw(Elements *self)
{
    Heal *Obj = ((Heal *)(self->pDerivedObj));
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            if (map_data[i][j] == 11) // Assuming map_data value 7 represents a heal item
            {
                // Update item position
                Obj->x = j * Obj->width;
                Obj->y = i * Obj->height;
                al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
            }
        }
    }
}

void Heal_destory(Elements *self)
{
    Heal *Obj = ((Heal *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
