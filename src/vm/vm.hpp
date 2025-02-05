#pragma once
#include "engine/module.hpp"
#include "pocketpy.h"
// #include "engine/engine.cpp"

class VM: public Module{
    private:
    // py_GlobalRef mod;
    py_ItemRef initFn = NULL;
    py_ItemRef updateFn = NULL;
    py_ItemRef drawFn = NULL;
    py_ItemRef drawUiFn = NULL;
    protected:
    bool initInternal();
    void cleanupInternal();
    public:
    bool update();
    bool draw();
    bool drawUi();
    bool launch();
};