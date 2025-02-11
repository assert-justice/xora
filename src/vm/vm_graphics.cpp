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

static bool newShaderFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    PY_CHECK_ARG_TYPE(1, tp_str);
    auto vertSrc = py_tostr(py_arg(0));
    auto fragSrc = py_tostr(py_arg(1));
    py_newint(py_retval(), engine.graphics.newShader(vertSrc, fragSrc));
    return true;
}

static bool getShaderUniformLocationFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    PY_CHECK_ARG_TYPE(1, tp_str);
    auto shaderId = py_toint(py_arg(0));
    auto name = py_tostr(py_arg(1));
    auto shader = engine.graphics.getShader(shaderId);
    if(!shader){
        return py_exception(tp_AttributeError, "Invalid shader id");
    }
    py_newint(py_retval(), shader->getUniformLocation(name));
    return true;
}

static bool bindShaderFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    auto shaderId = py_toint(py_arg(0));
    auto shader = engine.graphics.getShader(shaderId);
    if(!shader){
        return py_exception(tp_AttributeError, "Invalid shader id");
    }
    shader->use();
    py_newnone(py_retval());
    return true;
}

static bool bindTextureFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    auto textureId = py_toint(py_arg(0));
    auto tex = engine.graphics.getTexture(textureId);
    if(!tex){
        return py_exception(tp_AttributeError, "Invalid texture id");
    }
    tex->use();
    py_newnone(py_retval());
    return true;
}

static bool setShaderUniformMat4x4(int argc, py_Ref argv){
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_int);
    PY_CHECK_ARG_TYPE(1, tp_int);
    int shaderId = py_toint(py_arg(0));
    int loc = py_toint(py_arg(1));
    auto shader = engine.graphics.getShader(shaderId);
    if(!shader){
        return py_exception(tp_AttributeError, "Invalid shader id");
    }
    shader->setUniform(loc, engine.xoMath.popMat4());
    py_newnone(py_retval());
    return true;
}

static bool newMeshFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_list);
    PY_CHECK_ARG_TYPE(1, tp_list);
    auto dataList = py_arg(0);
    auto attribList = py_arg(1);
    std::vector<float> data;
    std::vector<int> attribSizes;
    int len = py_list_len(dataList);
    for(int i = 0; i < len; i++){
        float item = py_tofloat(py_list_getitem(dataList, i));
        data.push_back(item);
    }
    for(int i = 0; i < py_list_len(attribList); i++){
        float item = py_toint(py_list_getitem(attribList, i));
        attribSizes.push_back(item);
    }
    int id = engine.graphics.newMesh(data, attribSizes);
    py_newint(py_retval(), id);
    return true;
}

static bool drawMeshFn(int argc, py_Ref argv){
    PY_CHECK_ARGC(1);
    PY_CHECK_ARG_TYPE(0, tp_int);
    int meshId = py_toint(py_arg(0));
    auto mesh = engine.graphics.getMesh(meshId);
    if(!mesh){
        return py_exception(tp_AttributeError, "Invalid mesh id");
    }
    mesh->draw();
    py_newnone(py_retval());
    return true;
}

void bindGraphics(){
    auto mod = py_newmodule("xora_engine.graphics");
    py_bindfunc(mod, "new_texture_from_file", newTextureFromFileFn);
    py_bindfunc(mod, "draw_texture", drawTextureFn);
    py_bindfunc(mod, "draw_texture_ext", drawTextureExtFn);
    py_bindfunc(mod, "get_texture_dimensions", getTextureDimensionsFn);
    py_bindfunc(mod, "new_shader", newShaderFn);
    py_bindfunc(mod, "get_shader_uniform_location", getShaderUniformLocationFn);
    py_bindfunc(mod, "bind_shader", bindShaderFn);
    py_bindfunc(mod, "bind_texture", bindTextureFn);
    py_bindfunc(mod, "set_shader_uniform_mat4x4", setShaderUniformMat4x4);
    py_bindfunc(mod, "new_mesh", newMeshFn);
    py_bindfunc(mod, "draw_mesh", drawMeshFn);
}