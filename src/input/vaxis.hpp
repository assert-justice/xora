#pragma once
#include <vector>
#include <string>

class VAxis{
    public:
    VAxis();
    VAxis(std::string name);
    void poll();
    void addPosKey(int keyCode);
    void addNegKey(int keyCode);
    float getValue();
    private:
    std::string name;
    float value = 0.0f;
    std::vector<int> posKeys;
    std::vector<int> negKeys;
};