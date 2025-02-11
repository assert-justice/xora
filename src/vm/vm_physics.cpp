#include "vm_physics.hpp"
#include "engine/engine.hpp"
#include <glm/gtc/type_ptr.hpp>

static bool addBoxShapeFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_float);
    PY_CHECK_ARG_TYPE(1, tp_float);
    PY_CHECK_ARG_TYPE(2, tp_float);
    float width = py_tofloat(py_arg(0));
    float height = py_tofloat(py_arg(1));
    float depth = py_tofloat(py_arg(2));
    int id = engine.physics.addBoxShape(width, height, depth);
    py_newint(py_retval(), id);
    return true;
}
static bool addSphereShapeFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_float);
    float radius = py_tofloat(py_arg(0));
    int id = engine.physics.addSphereShape(radius);
    py_newint(py_retval(), id);
    return true;
}

static bool addRigidBodyFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(5);
    PY_CHECK_ARG_TYPE(0, tp_int);
    PY_CHECK_ARG_TYPE(1, tp_float);
    PY_CHECK_ARG_TYPE(2, tp_float);
    PY_CHECK_ARG_TYPE(3, tp_float);
    PY_CHECK_ARG_TYPE(4, tp_float);
    int shapeId = py_toint(py_arg(0));
    float x = py_tofloat(py_arg(1));
    float y = py_tofloat(py_arg(2));
    float z = py_tofloat(py_arg(3));
    float mass = py_tofloat(py_arg(4));
    int id = engine.physics.addRigidBody(shapeId, btVector3(x, y, z), mass);
    py_newint(py_retval(), id);
    return true;
}

static bool pushBodyTransformFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    float bodyId = py_toint(py_arg(0));
    auto body = engine.physics.getRigidBody(bodyId);
    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);
    glm::mat4 matrix;
    auto matData = glm::value_ptr(matrix);
    trans.getOpenGLMatrix(matData);
    engine.xoMath.pushMat4(matrix);
    py_newnone(py_retval());
    return true;
}

void bindPhysics()
{
    // Bind engine functions
    auto mod = py_newmodule("xora_engine.physics");
    py_bindfunc(mod, "add_box_shape", addBoxShapeFn);
    py_bindfunc(mod, "add_sphere_shape", addSphereShapeFn);
    py_bindfunc(mod, "add_rigid_body", addRigidBodyFn);
    py_bindfunc(mod, "push_body_transform", pushBodyTransformFn);
}
