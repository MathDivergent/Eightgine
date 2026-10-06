#include <CMain.hpp>

#include <CEngine.hpp>
#include <CModuleManager.hpp>
#include <CModuleInterface.hpp>

#include <PPlatform.hpp>
#include <PModuleControllerInterface.hpp>
#include <PFileSystemInterface.hpp>

#include <Eightest/Core.hpp>
#include <Eightmory/Core.hpp>
#include <Eightrefl/Core.hpp>
#include <Eightrefl/Standard/Standard.hpp>

#include <Eightser/Core.hpp>

#include <ranges> // views::reverse
#include <iostream> // cout

// TODO: provide exit code enum
int iExitCode = 0;

// TODO: temporary impl
static void CModuleManager_HotLoadModule(std::filesystem::path const& sModuleDir, std::string const& sModuleName, bool const bHasModuleFactory = true)
{
    std::filesystem::path const sModuleFilePathNoFileExtension = sModuleDir / (sModuleName + EIGHTGINE_BUILD_POSTFIX);
    void* const pModuleHandle = PPlatform::pModuleController->LoadModule(sModuleFilePathNoFileExtension);

    std::cout << "[CModuleManager_HotLoadModule][INFO]: sModuleName: " << sModuleName << " pModuleHandle: " << pModuleHandle << '\n';

    if (pModuleHandle == nullptr)
    {
        std::cout << "[CModuleManager_HotLoadModule][ERROR]: " << PPlatform::pModuleController->ExtractError().value_or("pModuleHandle == nullptr") << '\n';
        iExitCode = 1; return;
    }

    if (!bHasModuleFactory)
    {
        return;
    }

    auto const hModuleFactory = (CModuleManager::ModuleFactoryH)PPlatform::pModuleController->ModuleSymbol(pModuleHandle, CModuleManager::sModuleFactoryFunctionName.data());
    if (hModuleFactory == nullptr)
    {
        std::cout << "[CModuleManager_HotLoadModule][ERROR]: " << PPlatform::pModuleController->ExtractError().value_or("hModuleFactory == nullptr") << '\n';
        iExitCode = 1; return;
    }

    CModuleInterface* const pModule = hModuleFactory();
    if (pModule == nullptr)
    {
        std::cout << "[CModuleManager_HotLoadModule][ERROR]: pModule == nullptr" << '\n';
        iExitCode = 1; return;
    }

    pModule->sModuleName = sModuleName;
    pModule->pModuleHandle = pModuleHandle;

    CModuleManager::cModules.emplace_back(pModule);
}

static void CModuleManager_HotUnloadModule(std::unique_ptr<CModuleInterface>& pModule)
{
    std::cout << "[CModuleManager_HotUnloadModule][INFO]: sModuleName: " << pModule->sModuleName << " pModuleHandle: " << pModule->pModuleHandle <<  '\n';
    
    void* const pCachedModuleHandle = pModule->pModuleHandle;
    pModule.reset();

    if (PPlatform::pModuleController->UnloadModule(pCachedModuleHandle) == false)
    {
        std::cout << "[CModuleManager_HotUnloadModule][ERROR]: " << PPlatform::pModuleController->ExtractError().value_or("UnloadModule(...) == false") << '\n';
        iExitCode = 4; return;
    }
}

[[maybe_unused]] static void CEightest_ExecuteAutomation()
{
    eightest::global()->execute_all();

    if (!eightest::global()->stat())
    {
        iExitCode = 2;
    }
    if (eightest::global()->passed == 0)
    {
        iExitCode = 3;
    }
}

// TODO: add cli parser
// TODO: add quick load window, audio, fonts, configs
int CMain::Execute([[maybe_unused]] int iArgumentCount, [[maybe_unused]] char** pArgumentValues)
{
    // TODO: temp trigger linking
    char cMemory[1024]; [[maybe_unused]] eightmory::segment_manager_t aManager(cMemory, sizeof(cMemory));
    [[maybe_unused]] eightser::instantiable_registry_t* pInstantiableRegistry = eightser::instantiable_registry();
    [[maybe_unused]] eightrefl::registry_t* pGlobalRegistry = eightrefl::global();
    [[maybe_unused]] eightrefl::registry_t* pBuiltinRegistry = eightrefl::builtin();
    CEngine aEightgine;

    // TODO: provide logger
    {
        // TODO: should be from ini or json
        // TODO: native  Eight libs does not free by dlclose
        std::vector<std::string> const cModuleNames =
        {
            "EightgineRenderer",
            "EightgineAudio",
            "EightgineInput",
            "EightginePhysics",
            "EightgineScripting",
            "EightgineObjects",
            "EightgineLighting",
            "EightgineAnimations",
            "EightgineParticles",
            "EightgineNetwork",
            "EightgineInteractive",
            #if EIGHTGINE_WITH_EDITOR
            "EightgineEditor",
            #endif // EIGHTGINE_WITH_EDITOR
        };

        for (std::string const& sModuleName : cModuleNames)
        {
            CModuleManager_HotLoadModule(PPlatform::pFileSystem->ProjectModulesDir(), sModuleName);
        }
    }

    {
        // TODO: should be from ini or json
        std::vector<std::string> const cPlugInModuleNames =
        {
            "EightmoryTests",
            "EightserTests",
            "EightreflTests",
            "Game" // TODO: should be unloaded
        };

        for (std::string const& sPlugInModuleName : cPlugInModuleNames)
        {
            CModuleManager_HotLoadModule(PPlatform::pFileSystem->ProjectPlugInModulesDir(), sPlugInModuleName, /*bHasModuleFactory*/false);
        }
    }

    for (std::unique_ptr<CModuleInterface> const& pModule : CModuleManager::cModules)
    {
        pModule->StartupModule(&aEightgine);
    }

    CEightest_ExecuteAutomation();

    // TODO: suggestion to rework shutdown & upload sequance,
    //       and posibility to built in load & startup and shutdown & upload,
    //       needed for hot reload, plugins.
    for (std::unique_ptr<CModuleInterface> const& pModule : CModuleManager::cModules | std::views::reverse)
    {
        pModule->ShutdownModule();
    }

    for (std::unique_ptr<CModuleInterface>& pModule : CModuleManager::cModules | std::views::reverse)
    {
        CModuleManager_HotUnloadModule(pModule);
    }

    std::cout << "iExitCode: " << iExitCode << '\n'; return iExitCode;
}
