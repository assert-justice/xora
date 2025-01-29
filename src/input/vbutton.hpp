#pragma once
#include <string>
#include <vector>

class VButton{
    public:
    std::string name;
    VButton(std::string name);
    VButton();
    void poll(double time);
    void addKey(int keyCode);
    bool isDown();
    bool isPressed();
    private:
    bool state = false;
    bool lastState = false;
    double lastChanged = 0.0;
    std::vector<int> keys;
};