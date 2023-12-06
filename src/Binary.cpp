#include "Engine.hpp"
#include <vector>
#include <time.h>
#include <string>

bool static is_integer(std::string str) {
    try {
        std::stoi(str);
        return true;
    }
    catch (std::invalid_argument const& e) {
        return false;
    }
}

int main(int argc, char* argv[]) {

    // Convert arguments from Pointer Array to std::string
    std::vector<std::string> args(argv, argv + argc);
    std::string current;

    // Some Variables for window declaration
    bool is_fullscreen = false;
    bool is_debug = false;
    int win_h = 600;
    int win_w = 800;
    std::string win_nm = "Quantum Engine Demo";

    for (int i = 1; i < argc; i++) {
        current = args.at(i);
        
        if (current == "-debug") {
            is_debug = true;
        }
        else if (current == "-nodebug") {
            is_debug = false;
        }
        else if (current == "-windowed" || current == "-nofullscreen") {
            is_fullscreen = false;
        }
        else if (current == "-fullscreen" || current == "-nowindow") {
            is_fullscreen = true;
        }
        else if (current == "-w") {
            if (is_integer(args.at(i + 1)))
                win_w = std::stoi(args.at(i + 1));
            else {
                std::cout << args.at(i + 1) << " is not a integer." << std::endl;
            }
            i += 1;
        }
        else if (current == "-h") {
            if (is_integer(args.at(i + 1))) {
                win_h = std::stoi(args.at(i + 1));
            }
            else {
                std::cout << args.at(i + 1) << " is not a integer." << std::endl;
            }
            i += 1;
        }
        else if (current == "-help") {
            std::cout << "ARGUMENTS:\n-debug: to enable debugging messages\n-nodebug: to disable debugging messages (default)\n-windowed\\-nofullscreen: to open in windowed mode (default)\n-fullscreen\\-nowindow: to open in fullscreen mode\n-w <INTEGER>: to set window width\n-h <INTEGER>: to set window height\n";
            exit(-1);
        }
        else {
            std::cout << "ERROR: \"" << current << "\" is not a argument!" << std::endl;
            exit(-1);
        }


    }

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
    if (is_fullscreen) {
        engine.SetWindowParameters(win_nm, 0, 0);
    }
    else {
        engine.SetWindowParameters(win_nm, win_w, win_h);
    }

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