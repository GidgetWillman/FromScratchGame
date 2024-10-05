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

    //NOTE: Everything below this line is tutorial data that doesn't need to be in the final product

    //NOTE: Everything above this line is tutorial data that doesn't need to be in the final product

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    std::cout << "Thank you for a-playing my game!" << std::endl;
    glfwTerminate();
    return 0;
}