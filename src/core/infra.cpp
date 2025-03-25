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
 * File: infra.cpp
 * Last Change: Added Command Options
 */

#include "infra.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <map>

namespace glyph
{

    // Function to search for folders named 'doc', 'docs', 'documentation', etc.
    std::vector<std::string> findDocumentationFolders(const std::string &directory)
    {
        std::vector<std::string> folders;
        std::vector<std::string> potentialFolders = {"doc", "docs", "documentation"};

        for (const auto &entry : std::filesystem::directory_iterator(directory))
        {
            for (const auto &folder : potentialFolders)
            {
                if (entry.is_directory() && entry.path().filename() == folder)
                {
                    folders.push_back(entry.path().string());
                }
            }
        }

        return folders;
    }

    // Function to generate a .glyph file in a folder named .glyph
    bool generateGlyphFile(const std::string &filePath, const std::string &content)
    {
        std::string glyphFolder = ".glyph";
        std::filesystem::create_directory(glyphFolder);

        std::ofstream outFile(filePath + "/" + glyphFolder);
        if (!outFile)
        {
            std::cerr << "Error: Could not create file " << filePath + "/" + glyphFolder << "\n";
            return false;
        }

        outFile << content;
        outFile.close();
        return true;
    }

    // Function to interpret .glyph files (like BANNER = src/banner.jpg)
    std::map<std::string, std::string> interpretGlyphFile(const std::string &filePath)
    {
        std::map<std::string, std::string> definitions;
        std::ifstream inFile(filePath + ".glyph/");
        std::string line;

        if (!inFile)
        {
            std::cerr << "Error: Could not open file " << ".glyph/" + filePath << "\n";
            return definitions;
        }

        while (std::getline(inFile, line))
        {
            if (line.empty() || line[0] == '#')
            {
                continue;
            }

            size_t eqPos = line.find('=');
            if (eqPos != std::string::npos)
            {
                std::string key = line.substr(0, eqPos);
                std::string value = line.substr(eqPos + 1);

                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);

                definitions[key] = value;
            }
        }

        inFile.close();
        return definitions;
    }
} // NAMESPACE GLYPH
