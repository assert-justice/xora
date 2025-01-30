#include "vm_input.hpp"
#include "engine/engine.hpp"

static bool isKeyDownFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    bool down = glfwGetKey(engine.graphics.getWindow(), py_toint(py_arg(0))) == GLFW_PRESS;
    py_newbool(py_retval(), down);
    return true;
}

void bindInput(){
    auto mod = py_newmodule("xora_engine.input");
    py_bindfunc(mod, "is_key_down", isKeyDownFn);
}