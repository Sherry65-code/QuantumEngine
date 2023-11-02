#include "Engine.hpp"
#include <vector>
#include <time.h>

int main(int argc, char* argv[]) {

    // Intialize
    Engine engine;

    // Setup Shaders
    Engine::Shader shader;
    
    // Put all Shader Paths
    Engine::Shader Shaders[] = {
        {
            "assets/Shader1.vs",
            "assets/Shader1.fs"
        }
    };
    
    // Get Length of Shaders[]
    const uint32_t ShaderCount = sizeof(Shaders) / sizeof(Shaders[0]);

    // Make a Vector in order to manage all the shader programs
    std::vector<Engine::ShaderProgram> shaderPrograms;
    
    // Basic Window Setup and Parameters setup
    engine.SetWindowParameters("Quantum Engine", 800, 600);

    // Open Window
    engine.NewWindow();
    
    // Start Shader Compilation
    for (int x = 0; x < ShaderCount; x++) {

        // Show compilation message
        std::cout << "Compiling Shader (" << (x + 1) << " of " << ShaderCount << ")..." << std::endl;

        // Start Clock
        clock_t t_start = clock();

        // Push to vector the shader id after compilation
        shaderPrograms.push_back(engine.CompileShaders(Shaders[x]));
        
        // Get Clock Differentiation
        double t_end = (double)(clock() - t_start) / CLOCKS_PER_SEC;

        // Check for any errors
        if (shaderPrograms[x].Passed) {
            std::cout << "Shader " << (x + 1) << " compiled in " << t_end << "secs" << std::endl;
        }
        else {
            std::cerr << "Shader " << (x + 1) << " failed to Compile!" << std::endl;
        }

    }

    // PREVIEW // Use the first shader
    engine.UseProgram(shaderPrograms[0]);

    // DEBUG // To change view mode to wireframe
    engine.SetDisplayModeToWireframe(false);

    // Main Loop For Program
    engine.Loop();

    // Cleanup
    
    std::cout << "Cleaning Up..." << std::endl;

    for (int x = 0; x < ShaderCount; x++) {
        
        engine.DeleteProgram(shaderPrograms[x]);
        
        std::cout << "Deleted Program " << (x + 1) << std::endl;
    
    }
    
    // Exit by closing the window
    engine.Exit();

}