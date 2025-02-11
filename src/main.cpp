#include "engine/engine.hpp"

int main(){
    if(!engine.init()){
        printf("Engine encountered an error!\n");
    }
    engine.cleanup();
    return 0;
}
