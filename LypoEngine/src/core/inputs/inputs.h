//
// Created by wstap on 8/3/2024.
//

#ifndef INPUTS_H
#define INPUTS_H
#include "GLFW/glfw3.h"

class InputManager {
public:
    InputManager(GLFWwindow* window) : window_(window) {}

    // Keyboard inputs
    bool isKeyPressed(int key) const {
        return glfwGetKey(window_, key) == GLFW_PRESS;
    }

    bool isKeyReleased(int key) const {
        return glfwGetKey(window_, key) == GLFW_RELEASE;

    }

    // Mouse inputs
    bool isMouseButtonPressed(int button) const {
        return glfwGetMouseButton(window_, button) == GLFW_PRESS;
    }

    bool isMouseButtonReleased(int button) const {
        return glfwGetMouseButton(window_, button) == GLFW_RELEASE;
    }

    void getMousePosition(double& xpos, double& ypos) const {
        glfwGetCursorPos(window_, &xpos, &ypos);
    }

    // ... add joystick functions if needed ...

private:
    GLFWwindow* window_;
};

#endif //INPUTS_H
