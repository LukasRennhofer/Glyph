cmake_minimum_required(VERSION 3.10)

# Project name
project(glyph)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Comp Flags
add_compile_options(-w)

# Include directories
include_directories(src/external)

set(SOURCES
    # src
    src/main
    # compiler
    src/compiler/mdtransform.cpp
    # core
    src/core/version.cpp
    src/core/command.cpp
    src/core/infra.cpp
)

if(WIN32)
    # Windows-specific setup
    message(STATUS "Compiling for LWindows")
    
elseif(UNIX)
    # Linux-specific setup
    message(STATUS "Compiling for Linux")

endif()
# Create the executable
add_executable(glyph ${SOURCES})

# Link platform-specific libraries
# if(WIN32)
#     target_link_libraries(glyph ${WINDOWS_LIBRARIES})
# elseif(UNIX)
#     target_link_libraries(glyph ${LINUX_LIBRARIES})
# endif()

target_compile_options(glyph PRIVATE -Wall -Wextra)
