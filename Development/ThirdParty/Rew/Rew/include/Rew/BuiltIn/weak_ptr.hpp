#ifndef REW_BUILTIN_WEAK_PTR_HPP
#define REW_BUILTIN_WEAK_PTR_HPP

#include <memory> // weak_ptr

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// as function argument/return type
#include <Rew/BuiltIn/shared_ptr.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename ElementType>,
    std::weak_ptr<ElementType>, std::weak_ptr<rew::clean_of<ElementType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ElementType>, std::weak_ptr<ElementType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::weak_ptr<" + rew::name_of<ElementType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ElementType>, std::weak_ptr<ElementType>)
    FACTORY(R())
    FACTORY(R(R const&))
    FACTORY(R(std::shared_ptr<typename R::element_type> const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(operator=, R&(std::shared_ptr<typename R::element_type> const&))
    FUNCTION(reset)

    #ifdef REW_FULLY_ENABLE
//  FUNCTION(swap)
    FUNCTION(use_count)
    #endif // REW_FULLY_ENABLE

    FUNCTION(expired)
    FUNCTION(lock)

    #ifdef REW_FULLY_ENABLE
//  FUNCTION(owner_before, bool(R const&) const)
//  FUNCTION(owner_before, bool(std::shared_ptr<typename R::element_type> const&) const)
    #endif // REW_FULLY_ENABLE
REFLECTABLE_INIT()

#endif // REW_BUILTIN_WEAK_PTR_HPP
