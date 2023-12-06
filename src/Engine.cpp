#include "Engine.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

bool is_fullscreen = false;
uint32_t texture;

void Engine::SetWindowParameters(std::string window_name, int window_width, int window_height) {
    _window.name = window_name;
    _window.width = window_width;
    _window.height = window_height;
}

void Engine::NewWindow() {

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Create Window
    if (_window.height == 0 || _window.width == 0) {
        // Get monitor and monitor res
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        // set window
        _window.window = glfwCreateWindow(mode->width, mode->height, _window.name.c_str(), glfwGetPrimaryMonitor(), 0);
        
        _window.width = mode->width;
        _window.height = mode->height;
    }
    else {
        _window.window = glfwCreateWindow(_window.width, _window.height, _window.name.c_str(), 0, 0);
    }

    // Check if Window is created
    if (_window.window == NULL) {
        std::cerr << "ERROR: Failed to create Window!" << std::endl;
        glfwTerminate();
        return;
    }

    // Make Current Window the context for all APIS
    glfwMakeContextCurrent(_window.window);

    // Setup Glad Loader
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "ERROR: Failed to Initialize OpenGL Loader!" << std::endl;
        return;
    }

    // Setup Viewport size to the size of the window
    glViewport(0, 0, _window.width, _window.height);

    // Adjust Viewport size when a window size change event occurs
    glfwSetFramebufferSizeCallback(_window.window, Engine::framebuffer_size_callback);

}

void Engine::Loop() {
    
    // Loop until close button pressed
    
    Engine::before_render();

    while (!glfwWindowShouldClose(_window.window)) {

        // GetKeyInputs
        processInput();

        // Change Window Color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Rendering here

        Engine::render();

        // Extra important functions

        glfwSwapBuffers(_window.window);
        
        glfwPollEvents();
    
    }

}

void Engine::GetWindowDebugInfo() {
    std::cout << "WINDOW ID => " << _window.window << std::endl;
    std::cout << "WINDOW NAME => " << _window.name << std::endl;
    std::cout << "WINDOW USER SET WIDTH => " << _window.width << std::endl;
    std::cout << "WINDOW USER SET HEIGHT => " << _window.height << std::endl;
}

Engine::ShaderProgram Engine::CompileShaders(Engine::Shader shaders) {

    uint32_t vertexShader, fragmentShader;
    int success;
    char infoLog[512];
    bool returnStatement = true;

    std::string vertexShaderString = (Engine::read_from_file(shaders.VertexShader));
    std::string fragmentShaderString = (Engine::read_from_file(shaders.FragmentShader));

    const char* vertexShaderSource = vertexShaderString.c_str();
    const char* fragmentShaderSource = fragmentShaderString.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl; 
        returnStatement = false;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        returnStatement = false;
    }

    uint32_t shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED!\n" << infoLog << std::endl;
        returnStatement = false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    Engine::ShaderProgram shader_program;
    shader_program.program = shaderProgram;
    shader_program.vertexShader = vertexShader;
    shader_program.fragmentShader = fragmentShader;
    shader_program.Passed = returnStatement;

    return shader_program;
}

void Engine::UseProgram(Engine::ShaderProgram shader_program) {
    Engine::default_shader_program = shader_program.program;
}

void Engine::DeleteProgram(Engine::ShaderProgram shader_program) {
    glDeleteShader(shader_program.fragmentShader);
    glDeleteShader(shader_program.vertexShader);
    glDeleteProgram(shader_program.program);
}

void Engine::SetDisplayModeToWireframe(bool setToWireframe) {
    if (setToWireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Engine::Exit() {
    // Terminate Window which will properly clear all the resources
    glfwTerminate();
}

// 
// 
// 
//
// Private Functions
// 
// 
// 
// 
//

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Engine::processInput() {

    // EXPLANAITION
    // This Function will close the window as soon as the Escape key is pressed

    if (glfwGetKey(_window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window.window, true);
}

void Engine::before_render() {

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &Engine::graphics.VAO);
    glGenBuffers(1, &Engine::graphics.VBO);
    glGenBuffers(1, &Engine::graphics.EBO);

    glBindVertexArray(Engine::graphics.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, Engine::graphics.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Engine::graphics.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture;

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;

    unsigned char* data = stbi_load("assets/tex/container.png", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

}

void Engine::render() {
    glUseProgram(Engine::default_shader_program);
    glBindVertexArray(Engine::graphics.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

std::string Engine::read_from_file(const std::string& filename) {
    
    std::ifstream file(filename);
    
    // Check for file existence
    if (!file.is_open()) {
        std::cerr << "Error reading file " << filename << "!" << std::endl;
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}