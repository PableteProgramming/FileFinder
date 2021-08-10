#include <filefinder.hpp>

int main(int argc,char* argv[]){
    std::vector<std::string> opts = {dirParam1,dirParam2,searchParam1,searchParam2,recursiveParam1,recursiveParam2,fileParam1,fileParam2,contentParam1,contentParam2,caseParam1,caseParam2,helpParam1,helpParam2};
    ArgsParser parser(opts);
    
    //parse params
    parser.Parse(parser.ConvertParams(argc,argv));
    std::vector<std::pair<std::pair<std::string, std::string>, bool>> result = parser.GetResult();
    
    bool dirFound=false;
    std::string dir;
    bool recursive=false;
    bool searchFound=false;
    std::string search;
    bool file=false;
    bool content=false;
    bool caseSensitive=false;

	//result: vector<pair<pair<PARAM,VALUE>,FOUND>>

    for(int i=0; i<result.size();i++){
        //recursive
        if(result[i].first.first==recursiveParam1 || result[i].first.first==recursiveParam2){
            if(result[i].second){
                recursive=true;
            }
        }
        //file
        if(result[i].first.first==fileParam1 || result[i].first.first==fileParam2){
            if(result[i].second){
                file=true;
            }
        }
        //content
        if(result[i].first.first==contentParam1 || result[i].first.first==contentParam2){
            if(result[i].second){
                content=true;
            }
        }
        //case sensitive
        if(result[i].first.first==caseParam1 || result[i].first.first==caseParam2){
            if(result[i].second){
                caseSensitive=true;
            }
        }
        //case sensitive
        if(result[i].first.first==helpParam1 || result[i].first.first==helpParam2){
            if(result[i].second){
                Help();
                return 0;
            }
        }
        //dir
        if(result[i].first.first==dirParam1 || result[i].first.first==dirParam2){
            if(result[i].second){
                if(result[i].first.second!=""){
                    dirFound=true;
                    dir=result[i].first.second;
                }
            }
        }
        //search
        if(result[i].first.first==searchParam1 || result[i].first.first==searchParam2){
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
        std::cout<<termcolor::red<<"Please input the words to match after the -s or --search param"<<termcolor::reset<<std::endl;
        Help();
        return 1;
    }

    if(!file && !content){
        file=true;
    }

    std::cout<<termcolor::red<<"-----------------------------------------"<<termcolor::reset<<std::endl;
    std::cout<<termcolor::red<<"|"<<termcolor::blue<<"blue"<<termcolor::reset<<" => search matched in file content"<<termcolor::red<<" |"<<termcolor::reset<<std::endl;
    std::cout<<termcolor::red<<"|"<<termcolor::green<<"green"<<termcolor::reset<<" => search matched in file name"<<termcolor::red<<"   |"<<termcolor::reset<<std::endl;
    std::cout<<termcolor::red<<"-----------------------------------------"<<termcolor::reset<<std::endl;

    PerformSearch(dir,search,recursive,file,content,caseSensitive);
    
    //std::cout<<"FileFinder"<<std::endl;
    return 0;
}

void PerformSearch(std::string dir,std::string search,bool r,bool f,bool c,bool cs){
    //std::cout<<"c=>"<<c<<std::endl;
    if(!fs::exists(dir) || !fs::is_directory(dir)){
        std::cout<< "Path \""<<dir<<"\" is not a directory or it does not exist!"<<std::endl;
        return;
    }
    if(!r){
        for (const auto & entry : fs::directory_iterator(dir)){
            if(fs::is_directory(entry.path().string())){
                continue;
            }
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
                if(cs){
                    if(StringContains(rpath,search)){
                        //file found
                        std::cout<<termcolor::green<<rpath<<termcolor::reset<<std::endl;
                    }
                }
                else{
                    if(StringContains(ToLower(rpath),ToLower(search))){
                        //file found
                        std::cout<<termcolor::green<<rpath<<termcolor::reset<<std::endl;
                    }
                }
            }
            if(c){
                if(cs){
                    //std::cout<<"Checking "<<rpath<<std::endl;
                    std::string content= GetFileContent(entry.path().string());
                    //std::cout<<"Content => "<<content<<std::endl;
                    if(StringContains(content,search)){
                        //file with content found
                        std::cout<<termcolor::blue<<rpath<<termcolor::reset<<std::endl;
                    }
                }
                else{
                    //std::cout<<"Checking "<<rpath<<std::endl;
                    std::string content= GetFileContent(entry.path().string());
                    //std::cout<<"Content => "<<content<<std::endl;
                    if(StringContains(ToLower(content),ToLower(search))){
                        //file with content found
                        std::cout<<termcolor::blue<<rpath<<termcolor::reset<<std::endl;
                    }
                }
            }
        }
    }
    else{
        for (const auto & entry : fs::recursive_directory_iterator(dir)){
            if(fs::is_directory(entry.path().string())){
                continue;
            }
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
                if(cs){
                    if(StringContains(rpath,search)){
                        //file found
                        std::cout<<termcolor::green<<rpath<<termcolor::reset<<std::endl;
                    }
                }
                else{
                    if(StringContains(ToLower(rpath),ToLower(search))){
                        //file found
                        std::cout<<termcolor::green<<rpath<<termcolor::reset<<std::endl;
                    }
                }
            }
            if(c){
                if(cs){
                    //std::cout<<"Checking "<<rpath<<std::endl;
                    std::string content= GetFileContent(entry.path().string());
                    //std::cout<<"Content => "<<content<<std::endl;
                    if(StringContains(content,search)){
                        //file with content found
                        std::cout<<termcolor::blue<<rpath<<termcolor::reset<<std::endl;
                    }
                }
                else{
                    //std::cout<<"Checking "<<rpath<<std::endl;
                    std::string content= GetFileContent(entry.path().string());
                    //std::cout<<"Content => "<<content<<std::endl;
                    if(StringContains(ToLower(content),ToLower(search))){
                        //file with content found
                        std::cout<<termcolor::blue<<rpath<<termcolor::reset<<std::endl;
                    }
                }
            }
        }
    }
}

void Help(){
    std::cout<<"Non-optional parameters:"<<std::endl;
    std::cout<<"search words => -s|--search [words]"<<std::endl;
    std::cout<<std::endl<<"Optional parameters:"<<std::endl;
    std::cout<<"search in file content (default) => -c|--content"<<std::endl;
    std::cout<<"search in file names => -f|--file"<<std::endl;
    std::cout<<"search in subdirectories => -r|--recursive"<<std::endl;
    std::cout<<"the root search directory (default= .) => -d|--directory [directory]"<<std::endl;
    std::cout<<"case sensitive => -cs|--case-sensitive"<<std::endl;
    std::cout<<"help => -h|--help"<<std::endl;
}