#pragma once

#include <memory>
#include <utility>

#define LN_UNUSED(param) ((void)(param))

namespace Luna
{
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ...Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
	    return std::make_unique<T>(T(std::forward<Args>(args)...));
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
	    return std::make_shared<T>(T(std::forward<Args>(args)...));
    }
}

