#include "vm_window.hpp"
#include "engine/engine.hpp"

static bool setStatsFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_str);
    PY_CHECK_ARG_TYPE(1, tp_int);
    PY_CHECK_ARG_TYPE(2, tp_int);
    PY_CHECK_ARG_TYPE(3, tp_int);
    engine.graphics.setStats(
        py_tostr(py_arg(0)), 
        py_toint(py_arg(1)), 
        py_toint(py_arg(2)), 
        py_toint(py_arg(3)));
    py_newnone(py_retval());
    return true;
}

static bool getWidthFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(0);
    py_newint(py_retval(), engine.graphics.getWindowWidth());
    return true;
}
static bool getHeightFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(0);
    py_newint(py_retval(), engine.graphics.getWindowHeight());
    return true;
}

void bindWindow(){
    // Bind engine functions
    auto mod = py_newmodule("xora_engine.window");
    py_bindfunc(mod, "set_stats", setStatsFn);
    py_bindfunc(mod, "get_width", getWidthFn);
    py_bindfunc(mod, "get_height", getHeightFn);
}