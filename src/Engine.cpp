#include "Engine.hpp"


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
    _window.window = glfwCreateWindow(_window.width, _window.height, _window.name.c_str(), NULL, NULL);

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

    // Define the vertices and indices
    float vertices[] = {
        0.5f, 0.5f, 0.0f,       // top right
        0.5f, -0.5f, 0.0f,      // bottom right
        -0.5f, -0.5f, 0.0f,     // bottom left
        -0.5f, 0.5f, 0.0f       // top left
    };
    unsigned int indices[] = {
         3, 2, 1,       // first triangle
         3, 0, 1        // second triangle
    };

    // Generate and bind the buffers
    glGenBuffers(1, &Engine::graphics.VBO);
    glGenVertexArrays(1, &Engine::graphics.VAO);
    glGenBuffers(1, &Engine::graphics.EBO);

    glBindVertexArray(Engine::graphics.VAO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, Engine::graphics.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Engine::graphics.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set up vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO
    glBindVertexArray(0);
}

void Engine::render() {
    glUseProgram(Engine::default_shader_program);
    glBindVertexArray(Engine::graphics.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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