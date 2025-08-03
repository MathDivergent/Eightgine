#include <cJSON.h>

#ifdef EIGHTGINE_WITH_EDITOR
#include <Eightest/Core.hpp>
#endif

#include <iostream> // cout, cerr
#include <fstream> // ifstream

#if EIGHTGINE_PLATFORM_WINDOWS
#include <windows.h>
#elif EIGHTGINE_PLATFORM_LINUX || EIGHTGINE_PLATFORM_MACOS
#include <dlfcn.h>
#endif

namespace eightgine
{

int fMain(int iArgumentCount, char** pArgumentValues)
{
    // #if EIGHTGINE_PLATFORM_WINDOWS
    // AllocConsole();

    // FILE* fp;
    // freopen_s(&fp, "CONOUT$", "w", stdout);
    // freopen_s(&fp, "CONOUT$", "w", stderr);
    // freopen_s(&fp, "CONIN$", "r", stdin);

    // std::ios::sync_with_stdio();
    // // FreeConsole(); // to close console
    // #endif

    std::ifstream aPlugInsFile(std::string(EIGHTGINE_PROJECT_PLUGINS_DIR) + "/PlugIns.json", std::ios::ate | std::ios::binary);
    if (!aPlugInsFile)
    {
        std::cerr << "Failed to open PlugIns.json file\n";
        return 1;
    }

    std::streamsize size = aPlugInsFile.tellg();
    aPlugInsFile.seekg(0, std::ios::beg);

    std::string aPlugInsFileContent(size, '\0');
    if (!aPlugInsFile.read(const_cast<char*>(aPlugInsFileContent.data()), size))
    {
        std::cerr << "Error reading PlugIns.json file\n";
        return 1;
    }

    std::vector<std::string> plugins;

    auto aPlugInsJSON = cJSON_Parse(aPlugInsFileContent.data());
    auto aPlugInsJSONList = cJSON_GetObjectItem(aPlugInsJSON, "plugins");
    if (cJSON_IsArray(aPlugInsJSONList))
    {
        cJSON* aPlugInsJSONListItem = NULL;
        cJSON_ArrayForEach(aPlugInsJSONListItem, aPlugInsJSONList)
        {
            if (auto plugin = cJSON_GetStringValue(aPlugInsJSONListItem))
            {
                plugins.emplace_back(plugin);
                #if EIGHTGINE_DEBUG
                plugins.back().append("-Debug");
                #endif
            }
        }
    }
    cJSON_Delete(aPlugInsJSON);

    std::cout << "EIGHTGINE_PROJECT_EXECUTABLE_DIR: " << EIGHTGINE_PROJECT_EXECUTABLE_DIR << '\n';
    std::cout << "EIGHTGINE_PROJECT_RESOURCES_DIR: " << EIGHTGINE_PROJECT_RESOURCES_DIR << '\n';
    std::cout << "EIGHTGINE_PROJECT_PLUGINS_DIR: " << EIGHTGINE_PROJECT_PLUGINS_DIR << '\n';

    #if EIGHTGINE_PLATFORM_WINDOWS
    for (auto const& plugin : plugins)
    {
        std::string fullName = plugin + ".dll";
        HMODULE hGameModule = LoadLibrary(fullName.c_str());
        if (!hGameModule)
        {
            std::cout << "Failed to load " << fullName << std::endl;
            continue;
        }
        else
        {
            auto init = reinterpret_cast<void(*)()>(GetProcAddress(hGameModule, "RegisterModule"));
            if (init) init();
        }
    }
    #endif
    #if EIGHTGINE_PLATFORM_LINUX
    for (const auto& plugin : plugins)
    {
        std::string fullName = plugin + ".so";
        void* handle = dlopen(fullName.c_str(), RTLD_NOW);
        if (!handle)
        {
            std::cout << "Failed to load " << fullName << ": " << dlerror() << std::endl;
            continue;
        }

        dlerror();
        auto init = reinterpret_cast<void(*)()>(dlsym(handle, "RegisterModule"));
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
    #if EIGHTGINE_PLATFORM_MACOS
    for (const auto& plugin : plugins)
    {
        std::string fullName = plugin + ".dylib";
        void* handle = dlopen(fullName.c_str(), RTLD_NOW);
        if (!handle)
        {
            std::cout << "Failed to load " << fullName << ": " << dlerror() << std::endl;
            continue;
        }

        dlerror();
        auto init = reinterpret_cast<void(*)()>(dlsym(handle, "RegisterModule"));
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

    #if EIGHTGINE_WITH_EDITOR
    eightest::global()->try_catch([] { eightest::global()->execute_all(); });
    auto code = !eightest::global()->stat();
    #else
    auto code = 0;
    #endif

    // #if EIGHTGINE_PLATFORM_WINDOWS
    // FreeConsole();
    // #endif

    return code;
}

} // namespace eightgine

// //#include <SDL2/SDL.h>
// //#include <GLFW/glfw3.h>
// #if EIGHTGINE_DEBUG
// #include <Eightest/Core.hpp>
// #endif

// #define WITH_SDL2
// #ifdef WITH_SDL2
// #include <SDL_ttf.h>
// #include <SDL.h>
// #include <SDL_mixer.h>
// #endif
// // TEST(Test, Test)
// // {
// //     auto ex = EXPR(2)==2;
// //     automation::global.check(ex, this, "");
// // }

// // BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
// // {
// //     switch (fdwReason)
// //     {
// //     case DLL_PROCESS_ATTACH:
// //         break;
// //     case DLL_THREAD_ATTACH:
// //         break;
// //     case DLL_THREAD_DETACH:
// //         break;
// //     case DLL_PROCESS_DETACH:
// //         break;
// //     }
// //     return TRUE;
// // }
// #include <vector>
// #include <string>

// #include <iostream>
// #include <Eightser/Core.hpp>

// #define WITH_CJSON
// #ifdef WITH_CJSON
// #include <cJSON.h>
// #endif

// #if EIGHTGINE_PLATFORM_WINDOWS
// #include <windows.h>
// #endif

// #if EIGHTGINE_PLATFORM_LINUX
// #include <dlfcn.h>
// #endif

// #include <box2d/box2d.h>
// #include <lua.hpp>
// #include <Eightrefl/Core.hpp>
// #include <Eightrefl/Standard/Standard.hpp>

// namespace Eightgine
// {

// int fMain(int iArgumentCount, char** pArgumentValues)
// {
//     //b2WorldDef worldDef;
//     //b2CreateWorld(&worldDef);

//     // CJSON_IMPORT_SYMBOLS;
//     // CJSON_EXPORT_SYMBOLS;

// #if EIGHTGINE_PLATFORM_WINDOWS
//     AllocConsole();

//     FILE* fp;
//     freopen_s(&fp, "CONOUT$", "w", stdout);
//     freopen_s(&fp, "CONOUT$", "w", stderr);
//     freopen_s(&fp, "CONIN$", "r", stdin);

//     std::ios::sync_with_stdio();
//     // FreeConsole(); // to close console
// #endif
//     auto type = eightrefl::builtin()->find("std::size_t");

//     std::vector<std::string> libraries;
//     libraries.reserve(8);
// #ifdef WITH_CJSON
// #if EIGHTGINE_DEBUG
//     auto json = cJSON_Parse(
//     R"(
//     {
//       "plugins": [
//             "Game-Debug",
//             "EmptyProject-Debug"
//           ]
//     }
//     )");
// #else
//     auto json = cJSON_Parse(
//     R"(
//     {
//       "plugins": [
//             "Game",
//             "EmptyProject",
//           ]
//     }
//     )");
// #endif

//     auto plugins = cJSON_GetObjectItem(json, "plugins");
//     if (cJSON_IsArray(plugins))
//     {
//         cJSON* plugin = NULL;
//         cJSON_ArrayForEach(plugin, plugins)
//         {
//             if (auto name = cJSON_GetStringValue(plugin))
//             {
//                 libraries.emplace_back(name);
//             }
//         }
//     }
//     cJSON_Delete(json);

//     #if EIGHTGINE_PLATFORM_WINDOWS
//     for (auto const& library : libraries)
//     {
//         HMODULE hGameModule = LoadLibrary((library + ".dll").c_str());
//         if (!hGameModule)
//         {
//         } else
//         {
//             using InitFunc = void (*)();
//             InitFunc init = (InitFunc)GetProcAddress(hGameModule, "RegisterModule");
//             if (init) init();
//         }
//     }
//     #endif
//     #if EIGHTGINE_PLATFORM_LINUX
//     for (const auto& library : libraries)
//     {
//         std::string fullName =/* "lib" +*/ library + ".so";
//         void* handle = dlopen(fullName.c_str(), RTLD_NOW);
//         if (!handle)
//         {
//             std::cout << "Failed to load " << fullName << ": " << dlerror() << std::endl;
//             continue;
//         }

//         using InitFunc = void (*)();
//         dlerror();
//         InitFunc init = (InitFunc)dlsym(handle, "RegisterModule");
//         const char* dlsym_error = dlerror();
//         if (dlsym_error)
//         {
//             std::cout << "Cannot load symbol 'RegisterModule' from " << fullName << ": " << dlsym_error << std::endl;
//             dlclose(handle);
//             continue;
//         }

//         if (init) init();
//     }
//     #endif
//     #if EIGHTGINE_DEBUG
//     eightest::global()->try_catch([] { eightest::global()->execute_all(); });
//     /*return !*/eightest::global()->stat();
//     #endif
// #endif
//     // Registry::handler(nullptr);
//     #ifdef WITH_SDL2
//     // // TODO: example code

//     // TODO: dont use, temp
//     #if EIGHTGINE_PLATFORM_LINUX
//     // SDL_setenv("SDL_AUDIODRIVER", "dummy", 1);
//     #endif

//     if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0)
//     {
//         return 1;
//     }

//     auto window = SDL_CreateWindow("EightgineEditor", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
//     if (window == nullptr)
//     {
//         SDL_Quit();
//         return 1;
//     }

//     std::cout << "Available renderer drivers:\n";

//     int best = -1;
//     int bestScore = -1;

//     for (int i = 0; i < SDL_GetNumRenderDrivers(); ++i) {
//         SDL_RendererInfo info;
//         SDL_GetRenderDriverInfo(i, &info);
//         std::cout << "  " << i << ": " << info.name << '\n';
//         int score = 0;
//         if (info.flags & SDL_RENDERER_ACCELERATED) score += 10;
//         if (info.flags & SDL_RENDERER_PRESENTVSYNC) score += 5;
//         if (info.flags & SDL_RENDERER_TARGETTEXTURE) score += 2;

//         if (score > bestScore) {
//             bestScore = score;
//             best = i;
//         }
//     }
//     char const* err = NULL;
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, best, 0);
//     err = SDL_GetError();
//     if (err && *err) {
//         printf("SDL_CreateRenderer error: %s\n", err);
//         SDL_ClearError();
//     }
//     if (renderer == NULL) {
//         renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
//         printf("renderer == NULL, try fallback renderer\n");
//     }
//     err = SDL_GetError();
//     if (err && *err) {
//         printf("SDL_CreateRenderer error: %s\n", err);
//         SDL_ClearError();
//     }

//     SDL_RendererInfo info;
//     SDL_GetRendererInfo(renderer, &info);
//     std::cout << "Selected RendrererDriver: " << info.name << '\n';
//     if (info.flags & SDL_RENDERER_TARGETTEXTURE) {
//         printf("Target texture is supported!\n");
//     } else {
//         printf("Target texture NOT supported on this renderer.\n");
//     }
//     // const char* ld_path = std::getenv("LD_LIBRARY_PATH");
//     // if (ld_path)
//     //     std::cout << "LD_LIBRARY_PATH = " << ld_path << '\n';
//     // else
//     //     std::cout << "LD_LIBRARY_PATH not set\n";

//     // if ((Mix_Init(MIX_INIT_OPUS) & MIX_INIT_OPUS) == 0)
//     // {
//     //     printf("Failed to init OPUS support: %s\n", Mix_GetError());
//     //     SDL_DestroyWindow(window);
//     //     SDL_Quit();
//     //     return 1;
//     // }
//     auto const iFPS = 60;
//     auto const iFrameDelay = 1000 / iFPS;

//     auto bRunning = true;
//     SDL_Event aEvent;

//     TTF_Font* font = TTF_OpenFont(EIGHTGINE_PROJECT_RESOURCES_DIR "/Fonts/hand.otf", 64);
//     if (!font) {
//         std::cout << "TTF_OpenFont Error: " << TTF_GetError() << '\n';
//         SDL_DestroyWindow(window);
//         SDL_Quit();
//         return 1;
//     }

//     std::cout << "Available SDL audio drivers:\n";
//     for (int i = 0; i <  SDL_GetNumAudioDrivers(); ++i) {
//         std::cout << "  " << i << ": " << SDL_GetAudioDriver(i) << '\n';
//     }

//     if (SDL_GetNumAudioDrivers() > 0) {
//         if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//             std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << '\n';
//             SDL_DestroyWindow(window);
//             SDL_Quit();
//             return 1;
//         }

//         Mix_Music* music = Mix_LoadMUS(EIGHTGINE_PROJECT_RESOURCES_DIR "/Music/theme.ogg");
//         if (!music) {
//             std::cout << "Mix_LoadMUS Error: " << Mix_GetError() << '\n';
//             SDL_DestroyWindow(window);
//             Mix_CloseAudio();
//             SDL_Quit();
//             return 1;
//         }

//         if (Mix_PlayMusic(music, -1) == -1) {
//             std::cout << "Mix_PlayMusic Error: " << Mix_GetError() << '\n';
//         }
//     }

//     char const* text = "Hello, Eightgine!";
//     SDL_Color color = {255, 255, 255};
//     SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text, color);
//     SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//     err = SDL_GetError();
//     if (err && *err) {
//         printf("SDL_CreateTextureFromSurface error: %s\n", err);
//         SDL_ClearError();
//     }

//     int textW = textSurface->w;
//     int textH = textSurface->h;
//     SDL_FreeSurface(textSurface);

//     int winW, winH;
//     SDL_GetWindowSize(window, &winW, &winH);
//     SDL_Rect dstRect = {
//         (winW - textW) / 2,
//         (winH - textH) / 2,
//         textW,
//         textH
//     };

//     bool running = true;
//     bool window_shown = false;
//     Uint32 delay = static_cast<Uint32>(1000.0f / 30.0f);
//     SDL_Event e;

//     while (running) {
//         while (SDL_PollEvent(&e)) {
//             if (e.type == SDL_QUIT ||
//                 (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
//                 running = false;
//             }
//             else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_SHOWN) {
//                 window_shown = true;
//             }
//         }

//         if (window_shown) {
//             int winW, winH;
//             SDL_GetWindowSize(window, &winW, &winH);

//             SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//             err = SDL_GetError();
//             if (err && *err) {
//                 printf("SDL_SetRenderDrawColor error: %s\n", err);
//                 SDL_ClearError();
//             }
//             SDL_Rect fullRect = {0, 0, winW, winH};
//             SDL_RenderFillRect(renderer, &fullRect);
//             err = SDL_GetError();
//             if (err && *err) {
//                 printf("SDL_RenderFillRect error: %s\n", err);
//                 SDL_ClearError();
//             }
//             SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
//             err = SDL_GetError();
//             if (err && *err) {
//                 printf("SDL_RenderCopy error: %s\n", err);
//                 SDL_ClearError();
//             }
//             SDL_RenderPresent(renderer);
//             err = SDL_GetError();
//             if (err && *err) {
//                 printf("SDL_RenderPresent error: %s\n", err);
//                 SDL_ClearError();
//             }
//             window_shown = false;
//         }

//         SDL_Delay(delay);
//     }


//     SDL_DestroyTexture(textTexture);
//     TTF_CloseFont(font);
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     TTF_Quit();
//     SDL_Quit();
//     #endif
//     exit:
//     getchar();

// #if EIGHTGINE_PLATFORM_WINDOWS
//     FreeConsole();
// #endif
//     return 0;
// }

// } // namespace Eightgine
