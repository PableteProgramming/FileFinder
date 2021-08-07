#include <filefinder.hpp>

int main(int argc,char* argv[]){
    std::vector<std::string> opts = {"-o","--output","--url","-u","-v","--verbose"};
    ArgsParser parser(opts);
    
    //parse params
    parser.Parse(parser.ConvertParams(argc,argv));
    std::vector<std::pair<std::pair<std::string, std::string>, bool>> result = parser.GetResult();
    std::cout<<"FileFinder"<<std::endl;
    return 0;
}