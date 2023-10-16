#include "Engine.hpp"
#include <time.h>

int main() {

    Engine engine;

    // Shaders Compilation
    Engine::Shader shader1;
    Engine::ShaderProgram shaderprogram1;
    shader1.VertexShader = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    shader1.FragmentShader = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

    engine.SetWindowParameters("Hello, World!", 800, 600);
    engine.NewWindow();
    shaderprogram1 = engine.CompileShaders(shader1);
    std::cout << "Compiling Shaders...";
    clock_t tStart = clock();
    std::cout << "Compilation Over!\nTime Taken to Compile Shaders => " << (double)(clock()-tStart)/CLOCKS_PER_SEC << "secs";
    engine.UseProgram(shaderprogram1);
    engine.SetDisplayModeToWireframe(true);
    engine.Loop();
    engine.DeleteProgram(shaderprogram1);
}