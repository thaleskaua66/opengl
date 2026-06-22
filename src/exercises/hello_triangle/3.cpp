#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

// Shaders
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

const char *fragmentShaderSourceYellow = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
int shaderCompileDebug(unsigned int* shader, std::string type);
int shaderProgramCompileDebug(unsigned int* shader);

int main(int argc, char const *argv[])
{
    // Some debug vars
    int success;
    char infoLog[512];

    // Initializing glfw and setting OPENGL version and profile
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Starting the window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Crashing if glad couldn't load for some reason
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Setting viewport and adjusting it as user resizes the window
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Shaders
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int fsYellow;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    fsYellow = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glShaderSource(fsYellow, 1, &fragmentShaderSourceYellow, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
    glCompileShader(fsYellow);

    // Checking shader errors
    shaderCompileDebug(&vertexShader, "VERTEX");
    shaderCompileDebug(&fragmentShader, "FRAGMENT");
    shaderCompileDebug(&fsYellow, "FRAGMENT");

    // Shader programs
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    unsigned int spYellow;
    spYellow = glCreateProgram();

    glAttachShader(spYellow, vertexShader);
    glAttachShader(spYellow, fsYellow);
    glLinkProgram(spYellow);

    // Debug
    shaderProgramCompileDebug(&shaderProgram);
    shaderProgramCompileDebug(&spYellow);

    // Cleaning shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fsYellow);

    // Triangle vertices
    float vertices[] = {
       0.0f, 0.0f, 0.0f, // center
      -1.0f, 0.0f, 0.0f, // left
      -0.5f, -1.0f, 0.0f
    };

    float vertices_second_triangle[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.5f, 1.0f, 0.0f
    };

    // Triangle vertex buffer object
    // VAOS
    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); // Setting the buffer we're going to modify to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Linking vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);

    // Second triangle vertex buffer object

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_second_triangle), vertices_second_triangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    // While loop to make window persistent
    while(!glfwWindowShouldClose(window)) {
        
        // Input
        processInput(window);

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[0]);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glUseProgram(spYellow);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        // Swapping the end buffer to front buffer and checking events (inputs, crashes, etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

// Resizing the viewport as the user resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Checking the inputs each frame
void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int shaderCompileDebug(GLuint* shader, std::string type) {
    int success;
    char infoLog[512];

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(*shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;

        return -1;
    }

    return 0;
}

int shaderProgramCompileDebug(unsigned int* shader){
    int success;
    char infoLog[512];

    glGetProgramiv(*shader, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(*shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM\n" << infoLog << std::endl;
    }

    return 0;
}