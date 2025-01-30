#include "engine.hpp"
#include "utils/time.hpp"

bool Engine::init(){
    bool hasError = false;
    vm.init(&hasError);
    graphics.init(&hasError);
    input.init(&hasError);
    if(hasError) return false;
    return loop();
}

void Engine::cleanup()
{
    graphics.cleanup();
}

void Engine::quit()
{
    isRunning = false;
}

double Engine::deltaTime()
{
    return dt;
}

double Engine::frameTime()
{
    return ft;
}

bool Engine::loop()
{
    double t = 0.0;
    dt = 1.0 / tickRate; // target delta time
    double currentTime = getTime();
    double acc = 0.0;
    double scriptTime;
    double elapsedTime = 0;
    if(!vm.launch()) return false;
    while (isRunning){
        double newTime = getTime();
        // time since last frame
        // the frameTime is our budget for game logic
        ft = newTime - currentTime;
        currentTime = newTime;

        // we add the frame time to the accumulator 
        // in this way "left over" time will roll over to the next render loop
        acc += ft;
        // while the time budget has at least one more full time for a script update
        while(acc >= dt){
            scriptTime = getTime();
            input.poll(scriptTime);
            if(!vm.update()) return false;
            elapsedTime = getTime() - scriptTime;
            acc -= dt;
            t += dt;
        }
        graphics.drawBegin();
        if(!vm.draw()) return false;
        graphics.drawEnd();
        if(graphics.shouldClose()) isRunning = false;
    }
    return true;
}

Engine engine;