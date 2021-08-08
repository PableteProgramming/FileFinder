#include <iostream>
#include <fstream>
#include <argsparser.hpp>
#include <filesystem>
#include <algorithm>
#include <functional>
namespace fs= std::filesystem;

void PerformSearch(std::string,std::string,bool,bool,bool,bool);

std::string GetFileContent(std::string);

bool StringContains(std::string,std::string);