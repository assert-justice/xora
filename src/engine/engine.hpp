#pragma once
#include "graphics/graphics.hpp"
// #include "input/vinput.hpp"
#include "vm/vm.hpp"
#include "xo_math/xo_math.hpp"

class Engine{
    public:
    Graphics graphics;
    // VInput input;
    VM vm;
    XoMath xoMath;
    bool init();
    void cleanup();
    void quit();
    double deltaTime();
    double frameTime();
    void setTickRate(double tr){tickRate = tr;}
    double getTickRate(){return tickRate;}
    private:
    double dt;
    double ft;
    double tickRate = 100;
    bool isRunning = true;
    bool loop();
};

extern Engine engine;