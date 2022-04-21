#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

Window::Window(int screen_width, int screen_height, const char* title) :
    width(screen_width), height(screen_height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
}

void Window::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

bool Window::isKeyPress(GLenum key_code)
{
    return glfwGetKey(window, key_code) == GLFW_PRESS;
}

bool Window::isKeyRelease(GLenum key_code)
{
    return glfwGetKey(window, key_code) == GLFW_RELEASE;
}

bool Window::isRunning()
{
    return !glfwWindowShouldClose(window);
}

int Window::getWidth()
{
    return width;
}

int Window::getHeight()
{
    return height;
}

int Window::getKey(int key_code)
{
    return glfwGetKey(window, key_code);
}

void Window::close()
{
    glfwSetWindowShouldClose(window, true);
}

double Window::getTime()
{
    return glfwGetTime();
}

float Window::getDeltaTime()
{
    current_time = getTime();
    auto delta_time = current_time - last_time;
    last_time = current_time;
    return delta_time;
}

void Window::clear()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swap()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::getMousePosition(double& x, double& y)
{
    glfwGetCursorPos(window, &x, &y);
}

void Window::getMoiseOffset(double& x, double& y)
{
    double curr_x, curr_y;
    glfwGetCursorPos(window, &curr_x, &curr_y);
    x = (curr_x - prev_x) * (inverse_mouse_x ? -1 : 1);
    y = (curr_y - prev_y) * (inverse_mouse_y ? -1 : 1);
    prev_x = curr_x;
    prev_y = curr_y;
}
