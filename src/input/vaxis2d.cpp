#include "vaxis2d.hpp"

VAxis2D::VAxis2D(std::string name)
{
    xAxis = new VAxis();
    yAxis = new VAxis();
}

VAxis2D::~VAxis2D()
{
    delete xAxis;
    delete yAxis;
}

void VAxis2D::poll()
{
    xAxis->poll();
    yAxis->poll();
}

VAxis* VAxis2D::getAxisX()
{
    return xAxis;
}

VAxis *VAxis2D::getAxisY()
{
    return yAxis;
}
