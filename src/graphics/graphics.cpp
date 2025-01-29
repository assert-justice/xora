#include "graphics.hpp"
#include <iostream>
#include "stb_image.h"
#include "stb_image_write.h"
#include "utils/fs.hpp"

void Graphics::drawBegin()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    clear();
}

void Graphics::drawEnd()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Graphics::shouldClose()
{
    return glfwWindowShouldClose(window);
}

void Graphics::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLFWwindow* Graphics::getWindow()
{
    return window;
}

int Graphics::newTexture(int width, int height, unsigned char *data)
{
    auto ptr = new Texture(width, height, data);
    return textureStore.add(ptr);
}

void Graphics::freeTexture(int id)
{
    textureStore.del(id);
}

int Graphics::loadImage(std::string path)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4); 
    if(!data) return -1;
    int id = newTexture(width, height, data);
    stbi_image_free(data);
    return id;
}

bool Graphics::saveTexture(const char *path, int id)
{
    Texture* tex = nullptr;
    tex = textureStore.get(id);
    // stbi_flip_vertically_on_write(id == -1);
    if(tex == nullptr) return false;
    auto data = (uint8_t*)calloc(tex->width * tex->height * 4, sizeof(uint8_t));
    glReadPixels(0, 0, tex->width, tex->height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_write_png(path, tex->width, tex->height, 4, data, 4 * tex->width);
    free(data);
    return true;
}

Texture *Graphics::getTexture(int id)
{
    auto tex = textureStore.get(id);
    if(tex == nullptr){
        std::cout << "Invalid texture id '" << id << "'" << std::endl;
    }
    return tex;
}

void Graphics::setRenderTarget(int id)
{
    if(id == -1){
        // reset render target
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    auto fb = getTexture(id);
    fb->useTarget();
}

int Graphics::newShader(std::string vertexSource, std::string fragmentSource){
    auto shader = new Shader();
    bool hasError = false;
    shader->initialize(&hasError, vertexSource, fragmentSource);
    if(hasError) return -1;
    return shaderStore.add(shader);
}

void Graphics::freeShader(int id){
    shaderStore.del(id);
}

Shader* Graphics::getShader(int id){
    auto shader = shaderStore.get(id);
    if(shader == nullptr){
        std::cout << "Invalid shader id '" << id << "'" << std::endl;
    }
    return shader;
}

int Graphics::newMesh(std::vector<float> &data, std::vector<int> attribSizes)
{
    auto mesh = new Mesh(data, attribSizes);
    return meshStore.add(mesh);
}

void Graphics::freeMesh(int id)
{
    meshStore.del(id);
}

Mesh *Graphics::getMesh(int id)
{
    if(meshStore.has(id)) return meshStore.get(id);
    std::cout << "Invalid mesh id '" << id << "'" << std::endl;
    return nullptr;
}

bool Graphics::initInternal()
{
    if(!glfwInit()){
        std::cout << "Failed to init glfw" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "Xora", NULL, NULL);
    if (!window){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwSwapInterval(1);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST); 
    return true;
}

void Graphics::cleanupInternal(){
    glfwTerminate();
}