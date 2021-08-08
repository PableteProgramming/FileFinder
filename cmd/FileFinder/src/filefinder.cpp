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
                    dir=result[i].first.second!="";
                }
            }
        }
        //search
        if(result[i].first.first=="-s" || result[i].first.first=="--search"){
            if(result[i].second){
                if(result[i].first.second!=""){
                    searchFound=true;
                    search=result[i].first.second!="";
                }
            }
        }
    }

    if(!dirFound){
        dir=".";
    }

    if(!searchFound){
        std::cout<<"Please input the words to match after the -s or --search param";
        return 1;
    }

    PerformSearch(dir,search,recursive,verbose,file,content);
    
    std::cout<<"FileFinder"<<std::endl;
    return 0;
}

void PerformSearch(std::string dir,std::string search,bool r,bool v,bool f,bool c){
    for (const auto & entry : fs::directory_iterator(dir)){
        std::cout<<entry.path()<<std::endl;
    }
}