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
 * File: version.h
 * Last Change: Added Command Options
 */

#pragma once

#include <string>

namespace glyph::version
{

    // return: const int major
    int GetMajor();
    // return: const int minor
    int GetMinor();
    // return: const int revision
    int GetRevision();

    std::string GetVersionString();
} // NAMESPACE GLYPH::COMMAND