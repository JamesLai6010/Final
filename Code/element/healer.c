#include "healer.h"
#include <stdbool.h>
#include <stdio.h>

/*
   [heal function]
*/

Elements *New_Heal(int label, int x, int y)
{
    Heal *pDerivedObj = (Heal *)malloc(sizeof(Heal));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/gemRed.png");
    pDerivedObj->mp3 = al_load_sample("assets/sound/bubble.mp3");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);

    pDerivedObj->picked = false;
    pDerivedObj->x = x;
    pDerivedObj->y = y;
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
            al_play_sample(Obj->mp3, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            if (chara_health <= 80) chara_health += 20;
            else chara_health = 100;
            Obj->picked = true;
            self->dele = true;
            // Make the item disappear
        }
    }
}

void Heal_draw(Elements *self)
{
    Heal *Obj = ((Heal *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}

void Heal_destory(Elements *self)
{
    Heal *Obj = ((Heal *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
