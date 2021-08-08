#include <filefinder.hpp>

int main(int argc,char* argv[]){
    std::vector<std::string> opts = {"-d","--directory","--search","-s","-r","--recursive","-v","--verbose","-f","--file","-c","--content"};
    ArgsParser parser(opts);
    
    //parse params
    parser.Parse(parser.ConvertParams(argc,argv));
    std::vector<std::pair<std::pair<std::string, std::string>, bool>> result = parser.GetResult();
    
    bool verbose=false;
    bool dirFound=false;
    std::string dir;
    bool recursive=false;
    bool searchFound=false;
    std::string search;
    bool file=false;
    bool content=false;

	//result: vector<pair<pair<PARAM,VALUE>,FOUND>>

    for(int i=0; i<result.size();i++){
        //verbose
        if(result[i].first.first=="-v" || result[i].first.first=="--verbose"){
            if(result[i].second){
                verbose=true;
            }
        }
        //recursive
        if(result[i].first.first=="-r" || result[i].first.first=="--recursive"){
            if(result[i].second){
                recursive=true;
            }
        }
        //file
        if(result[i].first.first=="-f" || result[i].first.first=="--file"){
            if(result[i].second){
                file=true;
            }
        }
        //content
        if(result[i].first.first=="-c" || result[i].first.first=="--content"){
            if(result[i].second){
                content=true;
            }
        }
        //dir
        if(result[i].first.first=="-d" || result[i].first.first=="--directory"){
            if(result[i].second){
                if(result[i].first.second!=""){
                    dirFound=true;
                    dir=result[i].first.second;
                }
            }
        }
        //search
        if(result[i].first.first=="-s" || result[i].first.first=="--search"){
            if(result[i].second){
                if(result[i].first.second!=""){
                    searchFound=true;
                    search=result[i].first.second;
                }
            }
        }
    }

    if(!dirFound){
        dir=".";
    }

    if(!searchFound){
        std::cout<<"Please input the words to match after the -s or --search param"<<std::endl;
        return 1;
    }

    PerformSearch(dir,search,recursive,verbose,file,content);
    
    //std::cout<<"FileFinder"<<std::endl;
    return 0;
}

void PerformSearch(std::string dir,std::string search,bool r,bool v,bool f,bool c){
    if(!fs::exists(dir) || !fs::is_directory(dir)){
        std::cout<< "Path \""<<dir<<"\" is not a directory or it does not exist!"<<std::endl;
        return;
    }
    for (const auto & entry : fs::directory_iterator(dir)){
        std::string path= entry.path().string();
        std::string rpath="";
        bool end=false;
        for(int i=0; i<path.size();i++){
            if(!end && path[i]!='.' && path[i]!='/' && path[i]!='\\'){
                end=true;
                //we get all the points before it
                int j=i;
                while(true){
                    j--;
                    if(path[j]=='.'){
                        rpath+= ".";
                    }
                    else{
                        break;
                    }
                }
            }
            if(end){
                rpath+= path[i];
            }
        }
        if(f){
            if(StringContains(rpath,search)){
                std::cout<<rpath<<std::endl;
            }
        }
        if(c){
            if(StringContains(rpath,GetFileContent(entry.path().string()))){
                std::cout<<rpath<<std::endl;
            }
        }
    }
}

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