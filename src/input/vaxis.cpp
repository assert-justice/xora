#include "vaxis.hpp"
#include "engine/engine.hpp"

VAxis::VAxis()
{
    name = "[DEFAULT]";
}

VAxis::VAxis(std::string _name)
{
    name = _name;
}

void VAxis::poll()
{
    value = 0.0f;
    auto window = engine.graphics.getWindow();
    for(auto key: posKeys) if(glfwGetKey(window, key)) value += 1.0f;
    for(auto key: negKeys) if(glfwGetKey(window, key)) value -= 1.0f;
}

void VAxis::addPosKey(int keyCode)
{
    posKeys.push_back(keyCode);
}

void VAxis::addNegKey(int keyCode)
{
    negKeys.push_back(keyCode);
}

float VAxis::getValue()
{
    return value;
}
