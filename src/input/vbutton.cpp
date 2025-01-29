#include "vbutton.hpp"
#include "engine/engine.hpp"
#include <iostream>

VButton::VButton(std::string _name)
{
    name = _name;
}
VButton::VButton()
{
    name = "[DEFAULT]";
}
void VButton::poll(double time)
{
    lastState = state;
    state = false;
    auto window = engine.graphics.getWindow();
    for(auto key : keys){
        if(glfwGetKey(window, key)) state = true;
    }
    if(state != lastState) lastChanged = time;
    // std::cout << "bruh " << state << std::endl;
}

void VButton::addKey(int keyCode)
{
    keys.push_back(keyCode);
}

bool VButton::isDown()
{
    // std::cout << "fuck " << state << std::endl;
    return state;
}

bool VButton::isPressed()
{
    return state && !lastState;
}
