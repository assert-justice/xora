#pragma once
#include "input/vinput.hpp"

class InputHandler{
    public:
    VAxis2D* look;
    VAxis2D* move;
    VAxis* hover;
    VButton* pause;
};