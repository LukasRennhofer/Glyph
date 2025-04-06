cmake_minimum_required(VERSION 3.10)

# Project name
project(Glyph)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Comp Flags
add_compile_options(-w)

# Include directories
include_directories(External)

set(SOURCES
    # src
    main.cpp

    # External
    External/glad.c

    #Renderer
    Renderer/glyphRenderer.cpp
)

add_library(GlyphLib STATIC ${SOURCES})
target_include_directories(GlyphLib PUBLIC src External)

if(WIN32)
    message(STATUS "Compiling for Windows")

    set(WINDOWS_LIBRARIES
        mingw32
        opengl32
        gdi32
        user32
        imm32
        shell32
        freetype
    )


    # Find GLFW
    find_package(glfw3 REQUIRED)

    target_link_libraries(GlyphLib glfw ${WINDOWS_LIBRARIES})
    
elseif(UNIX)
    # Linux-specific setup
    message(STATUS "Compiling for Linux")

endif()

# === Create the Executable ===
add_executable(Glyph main.cpp)

# Link the engine library to the executable
target_link_libraries(Glyph GlyphLib)

# Optional: Compiler warnings for the main executable
target_compile_options(Glyph PRIVATE -Wall -Wextra)
