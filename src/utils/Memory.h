#pragma once
#include <new>
#include <limits>

//#define USE_ALLOCATOR_EXCEPTIONS
#define USE_ALLOCATOR_TRACE

#ifdef USE_LVGL_ALLOCATOR
#include "lvgl/src/misc/lv_mem.h"
#define sol_alloc lv_malloc
#define sol_free lv_free
#else
#include <cstdlib>
using sol_alloc = std::malloc;
using sol_free = std::free;
#endif

#ifdef USE_ALLOCATOR_TRACE
#include <iostream>
#endif // USE_ALLOCATOR_TRACE

namespace sol::utils
{
template<class T>
struct SolAllocator
{
    typedef T value_type;
 
    SolAllocator() = default;
    template <class U>
    constexpr SolAllocator(const SolAllocator <U>&) noexcept {}
 
    T* allocate(std::size_t n)
    {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
        {
#ifdef USE_ALLOCATOR_EXCEPTIONS
            throw std::bad_array_new_length();
#else
            return nullptr;
#endif // USE_ALLOCATOR_EXCEPTIONS
        }
 

        if (T* p = static_cast<T*>(sol_alloc(n * sizeof(T))))
        {
            report(p, n);
            return p;
        }
 
#ifdef USE_ALLOCATOR_EXCEPTIONS
        throw std::bad_alloc();
#else
        return nullptr;
#endif // USE_ALLOCATOR_EXCEPTIONS
    }
 
    void deallocate(T* p, std::size_t n) noexcept
    {
        report(p, n, 0);
        sol_free(p);
    }
 
private:
    void report(T* p, std::size_t n, bool alloc = true) const
    {
#ifdef USE_ALLOCATOR_TRACE
        std::cout << (alloc ? "Alloc: (" : "Dealloc: (") << typeid(T).name() << ") - " << sizeof(T) * n
                  << " bytes at " << std::hex << std::showbase
                  << reinterpret_cast<void*>(p) << std::dec << '\n';
#endif // USE_ALLOCATOR_TRACE
    }
};
 
    template<class T, class U>
    bool operator==(const SolAllocator <T>&, const SolAllocator <U>&) { return true; }
 
    template<class T, class U>
    bool operator!=(const SolAllocator <T>&, const SolAllocator <U>&) { return false; }

    template<class T, class... argsT>
    std::shared_ptr<T> sol_make_shared(argsT... args)
    {
        SolAllocator<T> alloc;
        return std::allocate_shared<T>(alloc, args...);
    };
} // namespace sol::utils
