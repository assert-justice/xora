#pragma once
#include <glm/glm.hpp>
#include "camera.hpp"
#include "input_handler.hpp"

class Globals{
    public:
    Camera camera;
    InputHandler inputHandler;
    void init();
};

extern Globals globals;