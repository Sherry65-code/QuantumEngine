#include "Engine.hpp"
#include <time.h>

int main() {

    Engine engine;

    // Shaders Compilation
    Engine::Shader shader1;
    Engine::ShaderProgram shaderprogram1;
    shader1.VertexShader = "assets/Shader1.vs";
    shader1.FragmentShader = "assets/Shader1.fs";
    engine.SetWindowParameters("Hello, World!", 800, 600);
    engine.NewWindow();
    clock_t tStart = clock();
    std::cout << "Compiling Shaders...";
    shaderprogram1 = engine.CompileShaders(shader1);
    std::cout << "Compilation Over!\nTime Taken to Compile Shaders => " << (double)(clock()-tStart)/CLOCKS_PER_SEC << "secs";
    engine.UseProgram(shaderprogram1);
    engine.SetDisplayModeToWireframe(false);
    engine.Loop();
    engine.DeleteProgram(shaderprogram1);
    engine.Exit();
}