#pragma once
#include <string>
#include <vector>
#include "engine/module.hpp"
#include "vbutton.hpp"
#include "vaxis.hpp"
#include "vaxis2d.hpp"

class VInput: public Module{
    public:
    void poll(double time);
    VButton* addVButton(std::string name);
    VAxis* addVAxis(std::string name);
    VAxis2D* addVAxis2D(std::string name);
    float getMouseX();
    float getMouseY();
    float getMouseDX();
    float getMouseDY();
    void setMouseEnabled(bool isEnabled);
    protected:
    bool initInternal();
    void cleanupInternal();
    private:
    std::vector<VButton*> buttons;
    std::vector<VAxis*> axes;
    std::vector<VAxis2D*> axes2d;
    float mouseX, mouseY, mouseDX, mouseDY = 0.0f;
};