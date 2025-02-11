#include "vm_math.hpp"
#include "engine/engine.hpp"

static bool pushIdentityFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(0);
    engine.xoMath.pushIdentity();
    py_newnone(py_retval());
    return true;
}
static bool pushPerspectiveFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(4);
    PY_CHECK_ARG_TYPE(0, tp_float);
    PY_CHECK_ARG_TYPE(1, tp_float);
    PY_CHECK_ARG_TYPE(2, tp_float);
    PY_CHECK_ARG_TYPE(3, tp_float);
    float fov = py_tofloat(py_arg(0));
    float aspect = py_tofloat(py_arg(1));
    float near = py_tofloat(py_arg(2));
    float far = py_tofloat(py_arg(3));
    engine.xoMath.pushPerspective(fov, aspect, near, far);
    py_newnone(py_retval());
    return true;
}
static bool pushVector3Fn(int argc, py_Ref argv){
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_float);
    PY_CHECK_ARG_TYPE(1, tp_float);
    PY_CHECK_ARG_TYPE(2, tp_float);
    float x = py_tofloat(py_arg(0));
    float y = py_tofloat(py_arg(1));
    float z = py_tofloat(py_arg(2));
    engine.xoMath.pushVector3(x, y, z);
    py_newnone(py_retval());
    return true;
}

static bool translateFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(0);
    engine.xoMath.translate();
    py_newnone(py_retval());
    return true;
}
static bool scaleFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(0);
    engine.xoMath.scale();
    py_newnone(py_retval());
    return true;
}
static bool rotateEulerFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(0);
    engine.xoMath.rotateEuler();
    py_newnone(py_retval());
    return true;
}

void bindMath()
{
    auto mod = py_newmodule("xora_engine.xo_math");
    py_bindfunc(mod, "push_identity", pushIdentityFn);
    py_bindfunc(mod, "push_perspective", pushPerspectiveFn);
    py_bindfunc(mod, "push_vector3", pushVector3Fn);
    py_bindfunc(mod, "translate", translateFn);
    py_bindfunc(mod, "scale", scaleFn);
    py_bindfunc(mod, "rotate_euler", rotateEulerFn);
}
