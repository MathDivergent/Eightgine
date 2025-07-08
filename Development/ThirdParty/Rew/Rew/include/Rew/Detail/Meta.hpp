#ifndef REW_DETAIL_META_HPP
#define REW_DETAIL_META_HPP

#include <type_traits> // conjunction, disjunction, false_type, true_type, void_t
#include <utility> // pair

template <typename ReflectableType, typename enable = void>
struct xxrew_alias { using R = ReflectableType; };

template <typename ReflectableType, typename enable = void>
struct xxrew_traits;

namespace rew
{

namespace meta
{

template <typename T> T&& decltype_value(T&&); // not impl
void decltype_value(); // not impl

template <typename Type>
struct type_identity { using type = Type; };

template <typename Type>
struct inherits : std::conditional_t
<
    std::conjunction_v< std::is_class<Type>, std::negation<std::is_final<Type>> >,
    Type,
    type_identity<Type>
> {};

template <typename ReferenceType>
struct to_reflectable_reference { using type = std::remove_const_t<std::remove_reference_t<ReferenceType>>*; };

template <typename PointerType>
struct to_reflectable_pointer { using type = std::remove_const_t<std::remove_pointer_t<PointerType>>*; };

template <typename ObjectType>
struct to_reflectable_object { using type = std::remove_const_t<ObjectType>; };

template <typename, typename enable = void> struct is_complete : std::false_type {};
template <typename Type> struct is_complete<Type, std::void_t<decltype(sizeof(Type))>> : std::true_type {};

template <typename, typename enable = void> struct is_custom_name : std::false_type {};
template <typename ReflectableType>
struct is_custom_name<ReflectableType, std::void_t<decltype(&::xxrew_traits<ReflectableType>::name)>> : std::true_type {};

template <typename, typename enable = void> struct is_custom_registry : std::false_type {};
template <typename ReflectableType>
struct is_custom_registry<ReflectableType, std::void_t<decltype(&::xxrew_traits<ReflectableType>::registry)>> : std::true_type {};

template <typename, typename enable = void> struct is_lazy : std::false_type {};
template <typename ReflectableType>
struct is_lazy<ReflectableType, std::void_t<typename ::xxrew_traits<ReflectableType>::lazy>> : std::true_type {};

template <typename, typename enable = void> struct is_builtin : std::false_type {};
template <typename ReflectableType>
struct is_builtin<ReflectableType, std::void_t<typename ::xxrew_traits<ReflectableType>::biiltin>> : std::true_type {};

template <typename MemberPointerType, typename DirtyMemberPointerType>
struct mark_dirty;

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...) const, DirtyReturnType(DirtyArgumentTypes...) const>
{
    using type = DirtyReturnType(ReflectableType::*)(DirtyArgumentTypes...) const;
};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...) const&, DirtyReturnType(DirtyArgumentTypes...) const&>
{
    using type = DirtyReturnType(ReflectableType::*)(DirtyArgumentTypes...) const&;
};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...), DirtyReturnType(DirtyArgumentTypes...)>
{
    using type = DirtyReturnType(ReflectableType::*)(DirtyArgumentTypes...);
};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...)&, DirtyReturnType(DirtyArgumentTypes...)&>
{
    using type = DirtyReturnType(ReflectableType::*)(DirtyArgumentTypes...)&;
};

template <typename ReturnType, typename... ArgumentTypes,
          typename DirtyReturnType, typename... DirtyArgumentTypes>
struct mark_dirty<ReturnType(*)(ArgumentTypes...), DirtyReturnType(DirtyArgumentTypes...)>
{
    using type = DirtyReturnType(*)(DirtyArgumentTypes...);
};

template <typename ReflectableType, typename PropertyType, typename DirtyPropertyType>
struct mark_dirty<PropertyType ReflectableType::*, DirtyPropertyType>
{
    using type = DirtyPropertyType ReflectableType::*;
};

template <typename PropertyType, typename DirtyPropertyType>
struct mark_dirty<PropertyType*, DirtyPropertyType>
{
    using type = DirtyPropertyType*;
};

template <typename PropertyType>
struct property_traits;

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType(ReflectableType::*)(void) const> { using type = PropertyType; };

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType(ReflectableType::*)(void) const&> { using type = PropertyType; };

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType(ReflectableType::*)(void)> { using type = PropertyType; };

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType(ReflectableType::*)(void)&> { using type = PropertyType; };

template <typename ReflectableType, typename PropertyType>
struct property_traits<void(ReflectableType::*)(PropertyType)> { using type = PropertyType; };

template <typename ReflectableType, typename PropertyType>
struct property_traits<void(ReflectableType::*)(PropertyType)&> { using type = PropertyType; };

template <typename PropertyType>
struct property_traits<PropertyType(*)(void)> { using type = PropertyType; };

template <typename PropertyType>
struct property_traits<PropertyType() const> { using type = PropertyType; };

template <typename PropertyType>
struct property_traits<PropertyType()> { using type = PropertyType; };

template <typename PropertyType>
struct property_traits<void(PropertyType)> { using type = PropertyType; };

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType ReflectableType::*> { using type = PropertyType; };

template <typename PropertyType>
struct property_traits<PropertyType*> { using type = PropertyType; };

template <typename>
struct function_traits;

template <typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ArgumentTypes...) const>
{
    using dirty_type = ReturnType(ArgumentTypes...) const;
    using dirty_pointer = ReturnType(*)(ArgumentTypes...);

    using type = typename ::xxrew_alias<ReturnType>::R(typename ::xxrew_alias<ArgumentTypes>::R...) const;
    using pointer = typename ::xxrew_alias<ReturnType>::R(*)(typename ::xxrew_alias<ArgumentTypes>::R...);
};

template <typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ArgumentTypes...) const&>
{
    using dirty_type = ReturnType(ArgumentTypes...) const&;
    using dirty_pointer = ReturnType(*)(ArgumentTypes...);

    using type = typename ::xxrew_alias<ReturnType>::R(typename ::xxrew_alias<ArgumentTypes>::R...) const&;
    using pointer = typename ::xxrew_alias<ReturnType>::R(*)(typename ::xxrew_alias<ArgumentTypes>::R...);
};

template <typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ArgumentTypes...)>
{
    using dirty_type = ReturnType(ArgumentTypes...);
    using dirty_pointer = ReturnType(*)(ArgumentTypes...);

    using type = typename ::xxrew_alias<ReturnType>::R(typename ::xxrew_alias<ArgumentTypes>::R...);
    using pointer = typename ::xxrew_alias<ReturnType>::R(*)(typename ::xxrew_alias<ArgumentTypes>::R...);
};

template <typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ArgumentTypes...)&>
{
    using dirty_type = ReturnType(ArgumentTypes...)&;
    using dirty_pointer = ReturnType(*)(ArgumentTypes...);

    using type = typename ::xxrew_alias<ReturnType>::R(typename ::xxrew_alias<ArgumentTypes>::R...)&;
    using pointer = typename ::xxrew_alias<ReturnType>::R(*)(typename ::xxrew_alias<ArgumentTypes>::R...);
};

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ClassType::*)(ArgumentTypes...) const>
    : function_traits<ReturnType(ArgumentTypes...) const> {};

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ClassType::*)(ArgumentTypes...) const&>
    : function_traits<ReturnType(ArgumentTypes...) const&> {};

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ClassType::*)(ArgumentTypes...)>
    : function_traits<ReturnType(ArgumentTypes...)> {};

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ClassType::*)(ArgumentTypes...)&>
    : function_traits<ReturnType(ArgumentTypes...)&> {};

template <typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(*)(ArgumentTypes...)>
    : function_traits<ReturnType(ArgumentTypes...)> {};

template <typename>
struct deleter_traits;

template <typename ReturnType, typename ReflectableType>
struct deleter_traits<ReturnType(ReflectableType)>
{
    using dirty_type = ReturnType(ReflectableType);
    using dirty_pointer = ReturnType(*)(ReflectableType);

    using type = typename ::xxrew_alias<ReturnType>::R(typename ::xxrew_alias<ReflectableType>::R);
    using pointer = typename ::xxrew_alias<ReturnType>::R(*)(typename ::xxrew_alias<ReflectableType>::R);
};

template <typename ReturnType, typename ReflectableType>
struct deleter_traits<ReturnType(*)(ReflectableType)>
    : deleter_traits<ReturnType(ReflectableType)> {};

namespace detail
{

template <typename ReflectableType, typename ParentReflectableType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr_impl(ReturnType(ParentReflectableType::* function)(ArgumentTypes...) const)
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ReturnType(ParentReflectableType::* function)(ArgumentTypes...) const)
        {
            return static_cast<ReturnType(ReflectableType::*)(ArgumentTypes...) const>(function);
        }
    };
    return xxinner::get(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr_impl(ReturnType(ParentReflectableType::* function)(ArgumentTypes...) const&)
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ReturnType(ParentReflectableType::* function)(ArgumentTypes...) const&)
        {
            return static_cast<ReturnType(ReflectableType::*)(ArgumentTypes...) const&>(function);
        }
    };
    return xxinner::get(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr_impl(ReturnType(ParentReflectableType::* function)(ArgumentTypes...))
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ReturnType(ParentReflectableType::* function)(ArgumentTypes...))
        {
            return static_cast<ReturnType(ReflectableType::*)(ArgumentTypes...)>(function);
        }
    };
    return xxinner::get(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr_impl(ReturnType(ParentReflectableType::* function)(ArgumentTypes...)&)
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ReturnType(ParentReflectableType::* function)(ArgumentTypes...)&)
        {
            return static_cast<ReturnType(ReflectableType::*)(ArgumentTypes...)&>(function);
        }
    };
    return xxinner::get(function);
}

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr_impl(ReturnType(*function)(ArgumentTypes...))
{
    return function;
}

template <typename ReflectableType, typename ParentReflectableType, typename ValueType>
constexpr auto property_ptr_impl(ValueType ParentReflectableType::* property)
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ValueType ParentReflectableType::* property)
        {
            return static_cast<ValueType ReflectableType::*>(property);
        }
    };
    return xxinner::get(property);
}

} // namespace detail

template <typename...>
struct access_traits;

template <>
struct access_traits<>
{
    template <typename...>
    struct property
    {
        template <typename PropertyType>
        static constexpr auto of(PropertyType(*iproperty)(void), void(*oproperty)(PropertyType))
        {
            return std::make_pair(iproperty, oproperty);
        }

        template <typename PropertyType>
        static constexpr auto of(PropertyType* iproperty, PropertyType* oproperty)
        {
            return std::make_pair(iproperty, oproperty);
        }
    };

    template <typename PropertyType>
    struct property<PropertyType()>
    {
        static constexpr auto of(typename ::xxrew_alias<PropertyType>::R(*iproperty)(void), void(*oproperty)(typename ::xxrew_alias<PropertyType>::R))
        {
            return std::make_pair(iproperty, oproperty);
        }
    };

    template <typename PropertyType>
    struct property<PropertyType>
    {
        static constexpr auto of(typename ::xxrew_alias<PropertyType>::R* iproperty, typename ::xxrew_alias<PropertyType>::R* oproperty)
        {
            return std::make_pair(iproperty, oproperty);
        }
    };

    template <typename...>
    struct function
    {
        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(*function)(ArgumentTypes...)) { return function; }
    };

    template <typename ReturnType, typename... ArgumentTypes>
    struct function<ReturnType(ArgumentTypes...)>
    {
        static constexpr auto of(typename ::xxrew_alias<ReturnType>::R(*function)(typename ::xxrew_alias<ArgumentTypes>::R...)) { return function; }

        template <typename OtherReturnType, typename... OtherArgumentTypes>
        static constexpr auto of(OtherReturnType(*function)(OtherArgumentTypes...)) { return function; }
    };
};

template <class ClassType>
struct access_traits<ClassType>
{
    template <typename GetterType, typename SetterType>
    static constexpr auto property_data(GetterType iproperty, SetterType oproperty)
    {
        return std::make_pair(detail::property_ptr_impl<ClassType>(iproperty), detail::property_ptr_impl<ClassType>(oproperty));
    }

    template <typename GetterType, typename SetterType>
    static constexpr auto function_data(GetterType iproperty, SetterType oproperty)
    {
        return std::make_pair(detail::function_ptr_impl<ClassType>(iproperty), detail::function_ptr_impl<ClassType>(oproperty));
    }

    template <typename FunctionType>
    static constexpr auto function_data(FunctionType function)
    {
        return detail::function_ptr_impl<ClassType>(function);
    }

    template <typename...>
    struct property
    {
        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType ParentClassType::* iproperty, PropertyType ParentClassType::* oproperty)
        {
            return property_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename PropertyType>
        static constexpr auto of(PropertyType(*iproperty)(void), void(*oproperty)(PropertyType)) { return std::make_pair(iproperty, oproperty); }

        template <typename PropertyType>
        static constexpr auto of(PropertyType* iproperty, PropertyType* oproperty) { return std::make_pair(iproperty, oproperty); }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType() const>
    {
        using PropertyType = typename ::xxrew_alias<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, typename type_identity<PropertyType(ParentClassType::*)(void) const>::type)
        {
            return function_data(iproperty, iproperty);
        }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType() const&>
    {
        using PropertyType = typename ::xxrew_alias<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, typename type_identity<PropertyType(ParentClassType::*)(void) const&>::type)
        {
            return function_data(iproperty, iproperty);
        }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType()>
    {
        using PropertyType = typename ::xxrew_alias<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), typename type_identity<PropertyType(ParentClassType::*)(void)>::type)
        {
            return function_data(iproperty, iproperty);
        }

        static constexpr auto of(PropertyType(*iproperty)(void), void(*oproperty)(PropertyType))
        {
            return std::make_pair(iproperty, oproperty);
        }

        static constexpr auto of(PropertyType(*iproperty)(void), typename type_identity<PropertyType(*)(void)>::type)
        {
            return std::make_pair(iproperty, iproperty);
        }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType()&>
    {
        using PropertyType = typename ::xxrew_alias<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, typename type_identity<PropertyType(ParentClassType::*)(void)&>::type)
        {
            return function_data(iproperty, iproperty);
        }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType>
    {
        using PropertyType = typename ::xxrew_alias<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType ParentClassType::* iproperty, PropertyType ParentClassType::* oproperty)
        {
            return property_data(iproperty, oproperty);
        }

        static constexpr auto of(PropertyType* iproperty, PropertyType* oproperty) { return std::make_pair(iproperty, oproperty); }
    };

    template <typename...>
    struct function
    {
        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ClassType::* function)(ArgumentTypes...) const) { return function; }
        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ParentClassType::* function)(ArgumentTypes...) const) { return function_data(function); }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ClassType::* function)(ArgumentTypes...) const&) { return function; }
        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ParentClassType::* function)(ArgumentTypes...) const&) { return function_data(function); }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ClassType::* function)(ArgumentTypes...)) { return function; }
        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ParentClassType::* function)(ArgumentTypes...)) { return function_data(function); }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ClassType::* function)(ArgumentTypes...)&) { return function; }
        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ParentClassType::* function)(ArgumentTypes...)&) { return function_data(function); }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(*function)(ArgumentTypes...)) { return function; }
    };

    template <typename DirtyReturnType, typename... DirtyArgumentTypes>
    struct function<DirtyReturnType(DirtyArgumentTypes...) const>
    {
        static constexpr auto of(typename ::xxrew_alias<DirtyReturnType>::R(ClassType::* function)(typename ::xxrew_alias<DirtyArgumentTypes>::R...) const) { return function; }

        template <class ParentClassType>
        static constexpr auto of(typename ::xxrew_alias<DirtyReturnType>::R(ParentClassType::* function)(typename ::xxrew_alias<DirtyArgumentTypes>::R...) const)
        {
            return function_data(function);
        }
    };

    template <typename DirtyReturnType, typename... DirtyArgumentTypes>
    struct function<DirtyReturnType(DirtyArgumentTypes...) const&>
    {
        static constexpr auto of(typename ::xxrew_alias<DirtyReturnType>::R(ClassType::* function)(typename ::xxrew_alias<DirtyArgumentTypes>::R...) const&) { return function; }

        template <class ParentClassType>
        static constexpr auto of(typename ::xxrew_alias<DirtyReturnType>::R(ParentClassType::* function)(typename ::xxrew_alias<DirtyArgumentTypes>::R...) const&)
        {
            return function_data(function);
        }
    };

    template <typename DirtyReturnType, typename... DirtyArgumentTypes>
    struct function<DirtyReturnType(DirtyArgumentTypes...)>
    {
        static constexpr auto of(typename ::xxrew_alias<DirtyReturnType>::R(ClassType::* function)(typename ::xxrew_alias<DirtyArgumentTypes>::R...)) { return function; }

        template <class ParentClassType>
        static constexpr auto of(typename ::xxrew_alias<DirtyReturnType>::R(ParentClassType::* function)(typename ::xxrew_alias<DirtyArgumentTypes>::R...))
        {
            return function_data(function);
        }

        static constexpr auto of(typename ::xxrew_alias<DirtyReturnType>::R(*function)(typename ::xxrew_alias<DirtyArgumentTypes>::R...)) { return function; }
    };

    template <typename DirtyReturnType, typename... DirtyArgumentTypes>
    struct function<DirtyReturnType(DirtyArgumentTypes...)&>
    {
        static constexpr auto of(typename ::xxrew_alias<DirtyReturnType>::R(ClassType::* function)(typename ::xxrew_alias<DirtyArgumentTypes>::R...)&) { return function; }

        template <class ParentClassType>
        static constexpr auto of(typename ::xxrew_alias<DirtyReturnType>::R(ParentClassType::* function)(typename ::xxrew_alias<DirtyArgumentTypes>::R...)&)
        {
            return function_data(function);
        }
    };
};

} // namespace meta

} // namespace rew

#endif // REW_DETAIL_META_HPP
