#include <iostream>
#include <fstream>
#include <argsparser.hpp>
#include <filesystem>
#include <termcolor/termcolor.hpp>
#include <funcs.hpp>
namespace fs= std::filesystem;

const std::string contentParam1="-c";
const std::string contentParam2="--content";
const std::string recursiveParam1= "-r";
const std::string recursiveParam2= "--recursive";
const std::string fileParam1= "-f";
const std::string fileParam2= "--file";
const std::string dirParam1= "-d";
const std::string dirParam2= "--directory";
const std::string searchParam1= "-s";
const std::string searchParam2= "--search";
const std::string caseParam1= "-cs";
const std::string caseParam2= "--case-sensitive";
const std::string helpParam1= "-h";
const std::string helpParam2= "--help";

void PerformSearch(std::string,std::string,bool,bool,bool,bool);
void Help();