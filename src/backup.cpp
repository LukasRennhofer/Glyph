#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Vertex Shader
const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUV;

out vec2 fragUV;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    fragUV = aUV;
}

)";

// Fragment Shader
const char* fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;

in vec2 fragUV; // You need to pass this from the vertex shader

uniform float u_radius; // corner radius in UV space
uniform vec4 u_color;   // background color

// Signed Distance Function for a rounded rectangle
float roundedBoxSDF(vec2 uv, float r) {
    vec2 dist = abs(uv - vec2(0.5)) - (vec2(0.5) - r);
    return length(max(dist, 0.0)) - r;
}

void main() {
    float dist = roundedBoxSDF(fragUV, u_radius);
    if (dist > 0.0) discard;

    FragColor = u_color;
}
)";

// Create simple rectangle in normalized device coords (NDC)
float quad[] = {
    // positions   // UVs (not used here)
    -0.5f,  0.5f,   0.0f, 1.0f,  // Top-left
     0.5f,  0.5f,   1.0f, 1.0f,  // Top-right
     0.5f, -0.5f,   1.0f, 0.0f,  // Bottom-right
    -0.5f, -0.5f,   0.0f, 0.0f   // Bottom-left
};

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};

int main() {
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Simple GUI Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Create shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Clean up shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up VAO/VBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // UV attribute (not used but in buffer)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f); // background
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        
        // Set the radius (in UV space: 0.0 - 0.5 is typical)
        float radius = 0.08f; // Adjust to make corners more or less round
        int radiusLoc = glGetUniformLocation(shaderProgram, "u_radius");
        glUniform1f(radiusLoc, radius);

        // Set window color (dark gray with full opacity)
        int colorLoc = glGetUniformLocation(shaderProgram, "u_color");
        glUniform4f(colorLoc, 0.1f, 0.1f, 0.1f, 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw the quad

        glfwSwapBuffers(window);
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}