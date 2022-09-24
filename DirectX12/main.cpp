#include<Windows.h>
#include"Application.h"
#include<iostream>
//  mainŠÖ”
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
   
    class Application* app= new Application();
    app->Run();

    delete app;
    return 0;
}