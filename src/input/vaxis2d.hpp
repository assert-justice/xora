#pragma once
#include <string>
#include "vaxis.hpp"

class VAxis2D{
    public:
    VAxis2D(std::string name);
    ~VAxis2D();
    void poll();
    VAxis* getAxisX();
    VAxis* getAxisY();
    private:
    std::string name;
    VAxis *xAxis, *yAxis;
};