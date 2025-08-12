#include <cJSON.h>

#ifdef EIGHTGINE_WITH_EDITOR
#include <Eightest/Core.hpp>
#endif

#include <iostream> // cout, cerr
#include <fstream> // ifstream

#include <CMain.hpp>

#include <PPlatform.hpp>
#include <PFileSystemInterface.hpp>
#include <PModuleControllerInterface.hpp>

#include <CModuleRegistry.hpp>
#include <CModuleInterface.hpp>

CMain* CMain::Global()
{
    static CMain self; return &self;
}

int CMain::Execute(int iArgumentCount, char** pArgumentValues)
{
    if (PPlatform::Global()->ModuleController == nullptr)
    {
        return -1;
    }

    for (auto const module : CModuleRegistry::Global()->All)
    {
        module->OnLoad();
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
                #if EIGHTGINE_DEBUG
                plugIns.back().append("-Debug");
                #endif
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

    for (auto const module : CModuleRegistry::Global()->All)
    {
        module->OnLoad();
    }

    #if EIGHTGINE_WITH_EDITOR
    eightest::global()->try_catch([] { eightest::global()->execute_all(); });
    auto code = !eightest::global()->stat();
    #else
    auto code = 0;
    #endif

    return code;
}
