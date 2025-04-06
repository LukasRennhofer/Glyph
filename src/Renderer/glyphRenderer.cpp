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
 * File: glyphRenderer.cpp
 * Last Change: Updated the projects docs
*/

#include "glyphRenderer.h"

namespace glyph::Renderer
{
    // =========== SHADERS ===============
    extern const char* vertexShaderSrcQUAD;
    extern const char* fragmentShaderSrcQUAD;
    // Simple full-quad vertex shader
    const char* vertexShaderSrcQUAD = R"(
    #version 330 core
    layout(location = 0) in vec2 aPos;
    uniform mat4 uProjection;  // Add uniform for projection matrix
    out vec2 vUV;

    void main() {
        gl_Position = uProjection * vec4(aPos, 0.0, 1.0);  // Apply the projection matrix to the vertex position
        vUV = aPos * 0.5 + 0.5;
    }
    )";
    
    // Fragment shader supporting border radius
    const char* fragmentShaderSrcQUAD = R"(
    #version 330 core
    in vec2 vUV;
    out vec4 FragColor;

    uniform vec2 uSize;
    uniform float uRadius;
    uniform vec4 uColor;

    float rectWithRadius(vec2 uv, vec2 size, float radius) {
        vec2 dist = abs(uv * size - size * 0.5) - (size * 0.5 - vec2(radius));
        float d = length(max(dist, 0.0)) - radius;
        return d;
    }

    void main() {
        float d = rectWithRadius(vUV, uSize, uRadius);
        float alpha = smoothstep(0.01, 0.0, d);
        FragColor = vec4(uColor.rgb, uColor.a * alpha);
    }
    )";

    // =========== Rectangle ===============
    Rectangle::Rectangle() {
        position = glm::vec2(0.0f);
        size = glm::vec2(100.0f, 100.0f);
        color = glm::vec4(1.0f);
        borderRadius = 30.0f;
        init();
    }
    
    Rectangle::~Rectangle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
    }
    
    void Rectangle::init() {
        // Full screen quad
        float vertices[] = {
            -1.0f,  1.0f,   0.0f, 1.0f,  // Top-left
             1.0f,  1.0f,   1.0f, 1.0f,  // Top-right
             1.0f, -1.0f,   1.0f, 0.0f,  // Bottom-right
            -1.0f, -1.0f,   0.0f, 0.0f   // Bottom-left
        };
        
        GLuint indices[] = { 0, 1, 2, 2, 3, 0 };
    
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        GLuint EBO;
        glGenBuffers(1, &EBO);
    
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glBindVertexArray(0);
    
        shaderProgram = compileShaderProgram();
    }
    
    GLuint Rectangle::compileShaderProgram() {
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertexShaderSrcQUAD, nullptr);
        glCompileShader(vs);
    
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragmentShaderSrcQUAD, nullptr);
        glCompileShader(fs);
    
        GLuint program = glCreateProgram();
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
    
        glDeleteShader(vs);
        glDeleteShader(fs);
    
        return program;
    }
    
    void Rectangle::setPosition(float x, float y) {
        position = glm::vec2(x, y);
    }
    
    void Rectangle::setSize(float w, float h) {
        size = glm::vec2(w, h);
    }
    
    void Rectangle::setColor(float r, float g, float b, float a) {
        color = glm::vec4(r, g, b, a);
    }
    
    void Rectangle::setBorderRadius(float radius) {
        borderRadius = radius;
    }
    
    void Rectangle::render(const glm::mat4& projectionMatrix) {
        glUseProgram(shaderProgram);
    
        // Send the projection matrix to the shader
        GLint uProjection = glGetUniformLocation(shaderProgram, "uProjection");
        glUniformMatrix4fv(uProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    
        // Send the size, radius, and color to the shader
        GLint uSize = glGetUniformLocation(shaderProgram, "uSize");
        glUniform2f(uSize, size.x, size.y);
    
        GLint uRadius = glGetUniformLocation(shaderProgram, "uRadius");
        glUniform1f(uRadius, borderRadius);
    
        GLint uColor = glGetUniformLocation(shaderProgram, "uColor");
        glUniform4fv(uColor, 1, glm::value_ptr(color));
    
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
} // namespace glyph::Renderer
