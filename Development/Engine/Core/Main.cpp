//#include <SDL2/SDL.h>
//#include <GLFW/glfw3.h>
#include <Automation/Core.hpp>


// TEST(Test, Test)
// {
//     auto ex = EXPR(2)==2;
//     automation::global.check(ex, this, "");
// }

// BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
// {
//     switch (fdwReason)
//     {
//     case DLL_PROCESS_ATTACH:
//         // DLL загружается в процесс
//         break;
//     case DLL_THREAD_ATTACH:
//         // Новый поток создаётся в процессе
//         break;
//     case DLL_THREAD_DETACH:
//         // Поток завершает работу
//         break;
//     case DLL_PROCESS_DETACH:
//         // DLL выгружается из процесса
//         break;
//     }
//     return TRUE; // Успешная инициализация
// }
#include <vector>
#include <string>

#include <cJSON/cJSON.h>
#include <windows.h>

namespace Eightgine
{

int fMain(int iArgumentCount, char** pArgumentValues)
{
    // CJSON_IMPORT_SYMBOLS;
    // CJSON_EXPORT_SYMBOLS;

    std::vector<std::string> libraries;
    libraries.reserve(8);

    auto json = cJSON_Parse(
    R"(
    {
      "plugins": [
            "EmptyProject-Debug"
          ]
    }
    )");
    auto plugins = cJSON_GetObjectItem(json, "plugins");
    if (cJSON_IsArray(plugins))
    {
        cJSON* plugin = NULL;
        cJSON_ArrayForEach(plugin, plugins)
        {
            if (auto name = cJSON_GetStringValue(plugin))
            {
                libraries.emplace_back(name);
            }
        }
    }
    cJSON_Delete(json);

    for (auto const& library : libraries)
    {
        HMODULE hGameModule = LoadLibrary((library + ".dll").c_str());
        if (!hGameModule)
        {
        } else
        {
            using InitFunc = void (*)();
            InitFunc init = (InitFunc)GetProcAddress(hGameModule, "RegisterModule");
            if (init) init();
        }
    }

    TRY_CATCH(EXECUTE_ALL());
    TESTING_STAT();
    // Registry::handler(nullptr);

    // // TODO: example code
    // if (SDL_Init(SDL_INIT_VIDEO) != 0)
    // {
    //     return 1;
    // }

    // auto pWindow = SDL_CreateWindow("EightgineEditor", 100, 100, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_SKIP_TASKBAR);
    // if (pWindow == nullptr)
    // {
    //     SDL_Quit();
    //     return 1;
    // }

    // auto pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // if (pRenderer == nullptr)
    // {
    //     SDL_DestroyWindow(pWindow);
    //     SDL_Quit();
    //     return 1;
    // }

    // auto const iFPS = 60;
    // auto const iFrameDelay = 1000 / iFPS;

    // auto bRunning = true;
    // SDL_Event aEvent;


    // while (bRunning)
    // {
    //     auto iFrameStart = SDL_GetTicks();

    //     while (SDL_PollEvent(&aEvent))
    //     {
    //         if (aEvent.type == SDL_QUIT)
    //         {
    //             bRunning = false;
    //         }
    //     }

    //     SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0xff);
    //     SDL_RenderClear(pRenderer);
    //     SDL_RenderPresent(pRenderer);

    //     auto iFrameTime = SDL_GetTicks() - iFrameStart;
    //     if (iFrameTime < iFrameDelay)
    //     {
    //         SDL_Delay(iFrameDelay - iFrameTime);
    //     }
    // }

    // SDL_DestroyRenderer(pRenderer);
    // SDL_DestroyWindow(pWindow);
    // SDL_Quit();
    // ~
    return 0;
}

} // namespace Eightgine
