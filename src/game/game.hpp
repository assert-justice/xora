#pragma once
#include "engine/app.hpp"
#include "engine/engine.hpp"
#include "input/vinput.hpp"
#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"
#include "box.hpp"
// #include "btLinearMathAll.cpp"

class Game: App{
    public:
    Game();
    void run();
    virtual void init();
    virtual void update(double dt);
    virtual void draw();
    private:
    // glm::mat4 cameraMatrix;
    // Box* crate;
    Box* floor;
    // btDiscreteDynamicsWorld* dynamicsWorld;
    // btAlignedObjectArray<btCollisionShape*> collisionShapes;
    // VButton *left, *right;
    // VAxis2D* turn;
    // float angle = 0.0f;
    // float tilt = 0.0f;
    int shader;
};