#pragma once
#include "app.hpp"
#include "graphics/graphics.hpp"
#include "input/vinput.hpp"

class Engine{
    public:
    Graphics graphics;
    VInput input;
    bool init(App* app);
    void cleanup();
    void quit();
    private:
    App* app = nullptr;
    bool isRunning = true;
    bool loop();
};

extern Engine engine;