#include "gamescene.h"

/*
   [GameScene function]
*/
Scene *New_GameScene(int label)
{
    end_time = 0;
    game_over = 0;
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // font
    pDerivedObj->font = al_load_ttf_font("assets/font/SuperMarioBros.ttf", 50, 0);
    pDerivedObj->game_time = 0; // 初始化時間
    pDerivedObj->game_over = false;
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/back.jpg");
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Floor(Floor_L));
    //_Register_elements(pObj, New_Teleport(Teleport_L));
    //_Register_elements(pObj, New_Tree(Tree_L)); //先取消這些東西 之後改成道具 陷阱 傳送
    _Register_elements(pObj, New_Character(Character_L));
    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}
void game_scene_update(Scene *self)
{
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    ElementVec allEle = _Get_all_elements(self);
    // update every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Update(ele);        
    }
    if (game_over) {
        end_time = game_time;
        self->scene_end = true;
        window = 5;
        printf("Change to GameOverScene\n");
    }
    // 如果角色沒有死亡，更新遊戲時間
    if (!game_over) {
        game_time += 1.0 / 60; // 60 FPS + 1s
    } 

    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->label == Character_L)
        {
            Character *chara = (Character *)(ele->pDerivedObj);
            chara->current_map = 0;
            if (chara->x >= 1850)
            {
                save_character_right_to_left();
                self->scene_end = true;
                window = 4; //game_scene2
                printf("Change to scene 2\n");
                return; 
            }
        }
    }
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
     
}

void game_scene_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
    // show_time
    int minutes = (int)game_time / 60;
    int seconds = (int)game_time % 60;

    char time_text[50];
    sprintf(time_text, "Time: %02d:%02d", minutes, seconds);
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 40, 30, ALLEGRO_ALIGN_LEFT, time_text);
}

void game_scene_destroy(Scene *self)
{
    printf("gameScene destroying\n");
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
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
    printf("gameScene destroy finishing\n");
}