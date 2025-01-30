#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils/fs.hpp"
#include "engine/module.hpp"
#include "utils/store.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "mesh.hpp"

class Graphics: public Module{
    public:
    // General
    void setStats(std::string name, int width, int height, int mode);
    int getWindowWidth(){return windowWidth;}
    int getWindowHeight(){return windowHeight;}
    void drawBegin();
    void drawEnd();
    bool shouldClose();
    void clear();
    GLFWwindow* getWindow();
    // Textures
    int newTexture(int width, int height, unsigned char* data);
    void freeTexture(int id);
    int loadImage(std::string path);
    bool saveTexture(const char* path, int id);
    Texture* getTexture(int id);
    void setRenderTarget(int id);
    // Shaders
    int newShader(std::string vertexSource, std::string fragmentSource);
    void freeShader(int id);
    Shader* getShader(int id);
    // Meshes
    int newMesh(std::vector<float> &data, std::vector<int> attribSizes);
    void freeMesh(int id);
    Mesh* getMesh(int id);
    protected:
    bool initInternal();
    void cleanupInternal();
    private:
    GLFWwindow* window = NULL;
    std::string windowName = "Xora";
    int windowWidth = 640;
    int windowHeight = 480;
    int windowMode = 0;
    Store<Texture> textureStore;
    Store<Shader> shaderStore;
    Store<Mesh> meshStore;
};