#include "speed.h"
#include <stdbool.h>
#include <stdio.h>
#include "../global.h"
/*
   [teleport function]
*/
bool draw;
Elements *New_Speed(int label, int x, int y)
{
    draw = false;
    Speed *pDerivedObj = (Speed *)malloc(sizeof(Speed));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/gemBlue.png");
    pDerivedObj->mp3 = al_load_sample("assets/sound/bubble.mp3");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);

    pDerivedObj->picked = false;
    //_Teleport_load_map(pDerivedObj);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
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
        //printf("%d %d %d %d\n",Obj->x, Obj->y, chara->x, chara->y);
        if (chara->x >= Obj->x-70 && chara->x <= Obj->x && chara->y >= Obj->y-100 && 
            chara->y <= Obj->y+70 && Obj->picked == false)
        {
            //printf("kkkk\n");
            al_play_sample(Obj->mp3, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            speed_timer = 5;
            speed = true;
            Obj->picked = true;
            self->dele = true;
            // 讓道具消失
        }
    }
}

void Speed_draw(Elements *self)
{
    Speed *Obj = ((Speed *)(self->pDerivedObj));
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
        //Obj->x = speed_x;
        //Obj->y = speed_y;
}

void Speed_destory(Elements *self)
{
    Speed *Obj = ((Speed *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
