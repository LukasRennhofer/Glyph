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
 * File: main.cpp
 * Last Change: Added Command Options
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

#include <vector>
#include <stack>
#include <queue>
#include <regex>

#include "compiler/mdtransform.h"
#include "core/command.h"
#include "core/infra.h"

int main(int argc, char *argv[])
{
	std::string inputFile = "resources/test.md";
	std::string outputFile = "output/index.html";

	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		if (arg == "-h" || arg == "--help")
		{
			glyph::command::printHelp();
			return 0;
		}
		else if (arg == "-v" || arg == "--version")
		{
			glyph::command::printVersion();
			return 0;
		}
		else if (arg == "-i" && i + 1 < argc)
		{
			inputFile = argv[++i];
		}
		else if (arg == "-o" && i + 1 < argc)
		{
			outputFile = argv[++i];
		}
		else if (arg == "init")
		{ // INIT COMMAND
			std::vector<std::string> docFolders = glyph::findDocumentationFolders(std::filesystem::current_path().string());
			if (docFolders.size() != 0)
			{
				glyph::generateGlyphFile(docFolders.at(0), "BANNER = NONE # It works here!");
				return 0;
			}
			else
			{
				std::cerr << "\e[1;31m" << "Error:" << "\e[0;37m" << " No documentation folder found!\n";
				return 1;
			}
		}
		else
		{
			std::cerr << "\e[1;31m" << "Error:" << "\e[0;37m" << " Unknown option or command: `" << arg << "`\n";
			glyph::command::printHelp();
			return 1;
		}
	};

	std::ifstream testInput(inputFile);
	if (!testInput.good())
	{
		std::cerr << "\e[1;31m" << "Error:" << "\e[0;37m" << " Cannot open input file " << inputFile << "\n";
		return 1;
	}

	MarkdownTransform transformer(inputFile);
	std::string contents = transformer.getContents();

	std::string head = "<!DOCTYPE html><html><head>\
		 <meta charset=\"utf-8\">\
		 <title>Markdown</title>\
		 <link rel=\"stylesheet\" href=\"my-markdown.css\">\
		 </head><body><article class=\"markdown-body\">";
	std::string end = "</article></body></html>";

	std::ofstream out(outputFile);
	if (!out.is_open())
	{
		std::cerr << "\e[1;31m" << "Error:" << "\e[0;37m" << " Cannot open output file " << outputFile << "\n";
		return 1;
	}

	out << head + contents + end;
	out.close();

	std::cout << "Successfully generated HTML: " << outputFile << "\n";
	return 0;
}