/*
 *    				~ Glyph Documentation Compiler ~
 *
 * Copyright (c) 2025 Lukas Rennhofer
 *
 * Licensed under the MIT License. See LICENSE file for more details.
 *
 * Author: Lukas Rennhofer
 * Date: 2025-03-23
 *
 * File: command.cpp
 * Last Change: Added Command Options
 */

#include "command.h"

namespace glyph::command
{
    void printHelp()
    {
        std::cout << "\e[1;35m" << "Glyph" << "\e[0;37m" << " - A lightweight documentation generator and compiler.\n";
        std::cout << "Usage: ./glyph [options]\n\n";
        std::cout << "Options:\n";
        std::cout << "  -h, --help            Show this help message\n";
        std::cout << "  -v, --version         Show version info\n";
        std::cout << "  -i <input.md>         Specify input Markdown file (default: resources/test.md)\n";
        std::cout << "  -o <output.html>      Specify output HTML file (default: output/index.html)\n";
    }

    void printVersion()
    {
        std::cout << "\e[1;35m" << "Glyph" << "\e[0;37m" << " version " << glyph::version::GetVersionString() << "\n";
    }
} // NAMESPACE GLYPH::COMMAND