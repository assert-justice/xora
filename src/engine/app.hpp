#pragma once

class App{
    public:
    virtual void init() =0;
    virtual void update(double dt) =0;
    virtual void draw() =0;
};