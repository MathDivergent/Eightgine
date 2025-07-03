//#include <SDL2/SDL.h>
//#include <GLFW/glfw3.h>
#if EIGHTGINE_DEBUG
#include <Eightest/Eightest.hpp>
#endif

#define WITH_SDL2
#ifdef WITH_SDL2
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_mixer.h>
#endif
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

#include <iostream>

#define WITH_CJSON
#ifdef WITH_CJSON
#include <cJSON.h>
#endif

#if EIGHTGINE_PLATFORM_WINDOWS
#include <windows.h>
#endif

#if EIGHTGINE_PLATFORM_LINUX
#include <dlfcn.h>
#endif

#include <box2d/box2d.h>
#include <lua.hpp>

namespace Eightgine
{

int fMain(int iArgumentCount, char** pArgumentValues)
{
    //b2WorldDef worldDef;
    //b2CreateWorld(&worldDef);

    // CJSON_IMPORT_SYMBOLS;
    // CJSON_EXPORT_SYMBOLS;

#if EIGHTGINE_PLATFORM_WINDOWS
    AllocConsole();

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    std::ios::sync_with_stdio();
    // FreeConsole(); // to close console
#endif

    std::vector<std::string> libraries;
    libraries.reserve(8);
#ifdef WITH_CJSON
#if EIGHTGINE_DEBUG
    auto json = cJSON_Parse(
    R"(
    {
      "plugins": [
            "Game-Debug",
            "EmptyProject-Debug"
          ]
    }
    )");
#else
    auto json = cJSON_Parse(
    R"(
    {
      "plugins": [
            "Game",
            "EmptyProject",
          ]
    }
    )");
#endif

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
            std::cout << "Failed to load " << fullName << ": " << dlerror() << std::endl;
            continue;
        }

        using InitFunc = void (*)();
        dlerror();
        InitFunc init = (InitFunc)dlsym(handle, "RegisterModule");
        const char* dlsym_error = dlerror();
        if (dlsym_error)
        {
            std::cout << "Cannot load symbol 'RegisterModule' from " << fullName << ": " << dlsym_error << std::endl;
            dlclose(handle);
            continue;
        }

        if (init) init();
    }
    #endif
    #if EIGHTGINE_DEBUG
    TRY_CATCH(EXECUTE_ALL());
    TESTING_STAT();
    #endif
#endif
    // Registry::handler(nullptr);
    #ifdef WITH_SDL2
    // // TODO: example code

    // TODO: dont use, temp
    #if EIGHTGINE_PLATFORM_LINUX
    SDL_setenv("SDL_AUDIODRIVER", "dummy", 1);
    #endif

    if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0)
    {
        return 1;
    }

    auto window = SDL_CreateWindow("EightgineEditor", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        SDL_Quit();
        return 1;
    }

    std::cout << "Available renderer drivers:\n";

    int best = -1;
    int bestScore = -1;

    for (int i = 0; i < SDL_GetNumRenderDrivers(); ++i) {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i, &info);
        std::cout << "  " << i << ": " << info.name << '\n';
        int score = 0;
        if (info.flags & SDL_RENDERER_ACCELERATED) score += 10;
        if (info.flags & SDL_RENDERER_PRESENTVSYNC) score += 5;
        if (info.flags & SDL_RENDERER_TARGETTEXTURE) score += 2;

        if (score > bestScore) {
            bestScore = score;
            best = i;
        }
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, best, 0);
    SDL_RendererInfo info;
    SDL_GetRenderDriverInfo(best, &info);
    std::cout << "Selected RendrererDriver: " << info.name << '\n';

    // const char* ld_path = std::getenv("LD_LIBRARY_PATH");
    // if (ld_path)
    //     std::cout << "LD_LIBRARY_PATH = " << ld_path << '\n';
    // else
    //     std::cout << "LD_LIBRARY_PATH not set\n";

    // if ((Mix_Init(MIX_INIT_OPUS) & MIX_INIT_OPUS) == 0)
    // {
    //     printf("Failed to init OPUS support: %s\n", Mix_GetError());
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return 1;
    // }
    auto const iFPS = 60;
    auto const iFrameDelay = 1000 / iFPS;

    auto bRunning = true;
    SDL_Event aEvent;

    TTF_Font* font = TTF_OpenFont(EIGHTGINE_PROJECT_RESOURCES_DIR "/Fonts/hand.otf", 64);
    if (!font) {
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::cout << "Available SDL audio drivers:\n";
    for (int i = 0; i <  SDL_GetNumAudioDrivers(); ++i) {
        std::cout << "  " << i << ": " << SDL_GetAudioDriver(i) << '\n';
    }

    if (SDL_GetNumAudioDrivers() > 0) {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << '\n';
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }

        Mix_Music* music = Mix_LoadMUS(EIGHTGINE_PROJECT_RESOURCES_DIR "/Music/theme.ogg");
        if (!music) {
            std::cout << "Mix_LoadMUS Error: " << Mix_GetError() << '\n';
            SDL_DestroyWindow(window);
            Mix_CloseAudio();
            SDL_Quit();
            return 1;
        }

        if (Mix_PlayMusic(music, -1) == -1) {
            std::cout << "Mix_PlayMusic Error: " << Mix_GetError() << '\n';
        }
    }

    char const* text = "Hello, Eightgine!";
    SDL_Color color = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text, color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textW = textSurface->w;
    int textH = textSurface->h;
    SDL_FreeSurface(textSurface);

    int winW, winH;
    SDL_GetWindowSize(window, &winW, &winH);
    SDL_Rect dstRect = {
        (winW - textW) / 2,
        (winH - textH) / 2,
        textW,
        textH
    };

    bool running = true;
    bool window_shown = false;
    Uint32 delay = static_cast<Uint32>(1000.0f / 30.0f);
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT ||
                (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
            else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_SHOWN) {
                window_shown = true;
            }
        }

        if (window_shown) {
            int winW, winH;
            SDL_GetWindowSize(window, &winW, &winH);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_Rect fullRect = {0, 0, winW, winH};
            SDL_RenderFillRect(renderer, &fullRect);

            SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
            SDL_RenderPresent(renderer);

            window_shown = false;
        }

        SDL_Delay(delay);
    }


    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    #endif
    exit:
    scanf("%*[^\n]");
    getchar();

#if EIGHTGINE_PLATFORM_WINDOWS
    FreeConsole();
#endif
    return 0;
}

} // namespace Eightgine
