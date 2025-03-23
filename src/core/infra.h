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
 * File: infra.h
 * Last Change: Added Command Options
 */

#pragma once

#include <string>
#include <vector>
#include <map>

namespace glyph {
    std::vector<std::string> findDocumentationFolders(const std::string& directory);
    bool generateGlyphFile(const std::string& filePath, const std::string& content);
    std::map<std::string, std::string> interpretGlyphFile(const std::string& filePath);
} // NAMESPACE GLYPH
