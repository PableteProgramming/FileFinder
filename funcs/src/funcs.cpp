#include <funcs.hpp>

std::string GetFileContent(std::string s){
    std::ifstream ifs(s);
    if(!ifs){
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    return content;
}

bool StringContains(std::string s,std::string s1){
    auto it = std::search(s.begin(), s.end(), std::boyer_moore_searcher(s1.begin(), s1.end()));
    if(it != s.end()){
        return true;
    }
    return false;
}

std::string ToLower(std::string s){
    std::string s1=s;
    for(int i=0; i<s.size();i++){
        s1[i]= tolower(s[i]);
    }
    return s1;
}