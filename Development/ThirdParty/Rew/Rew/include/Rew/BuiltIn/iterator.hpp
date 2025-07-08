#ifndef REW_BUILTIN_ITERATOR_HPP
#define REW_BUILTIN_ITERATOR_HPP

#include <Rew/Reflectable.hpp>

#ifdef REW_FULLY_ENABLE
TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainerType>, std_const_iterator,
    std_const_iterator<StdContainerType>, typename rew::clean_of<StdContainerType>::const_iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainerType>, std_const_iterator<StdContainerType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(rew::name_of<StdContainerType>() + "::const_iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainerType>, std_const_iterator<StdContainerType>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainerType>, std_iterator,
    std_iterator<StdContainerType>, typename rew::clean_of<StdContainerType>::iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainerType>, std_iterator<StdContainerType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(rew::name_of<StdContainerType>() + "::iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainerType>, std_iterator<StdContainerType>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainerType>, std_const_reverse_iterator,
    std_const_reverse_iterator<StdContainerType>, typename rew::clean_of<StdContainerType>::const_reverse_iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainerType>, std_const_reverse_iterator<StdContainerType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(rew::name_of<StdContainerType>() + "::const_reverse_iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainerType>, std_const_reverse_iterator<StdContainerType>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainerType>, std_reverse_iterator,
    std_reverse_iterator<StdContainerType>, typename rew::clean_of<StdContainerType>::reverse_iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainerType>, std_reverse_iterator<StdContainerType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(rew::name_of<StdContainerType>() + "::reverse_iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainerType>, std_reverse_iterator<StdContainerType>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainerType>, std_const_local_iterator,
    std_const_local_iterator<StdContainerType>, typename rew::clean_of<StdContainerType>::const_local_iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainerType>, std_const_local_iterator<StdContainerType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(rew::name_of<StdContainerType>() + "::const_local_iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainerType>, std_const_local_iterator<StdContainerType>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainerType>, std_local_iterator,
    std_local_iterator<StdContainerType>, typename rew::clean_of<StdContainerType>::local_iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainerType>, std_local_iterator<StdContainerType>)
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(rew::name_of<StdContainerType>() + "::local_iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainerType>, std_local_iterator<StdContainerType>)
REFLECTABLE_INIT()
#endif // REW_FULLY_ENABLE

#endif // REW_BUILTIN_ITERATOR_HPP
