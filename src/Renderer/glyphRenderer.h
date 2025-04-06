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
 * File: glyphRenderer.h
 * Last Change: Updated the projects docs
*/

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace glyph::Renderer
{
    // =========== SHADERS ===============
    extern const char* vertexShaderSrcQUAD;
    extern const char* fragmentShaderSrcQUAD;

    enum class RenderBackend {
        OpenGL,
        Vulkan // TODO
    };
    
    // =========== Rectangle ===============
    class Rectangle {
        public:
            Rectangle();
            ~Rectangle();
        
            void setPosition(float x, float y);
            void setSize(float width, float height);
            void setColor(float r, float g, float b, float a = 1.0f);
            void setBorderRadius(float radius);
        
            void render(const glm::mat4& projectionMatrix);
        
        private:
            GLuint VAO, VBO;
            GLuint shaderProgram;
            glm::vec2 position;
            glm::vec2 size;
            glm::vec4 color;
            float borderRadius;
        
            void init();
            GLuint compileShaderProgram();
        };
} // namespace glyph::Renderer
