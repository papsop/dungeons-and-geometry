#include "GameInjection.h"

#include <windows.h>
#include <WinBase.h>
#include <iostream>

int main()
{
    //Game::GameInjection inj;
    //Engine::Application::Instance().Run(inj);
    WritePrivateProfileString(L"settings", L"action_fire", L"1337", L"./config.ini");

    int number = GetPrivateProfileInt(L"settings", L"action_fire", 0, L"./config.ini");
    std::cout << number << std::endl;
    std::cin.get();


    return 0;
}