#include "globals.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/engine.hpp"

Globals globals;

void Globals::init()
{
    inputHandler.look = engine.input.addVAxis2D("look");
    inputHandler.look->getAxisX()->addNegKey(GLFW_KEY_LEFT);
    inputHandler.look->getAxisX()->addPosKey(GLFW_KEY_RIGHT);
    inputHandler.look->getAxisY()->addNegKey(GLFW_KEY_UP);
    inputHandler.look->getAxisY()->addPosKey(GLFW_KEY_DOWN);

    inputHandler.move = engine.input.addVAxis2D("move");
    inputHandler.move->getAxisX()->addNegKey(GLFW_KEY_A);
    inputHandler.move->getAxisX()->addPosKey(GLFW_KEY_D);
    inputHandler.move->getAxisY()->addNegKey(GLFW_KEY_S);
    inputHandler.move->getAxisY()->addPosKey(GLFW_KEY_W);

    inputHandler.hover = engine.input.addVAxis("hover");
    inputHandler.hover->addNegKey(GLFW_KEY_LEFT_CONTROL);
    inputHandler.hover->addPosKey(GLFW_KEY_SPACE);

    inputHandler.pause = engine.input.addVButton("pause");
    inputHandler.pause->addKey(GLFW_KEY_ESCAPE);
}
