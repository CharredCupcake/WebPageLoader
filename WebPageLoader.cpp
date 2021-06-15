#include <iostream >
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> links;
std::string input, output;
std::ifstream inStream;
std::ofstream outStream;

void GetInputFile()
{
	std::cout << "Type input file name: ";
	std::cin >> input;
	input.append(".TXT");
}

void GetLinks()
{
	do
	{
		inStream.open(input.c_str());
	} while (!inStream.is_open());
	std::cout << input.c_str() << " opened...\n";
	std::string currentLine;
	while(!inStream.eof())
	{
		inStream >> currentLine;
		links.push_back(currentLine);
	}
	if (links[links.size() - 1] == links[links.size() - 2])
	{
		links.pop_back();
	}
	inStream.close();
}

void PrintLinksExtracted()
{
	std::cout << "Extracted Links:\n";
	size_t linksSize = links.size();
	for (size_t i = 0; i < linksSize; i++)
	{
		std::cout << links[i]<<'\n';
	}
}

void LoadScript()
{
	size_t linksCount = links.size();
	for (size_t i = 0; i < linksCount; i++)
	{
		outStream << "window.open(\"" << links[i] << "\");\n";
	}
}

void CreateFile()
{
	output.assign(input.c_str(), input.length() - 4);
	output.append("HTML.HTML");
	do
	{
		outStream.open(output.c_str(), std::ofstream::trunc);
		std::cout << "Attempting to create " << input.c_str() << " ...\n";
	} while (!outStream.is_open());
	std::cout << output.c_str() << " created...\n";
	outStream << "<!DOCTYPE html>\n<html>\n<head>\n<title>Opened links from "
			  << input.c_str()
			  << "</title>\n</head>\n<script>\n";
	LoadScript();
	outStream << "</script>\n<body>\n<center>\n<h1>Opened links from "
			  << input.c_str()
			  <<"</h1>\n</center>\n</body>\n</html>";
	outStream.close();
}

void Execute()
{
	system(std::string("start " + output).c_str());
	std::cout << output << " executed";
}

int main()
{
	GetInputFile();
	GetLinks();
	PrintLinksExtracted();
	CreateFile();
	Execute();

	return 0;
}
