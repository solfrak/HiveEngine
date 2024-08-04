//
// Created by lapor on 7/19/2024.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "core/events/KeyEvent.h"
#include "core/inputs/inputs.h"
#include "core/layers/EventBus.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Lypo::EventBus& bus = Lypo::EventBus::getInstance();
    std::cout << "--------key_callback----------" << std::endl;
    std::cout   << "Key: "      << key << std::endl
                << "Scancode: " << scancode << std::endl
                << "Action: "   << action << std::endl
                << "Mods: "     << mods << std::endl;

    switch (action)
    {
        case GLFW_PRESS:
        {
            Lypo::KeyPressedEvent event(key, false);
            bus.dispatch(&event);
            break;
        }
        case GLFW_RELEASE:
        {
            Lypo::KeyReleasedEvent event(key);
            bus.dispatch(&event);
            break;
        }
        case GLFW_REPEAT:
        {
            Lypo::KeyPressedEvent event(key, true);
            bus.dispatch(&event);
            break;
        }
        default:
            break;
    }
}

int main(void)
{
    GLFWwindow* window;

    auto& bus = Lypo::EventBus::getInstance();

    auto eventHandler1 = new Lypo::RealNode(1);

    auto eventHandler1_1 = new Lypo::RealNode(11);
    auto eventHandler1_2 = new Lypo::RealNode(12);
    auto eventHandler1_3 = new Lypo::RealNode(13);

    auto eventHandler1_1_1 = new Lypo::RealNode(111);
    auto eventHandler1_1_2 = new Lypo::RealNode(112);

    auto eventHandler1_2_1 = new Lypo::RealNode(121);
    auto eventHandler1_2_2 = new Lypo::RealNode(122);


    eventHandler1_1->addChild(eventHandler1_1_1);
    eventHandler1_1->addChild(eventHandler1_1_2);

    eventHandler1_1->addChild(eventHandler1_2_1);
    eventHandler1_1->addChild(eventHandler1_2_2);

    eventHandler1->addChild(eventHandler1_1);
    eventHandler1->addChild(eventHandler1_2);
    eventHandler1->addChild(eventHandler1_3);

    bus.addEventListener(eventHandler1);


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Creates InputManager */
    InputManager im = InputManager(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Error in glad load" << std::endl;
        return -1;
    }

    /* Set the key callback */
    glfwSetKeyCallback(window, key_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        /* Simple test to query if a specific key is pressed */
        std::cout << im.isKeyPressed(68) << std::endl;
    }

    glfwTerminate();
    return 0;
}