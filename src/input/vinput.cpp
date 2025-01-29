#include "vinput.hpp"
#include "engine/engine.hpp"

void VInput::poll(double time)
{
    auto window = engine.graphics.getWindow();
    for(auto button: buttons) button->poll(time);
    for(auto axis: axes) axis->poll();
    for(auto axis: axes2d) axis->poll();
    double mx, my, mdx, mdy;
    glfwGetCursorPos(window, &mx, &my);
    mouseDX = mx - mouseX;
    mouseDY = my - mouseY;
    mouseX = mx; mouseY = my;
    if(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        glfwSetCursorPos(window, 0, 0);
        mouseX = 0; mouseY = 0;
    }
}

VButton* VInput::addVButton(std::string name)
{
    auto button = new VButton(name);
    buttons.push_back(button);
    return button;
}

VAxis *VInput::addVAxis(std::string name)
{
    auto axis = new VAxis(name);
    axes.push_back(axis);
    return axis;
}

VAxis2D *VInput::addVAxis2D(std::string name)
{
    auto axis = new VAxis2D(name);
    axes2d.push_back(axis);
    return axis;
}

float VInput::getMouseX()
{
    return mouseX;
}

float VInput::getMouseY()
{
    return mouseY;
}

float VInput::getMouseDX()
{
    return mouseDX;
}

float VInput::getMouseDY()
{
    return mouseDY;
}

void VInput::setMouseEnabled(bool isEnabled)
{
    auto window = engine.graphics.getWindow();
    if (glfwRawMouseMotionSupported()) glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, !isEnabled);
    glfwSetInputMode(window, GLFW_CURSOR, isEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

bool VInput::initInternal()
{
    return true;
}

void VInput::cleanupInternal()
{
    for(auto button: buttons) delete button;
    for(auto axis: axes) delete axis;
    for(auto axis: axes2d) delete axis;
}
