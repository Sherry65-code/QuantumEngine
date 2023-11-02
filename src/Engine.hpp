#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Engine {

    private:
    typedef struct Window {
        GLFWwindow* window;
        std::string name;
        int width;
        int height;
    } Window;
    typedef uint32_t DefaultShaderProgram;
    typedef struct Graphics {
        uint32_t VAO;
        uint32_t VBO;
        uint32_t EBO;
    } Graphics;
    Engine::Window _window;
    Engine::DefaultShaderProgram default_shader_program;
    Engine::Graphics graphics;

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void processInput();
    void render();
    void before_render();
    std::string read_from_file(const std::string& filename);

    public:
    typedef struct Shader {
        std::string VertexShader;
        std::string FragmentShader;
    } Shader;
    typedef struct ShaderProgram {
        uint32_t program;
        uint32_t vertexShader;
        uint32_t fragmentShader;
        bool Passed;
    } ShaderProgram;

    Engine::ShaderProgram CompileShaders(Engine::Shader shaders);
    void UseProgram(Engine::ShaderProgram shader_program);
    void DeleteProgram(Engine::ShaderProgram shader_program);
    void SetWindowParameters(std::string window_name, int window_width, int window_height);
    void NewWindow();
    void Loop();
    void GetWindowDebugInfo();
    void SetDisplayModeToWireframe(bool setToWireframe);
    void Exit();
};