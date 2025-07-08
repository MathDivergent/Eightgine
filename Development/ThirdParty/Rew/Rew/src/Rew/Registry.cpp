#include <Rew/Registry.hpp>

#include <Rew/Injection.hpp>
#include <Rew/Parent.hpp>
#include <Rew/Factory.hpp>
#include <Rew/Function.hpp>
#include <Rew/Property.hpp>
#include <Rew/Deleter.hpp>
#include <Rew/Meta.hpp>

namespace rew
{

registry_t::registry_t()
{
    all.reserve(REW_REGISTRY_RESERVE_SIZE);
}

registry_t::~registry_t()
{
    for (auto& [name, meta] : all)
    {
        delete meta->reflection;
        delete meta;
    }
}

type_t* registry_t::find(std::string const& name) const
{
    auto it = all.find(name);
    return it != all.end() ? it->second : nullptr;
}

#ifdef REW_RTTI_ALL_ENABLE
type_t* registry_t::find(std::type_index typeindex) const
{
    auto it = rtti_all.find(typeindex);
    return it != rtti_all.end() ? it->second : nullptr;
}
#endif // REW_RTTI_ALL_ENABLE

registry_t global;

} // namespace rew
