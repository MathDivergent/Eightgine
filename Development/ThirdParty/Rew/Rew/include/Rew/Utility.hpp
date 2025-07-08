#ifndef REW_UTILITY_HPP
#define REW_UTILITY_HPP

#include <any> // any
#include <memory> // addressof

#include <Rew/Detail/Meta.hpp>

namespace rew
{

inline namespace utility
{

template <typename ValueType>
ValueType forward(std::any const& object)
{
    if constexpr (std::is_reference_v<ValueType>)
    {
        return *std::any_cast<typename meta::to_reflectable_reference<ValueType>::type>(object);
    }
    else if constexpr (std::is_pointer_v<ValueType>)
    {
        return std::any_cast<typename meta::to_reflectable_pointer<ValueType>::type>(object);
    }
    else
    {
        return std::any_cast<typename meta::to_reflectable_object<ValueType>::type>(object);
    }
}

template <typename ValueType>
std::any backward(ValueType&& result)
{
    if constexpr (std::is_reference_v<ValueType>)
    {
        return const_cast<typename meta::to_reflectable_reference<ValueType>::type>(std::addressof(result));
    }
    else if constexpr (std::is_pointer_v<ValueType>)
    {
        return const_cast<typename meta::to_reflectable_pointer<ValueType>::type>(result);
    }
    else
    {
        return result;
    }
}

} // inline namespace utility

} // namespace rew

#endif // REW_UTILITY_HPP
