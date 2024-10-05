#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) //resize the viewport if the user resizes the window
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int, char**)
{
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(800, 600, "THE BUMBLY BINGUS ENGINE", NULL, NULL);
    if(!window){std::cout << "Failed to create GLFW Window" << std::endl; glfwTerminate(); return -1;}
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Couldn't load OpenGL" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glViewport(0, 0, 800, 600); //first two parameters set lower left corner, then width and height of the rendering window (currently matching the size of the GLFW window)
    //Note: OpenGL uses screen coordinates between -1 and 1, the above maps the real pixel range.

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //adjust the viewport based on the window size if the user resizes the window
    
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    //NOTE: Everything below this line is tutorial data that may not need to be in the final product
    float vertices[] = { //triangle vertex description in xyz, note that we can cleanly format the data if we so please
        -0.5f, -0.5f, 0.0f, //bottom left
         0.5f, -0.5f, 0.0f, //bottom right
         0.0f,  0.5f, 0.0f  //top
    }; //DON'T FORGET THE SEMICOLON YOU MORON

    unsigned int VBO; //vertex buffer object, which is a GL_ARRAY_BUFFER
    glGenBuffers(1, &VBO); //generate a buffer ID
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind VBO to GL_ARRAY_BUFFER, so any buffer calls to GL_ARRAY_BUFFER will configure VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copy the vertices into VBO on the graphics card, flag it as Static since the data is set once and used many times
                                                                               //GL_DYNAMIC_DRAW would place it in memory that allows faster writes
    //vertex shader
    const char *vertexShaderSource = "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    //NOTE: Everything above this line is tutorial data that may not need to be in the final product

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    std::cout << "Thanks for playing!!" << std::endl;
    glfwTerminate();
    return 0;
}