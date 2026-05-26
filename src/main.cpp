#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(int argc, char const *argv[])
{
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

    // Hello Triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f, 0.5f, 0.0f
    };

    // Triangle vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Setting the buffer we're going to modify to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /*
    glBufferData is a function specifically targeted to copy user-defined data into the currently bound buffer.
    Its first argument is the type of the buffer we want to copy data into:
    the vertex buffer object currently bound to the GL_ARRAY_BUFFER target.
    The second argument specifies the size of the data (in bytes) we want to pass to the buffer;
    a simple sizeof of the vertex data suffices. The third parameter is the actual data we want to send. 
    */

    // Crashing if glad couldn't load for some reason
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Setting viewport and adjusting it as user resizes the window
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // While loop to make window persistent
    while(!glfwWindowShouldClose(window)) {
        
        // Input
        processInput(window);

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swapping the end buffer to front buffer and checking events (inputs, crashes, etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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