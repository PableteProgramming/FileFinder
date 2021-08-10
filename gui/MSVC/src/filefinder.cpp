#include <filefinder.hpp> 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
   WNDCLASSEX wcex;

   wcex.cbSize = sizeof(WNDCLASSEX);
   wcex.style          = CS_HREDRAW | CS_VREDRAW;
   wcex.lpfnWndProc    = WndProc;
   wcex.cbClsExtra     = 0;
   wcex.cbWndExtra     = 0;
   wcex.hInstance      = hInstance;
   wcex.hIcon          = LoadIcon(wcex.hInstance, IDI_APPLICATION);
   wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
   wcex.lpszMenuName   = MAKEINTRESOURCE(ID_MENU1);
   wcex.lpszClassName  = szWindowClass;
   wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

   if (!RegisterClassEx(&wcex))
   {
      MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Windows Desktop Guided Tour"), NULL);
      return 1;
   }

   hInst = hInstance;

   HWND hWnd = CreateWindowEx(NULL, szWindowClass, szTitle,  WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 500, 100, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Windows Desktop Guided Tour"), NULL);
      return 1;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   MSG msg;
   while (GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hInstance;
    switch (message)
    {
    case WM_CREATE: {
        hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
        break;
    }
    case WM_DESTROY:{
        PostQuitMessage(0);
        break;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case ID_EXIT:{
            PostQuitMessage(0);
            break;
        }
        case ID_HELP:{
            DialogBox(hInstance, MAKEINTRESOURCE(HelpDialog), hWnd, DlgProc);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}

INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG: {
            return TRUE;
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case IDOK: {
                    EndDialog(hWnd, FALSE);
                    break;
                }
                case IDCANCEL: {
                    EndDialog(hWnd, FALSE);
                    break;
                }
            }
            break;
        }
    }
    return FALSE;
}

void PerformSearch(std::string search,std::string dir,bool r,bool f,bool c,bool cs){
    //std::cout<<"c=>"<<c<<std::endl;
    if(!fs::exists(dir) || !fs::is_directory(dir)){
        //std::cout<< "Path \""<<dir<<"\" is not a directory or it does not exist!"<<std::endl;
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
                        //std::cout<<termcolor::green<<rpath<<termcolor::reset<<std::endl;
                    }
                }
                else{
                    if(StringContains(ToLower(rpath),ToLower(search))){
                        //file found
                        //std::cout<<termcolor::green<<rpath<<termcolor::reset<<std::endl;
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
                        //std::cout<<termcolor::blue<<rpath<<termcolor::reset<<std::endl;
                    }
                }
                else{
                    //std::cout<<"Checking "<<rpath<<std::endl;
                    std::string content= GetFileContent(entry.path().string());
                    //std::cout<<"Content => "<<content<<std::endl;
                    if(StringContains(ToLower(content),ToLower(search))){
                        //file with content found
                        //std::cout<<termcolor::blue<<rpath<<termcolor::reset<<std::endl;
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
                        //std::cout<<termcolor::green<<rpath<<termcolor::reset<<std::endl;
                    }
                }
                else{
                    if(StringContains(ToLower(rpath),ToLower(search))){
                        //file found
                        //std::cout<<termcolor::green<<rpath<<termcolor::reset<<std::endl;
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
                        //std::cout<<termcolor::blue<<rpath<<termcolor::reset<<std::endl;
                    }
                }
                else{
                    //std::cout<<"Checking "<<rpath<<std::endl;
                    std::string content= GetFileContent(entry.path().string());
                    //std::cout<<"Content => "<<content<<std::endl;
                    if(StringContains(ToLower(content),ToLower(search))){
                        //file with content found
                        //std::cout<<termcolor::blue<<rpath<<termcolor::reset<<std::endl;
                    }
                }
            }
        }
    }
}