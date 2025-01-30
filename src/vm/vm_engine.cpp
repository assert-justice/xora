#include "vm_engine.hpp"
#include "engine/engine.hpp"

static bool deltaTimeFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(0);
    py_newfloat(py_retval(), engine.deltaTime());
    return true;
}
static bool frameTimeFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(0);
    py_newfloat(py_retval(), engine.frameTime());
    return true;
}
static bool quitFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(0);
    engine.quit();
    py_newnone(py_retval());
    return true;
}

void bindEngine(){
    // Bind engine functions
    auto mod = py_newmodule("xora_engine.engine");
    py_bindfunc(mod, "delta_time", deltaTimeFn);
    py_bindfunc(mod, "frame_time", frameTimeFn);
    py_bindfunc(mod, "quit", quitFn);
}