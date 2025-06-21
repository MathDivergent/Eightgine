//#include <SDL2/SDL.h>
//#include <GLFW/glfw3.h>
#include <Automation/Core.hpp>
#include <SDL2/SDL.h>

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
//         break;
//     case DLL_THREAD_ATTACH:
//         break;
//     case DLL_THREAD_DETACH:
//         break;
//     case DLL_PROCESS_DETACH:
//         break;
//     }
//     return TRUE;
// }
#include <vector>
#include <string>

#include <cJSON/cJSON.h>

#if EIGHTGINE_PLATFORM_WINDOWS
#include <windows.h>
#endif

#if EIGHTGINE_PLATFORM_LINUX
#include <dlfcn.h>
#include <iostream>
#endif

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
            "Game"
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

    #if EIGHTGINE_PLATFORM_WINDOWS
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
    #endif
    #if EIGHTGINE_PLATFORM_LINUX
    for (const auto& library : libraries)
    {
        std::string fullName =/* "lib" +*/ library + ".so";
        void* handle = dlopen(fullName.c_str(), RTLD_NOW);
        if (!handle)
        {
            std::cerr << "Failed to load " << fullName << ": " << dlerror() << std::endl;
            continue;
        }

        using InitFunc = void (*)();
        dlerror();
        InitFunc init = (InitFunc)dlsym(handle, "RegisterModule");
        const char* dlsym_error = dlerror();
        if (dlsym_error)
        {
            std::cerr << "Cannot load symbol 'RegisterModule' from " << fullName << ": " << dlsym_error << std::endl;
            dlclose(handle);
            continue;
        }

        if (init) init();
    }
    #endif
    TRY_CATCH(EXECUTE_ALL());
    TESTING_STAT();

    // Registry::handler(nullptr);

    // // TODO: example code
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return 1;
    }

    auto pWindow = SDL_CreateWindow("EightgineEditor", 100, 100, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_SKIP_TASKBAR);
    if (pWindow == nullptr)
    {
        SDL_Quit();
        return 1;
    }

    auto pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (pRenderer == nullptr)
    {
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        return 1;
    }

    auto const iFPS = 60;
    auto const iFrameDelay = 1000 / iFPS;

    auto bRunning = true;
    SDL_Event aEvent;


    while (bRunning)
    {
        auto iFrameStart = SDL_GetTicks();

        while (SDL_PollEvent(&aEvent))
        {
            if (aEvent.type == SDL_QUIT)
            {
                bRunning = false;
            }
        }

        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0xff);
        SDL_RenderClear(pRenderer);
        SDL_RenderPresent(pRenderer);

        auto iFrameTime = SDL_GetTicks() - iFrameStart;
        if (iFrameTime < iFrameDelay)
        {
            SDL_Delay(iFrameDelay - iFrameTime);
        }
    }

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    // ~
    return 0;
}

} // namespace Eightgine
