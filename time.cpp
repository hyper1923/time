#include <iostream>
#include <Windows.h>
#include <chrono>
#include <sstream>
int main(int argc, char** argv){
    if(argc < 2){
        printf("This program needs few more arguments to run.\n\r");
        exit(EXIT_SUCCESS);

    }
    STARTUPINFO info = {sizeof(info)};
    std::wstringstream wss;
    wss << argv[1];
    std::wstringstream args;
    for(int i = 2; i < argc; i++){
        args << argv[i];
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();
    PROCESS_INFORMATION processInfo;
    LPWSTR h = L"hello_world";
    if(CreateProcessW(wss.str().c_str(),h,NULL,NULL,TRUE,0,NULL,NULL,(LPSTARTUPINFOW)&info,&processInfo)){
        WaitForSingleObject(processInfo.hProcess,INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    } else{
        printf("An error occured while creating process\n\r");
        exit(EXIT_FAILURE);
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();
    system("cls");
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    printf("Elasped Time: %dms\n\r", millis);
}