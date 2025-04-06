/*
 *    				~ Glyph GUI ~
 *
 * Copyright (c) 2025 Lukas Rennhofer
 *
 * Licensed under the MIT License. See LICENSE file for more details.
 *
 * Author: Lukas Rennhofer
 * Date: 2025-03-27
 *
 * File: main.cpp
 * Last Change: Updated the projects docs
 */

 #include "glyph.h"
 #include <glad/glad.h>
 #include <GLFW/glfw3.h>
 #include <glm/glm.hpp>
 #include <glm/gtc/matrix_transform.hpp>
 #include <glm/gtc/type_ptr.hpp>
 #include <iostream>
 

 int main() {

     glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f); // Change values as needed
     // Init GLFW
     glfwInit();
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
     // Create window
     GLFWwindow* window = glfwCreateWindow(800, 600, "Draggable Rectangle", NULL, NULL);
     if (!window) {
         std::cerr << "Failed to create GLFW window\n";
         glfwTerminate();
         return -1;
     }

     glfwMakeContextCurrent(window);
     gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

     glyph::Renderer::Rectangle rect;
     rect.setPosition(200, 100);
     rect.setSize(50, 50);
     rect.setColor(1.0f, 3.0f, 1.0f, 0.5f); // semi-transparent red
     rect.setBorderRadius(200.0f);

     while (!glfwWindowShouldClose(window)) {
         glClear(GL_COLOR_BUFFER_BIT);
        
         rect.render(projection);

         glfwSwapBuffers(window);
         glfwPollEvents();
     }
 
     glfwDestroyWindow(window);
     glfwTerminate();
     return 0;
}
 
 