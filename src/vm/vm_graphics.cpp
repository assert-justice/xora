#include "vm_graphics.hpp"
#include "engine/engine.hpp"

static bool newTextureFromFileFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_str);
    auto fpath = py_tostr(py_arg(0));
    int id = engine.graphics.loadImage(fpath);
    py_newint(py_retval(), id);
    return true;
}

static bool drawTextureFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(3);
    PY_CHECK_ARG_TYPE(0, tp_int);
    PY_CHECK_ARG_TYPE(1, tp_float);
    PY_CHECK_ARG_TYPE(2, tp_float);
    int texId = py_toint(py_arg(0));
    float x = py_tofloat(py_arg(1));
    float y = py_tofloat(py_arg(2));
    engine.graphics.drawImage(texId, x, y);
    py_newnone(py_retval());
    return true;
}
static bool drawTextureExtFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(12);
    PY_CHECK_ARG_TYPE(0, tp_int); // Handle id
    PY_CHECK_ARG_TYPE(1, tp_float); // x
    PY_CHECK_ARG_TYPE(2, tp_float); // y
    PY_CHECK_ARG_TYPE(3, tp_float); // width
    PY_CHECK_ARG_TYPE(4, tp_float); // height
    PY_CHECK_ARG_TYPE(5, tp_float); // sx
    PY_CHECK_ARG_TYPE(6, tp_float); // sy
    PY_CHECK_ARG_TYPE(7, tp_float); // sw
    PY_CHECK_ARG_TYPE(8, tp_float); // sh
    PY_CHECK_ARG_TYPE(9, tp_float); // ox
    PY_CHECK_ARG_TYPE(10, tp_float); // oy
    PY_CHECK_ARG_TYPE(11, tp_float); // angle
    int texId = py_toint(py_arg(0));
    float x = py_tofloat(py_arg(1));
    float y = py_tofloat(py_arg(2));
    float width = py_tofloat(py_arg(3));
    float height = py_tofloat(py_arg(4));
    float sx = py_tofloat(py_arg(5));
    float sy = py_tofloat(py_arg(6));
    float sw = py_tofloat(py_arg(7));
    float sh = py_tofloat(py_arg(8));
    float ox = py_tofloat(py_arg(9));
    float oy = py_tofloat(py_arg(9));
    float angle = py_tofloat(py_arg(9));
    engine.graphics.drawImageExt(texId, x, y, width, height, sx, sy, sw, sh, ox, oy, angle);
    py_newnone(py_retval());
    return true;
}

static bool getTextureDimensionsFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int texId = py_toint(py_arg(0));
    auto tex = engine.graphics.getTexture(texId);
    py_Ref r = py_retval();
    py_newtuple(r, 2);
    py_newint(py_tuple_getitem(r, 0), tex->width);
    py_newint(py_tuple_getitem(r, 1), tex->height);
    return true;
}

void bindGraphics(){
    auto mod = py_newmodule("xora_engine.graphics");
    py_bindfunc(mod, "new_texture_from_file", newTextureFromFileFn);
    py_bindfunc(mod, "draw_texture", drawTextureFn);
    py_bindfunc(mod, "draw_texture_ext", drawTextureExtFn);
    py_bindfunc(mod, "get_texture_dimensions", getTextureDimensionsFn);
}