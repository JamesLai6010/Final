#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include "scene.h"
extern Scene *scene;
typedef enum SceneType
{
    Menu_L = 0,
    GameScene_L,
    AboutScene_L,
    ExitScene_L,
    GameScene_L2,
    GameOverScene_L,
    GameScene_L3,
    GameScene_L4,
    GameScene_L5,
    CountdownScene_L = 10
} SceneType;
void create_scene(SceneType);

#endif