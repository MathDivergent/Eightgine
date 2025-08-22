#ifdef EIGHTGINE_WITH_EDITOR
#include <Eightest/Core.hpp>
#endif

#include <iostream> // cout, cerr
#include <fstream> // ifstream

#include <cJSON.h>
#include <iniparser.h>

#include <CMain.hpp>

#include <Eightmory/Core.hpp>
#include <Eightser/Core.hpp>
#include <Eightser/Standard/AnyRegistry.hpp>
#include <Eightrefl/Core.hpp>

#include <PPlatform.hpp>
#include <PFileSystemInterface.hpp>
#include <PModuleControllerInterface.hpp>

#include <CModuleManager.hpp>
#include <CModuleInterface.hpp>

#if 0
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
// #include <entt/entt.hpp>
#endif // if

CMain* CMain::Global()
{
    static CMain self; return &self;
}

static int ExecuteImpl();

int CMain::Execute(int iArgumentCount, char** pArgumentValues)
{
    char memory[1024]; eightmory::segment_manager_t manager(memory, sizeof(memory)); (void)manager;

    (void)eightser::instantiable_registry();
    (void)eightser::any_registry();
    (void)eightrefl::global();

    if (PPlatform::Global()->ModuleController == nullptr)
    {
        return -1;
    }

    auto plugInsPath = PPlatform::Global()->FileSystem->ProjectPlugInsDir() / "PlugIns.json";
    std::cout << "plugInsPath: " << plugInsPath << '\n';
    std::ifstream aPlugInsFile(plugInsPath.c_str(), std::ios::ate | std::ios::binary);
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

    std::vector<std::string> plugIns;

    auto aPlugInsJSON = cJSON_Parse(aPlugInsFileContent.data());
    auto aPlugInsJSONList = cJSON_GetObjectItem(aPlugInsJSON, "plugins");
    if (cJSON_IsArray(aPlugInsJSONList))
    {
        cJSON* aPlugInsJSONListItem = NULL;
        cJSON_ArrayForEach(aPlugInsJSONListItem, aPlugInsJSONList)
        {
            if (auto plugIn = cJSON_GetStringValue(aPlugInsJSONListItem))
            {
                plugIns.emplace_back(plugIn);
                plugIns.back().append(EIGHTGINE_BUILD_POSTFIX);
            }
        }
    }
    cJSON_Delete(aPlugInsJSON);

    for (auto const& plugIn : plugIns)
    {
        auto name = PPlatform::Global()->FileSystem->ProjectPlugInsDir() / plugIn;
        std::cout << "name: " << name;
        auto module = PPlatform::Global()->ModuleController->LoadModule(name.string());
        std::cout << " module: " << module << '\n';
    }

    for (auto const module : CModuleManager::Global()->Modules)
    {
        module->OnLoad();
    }

    #if EIGHTGINE_WITH_EDITOR
    eightest::global()->try_catch([] { eightest::global()->execute_all(); });
    auto code = !eightest::global()->stat();
    #else
    auto code = 0;
    #endif

    ExecuteImpl();

    return code;
}

static int ExecuteImpl()
{
    #if 0
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
    char const* err = NULL;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, best, 0);
    err = SDL_GetError();
    if (err && *err) {
        printf("SDL_CreateRenderer error: %s\n", err);
        SDL_ClearError();
    }
    if (renderer == NULL) {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        printf("renderer == NULL, try fallback renderer\n");
    }
    err = SDL_GetError();
    if (err && *err) {
        printf("SDL_CreateRenderer error: %s\n", err);
        SDL_ClearError();
    }

    SDL_RendererInfo info;
    SDL_GetRendererInfo(renderer, &info);
    std::cout << "Selected RendrererDriver: " << info.name << '\n';
    if (info.flags & SDL_RENDERER_TARGETTEXTURE) {
        printf("Target texture is supported!\n");
    } else {
        printf("Target texture NOT supported on this renderer.\n");
    }

    auto const iFPS = 60;
    auto const iFrameDelay = 1000 / iFPS;

    auto bRunning = true;
    SDL_Event aEvent;

    TTF_Font* font = TTF_OpenFont((PPlatform::Global()->FileSystem->ProjectResourcesDir() / "Fonts/hand.otf").string().c_str(), 64);
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

        Mix_Music* music = Mix_LoadMUS((PPlatform::Global()->FileSystem->ProjectResourcesDir() / "Music/theme.ogg").string().c_str());
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
    err = SDL_GetError();
    if (err && *err) {
        printf("SDL_CreateTextureFromSurface error: %s\n", err);
        SDL_ClearError();
    }

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
            err = SDL_GetError();
            if (err && *err) {
                printf("SDL_SetRenderDrawColor error: %s\n", err);
                SDL_ClearError();
            }
            SDL_Rect fullRect = {0, 0, winW, winH};
            SDL_RenderFillRect(renderer, &fullRect);
            err = SDL_GetError();
            if (err && *err) {
                printf("SDL_RenderFillRect error: %s\n", err);
                SDL_ClearError();
            }
            SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
            err = SDL_GetError();
            if (err && *err) {
                printf("SDL_RenderCopy error: %s\n", err);
                SDL_ClearError();
            }
            SDL_RenderPresent(renderer);
            err = SDL_GetError();
            if (err && *err) {
                printf("SDL_RenderPresent error: %s\n", err);
                SDL_ClearError();
            }
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
    #endif // if
    return 0;
}
