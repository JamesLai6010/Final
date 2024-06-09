#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "aboutscene.h"
#include <stdio.h>
#include "exitscene.h"
#include "gamescene2.h"
#include "gameoverscene.h"
Scene *scene = NULL;

void create_scene(SceneType type)
{
    printf("debug message in sceneManager.c\n");
    printf("create_scene called with type: %d\n", type);
    fflush(stdout); // 確保立即刷新標準輸出
    switch (type)
    {
    case Menu_L:
        printf("Creating Menu_L\n");
        fflush(stdout);
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        fflush(stdout);
        scene = New_GameScene(GameScene_L);
        printf("Creating GameScene_L\n");
        break;
    case AboutScene_L:
        fflush(stdout);
        scene = New_AboutScene(AboutScene_L);
        printf("Creating AboutScene_L\n");
        break;
    case  ExitScene_L:
        fflush(stdout);
        scene = New_ExitScene(ExitScene_L);
        printf("Creating ExitScene_L\n");
        break;
    case GameScene_L2:
        fflush(stdout);
        scene = New_GameScene2(GameScene_L2);
        printf("Creating GameScene_L2\n");
        break;
    case GameOverScene_L:
        fflush(stdout);
        scene = New_GameOverScene(GameOverScene_L);
        printf("Creating GameOverScene_L\n");
        break;
    default:
        printf("Unknown SceneType\n");
        fflush(stdout);
        break;
    }
}
