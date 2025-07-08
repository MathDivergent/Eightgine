#ifndef REW_BUILTIN_QUEUE_HPP
#define REW_BUILTIN_QUEUE_HPP

#include <queue> // queue

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

// default container for queue
#include <Rew/BuiltIn/deque.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ValueType, class ContainerType>),
    (std::queue<ValueType, ContainerType>), std::queue<rew::clean_of<ValueType>, rew::clean_of<ContainerType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::queue<ValueType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::queue<" + rew::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType, class ContainerType>), std::queue<ValueType, ContainerType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME("std::queue<" + rew::name_of<ValueType>() + ", " + rew::name_of<ContainerType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType, class ContainerType>), std::queue<ValueType, ContainerType>)
    FACTORY(R())

    #ifdef REW_FULLY_ENABLE
    FACTORY(R(typename R::container_type const&))
    #endif // REW_FULLY_ENABLE

    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(front, typename R::reference())
    FUNCTION(front, typename R::const_reference() const)
    FUNCTION(back, typename R::reference())
    FUNCTION(back, typename R::const_reference() const)
    FUNCTION(empty)
    FUNCTION(size)
    FUNCTION(push, void(typename R::const_reference))
    FUNCTION(pop)

    #ifdef REW_FULLY_ENABLE
    FUNCTION(swap)
    #endif // REW_FULLY_ENABLE
REFLECTABLE_INIT()

#endif // REW_BUILTIN_QUEUE_HPP
