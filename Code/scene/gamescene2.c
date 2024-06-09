#include "gamescene2.h"
/*
   [GameScene function]
*/
Scene *New_GameScene2(int label)
{
    printf("GameScene2 creating\n");
    GameScene2 *pDerivedObj = (GameScene2 *)malloc(sizeof(GameScene2));
    Scene *pObj = New_Scene(label);
    // font
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 44, 0);
    pDerivedObj->game_time = 0; // 初始化時間
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/back.jpg");
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Floor2(Floor_L2));
    //_Register_elements(pObj, New_Teleport(Teleport_L));
    //_Register_elements(pObj, New_Tree(Tree_L)); //先取消這些東西 之後改成道具 陷阱 傳送
    _Register_elements(pObj, New_Character(Character_L2));
    // setting derived object function
    pObj->Update = game_scene2_update;
    pObj->Draw = game_scene2_draw;
    pObj->Destroy = game_scene2_destroy;
    return pObj;
}
void game_scene2_update(Scene *self)
{
    GameScene2 *gs = ((GameScene2 *)(self->pDerivedObj));
    gs->game_time += 1.0 / 60; // 60 FPS + 1s
    // update every element
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
    }

    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->label == Character_L2)
        {
            Character *chara = (Character *)(ele->pDerivedObj);
            if(chara->x <= 0){
                self->scene_end = true;
                window = 1;
                printf("Change to scene 1\n");
                return;
            }
        }
    }

}
void game_scene2_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene2 *gs = ((GameScene2 *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
    // show_time
    int minutes = (int)gs->game_time / 60;
    int seconds = (int)gs->game_time % 60;

    char time_text[50];
    sprintf(time_text, "Time: %02d:%02d", minutes, seconds);
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 30, 20, ALLEGRO_ALIGN_LEFT, time_text);
}

void game_scene2_destroy(Scene *self)
{
    printf("gameScene2 destroying\n");
    GameScene2 *Obj = ((GameScene2 *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    al_destroy_font(Obj->font);
    free(Obj);
    free(self);
}