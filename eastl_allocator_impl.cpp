#define EASTL_USER_DEFINED_ALLOCATOR
#include <EASTL/allocator.h>

#include <iostream>

char memory[1024];
char* mem_ptr = memory;

namespace eastl
{

allocator::allocator(const char* EASTL_NAME(pName))
{
#if EASTL_NAME_ENABLED
    mpName = pName ? pName : EASTL_ALLOCATOR_DEFAULT_NAME;
#endif
}


allocator::allocator(const allocator& EASTL_NAME(alloc))
{
#if EASTL_NAME_ENABLED
    mpName = alloc.mpName;
#endif
}


allocator::allocator(const allocator&, const char* EASTL_NAME(pName))
{
#if EASTL_NAME_ENABLED
    mpName = pName ? pName : EASTL_ALLOCATOR_DEFAULT_NAME;
#endif
}


allocator& allocator::operator=(const allocator& EASTL_NAME(alloc))
{
#if EASTL_NAME_ENABLED
    mpName = alloc.mpName;
#endif
    return *this;
}


const char* allocator::get_name() const
{
#if EASTL_NAME_ENABLED
    return mpName;
#else
    return EASTL_ALLOCATOR_DEFAULT_NAME;
#endif
}


void allocator::set_name(const char* EASTL_NAME(pName))
{
#if EASTL_NAME_ENABLED
    mpName = pName;
#endif
}


void* allocator::allocate(size_t n, int flags)
{
#if EASTL_NAME_ENABLED
#define pName mpName
#else
#define pName EASTL_ALLOCATOR_DEFAULT_NAME
#endif

#if EASTL_DLL
    return allocate(n, EASTL_SYSTEM_ALLOCATOR_MIN_ALIGNMENT, 0, flags);
#elif (EASTL_DEBUGPARAMS_LEVEL <= 0)
    std::cout << "Allocated " << n << " bytes" << std::endl;
    void* allocated_mem = (void*)mem_ptr;
    mem_ptr += n;
    return allocated_mem;
#elif (EASTL_DEBUGPARAMS_LEVEL == 1)
    return ::new(   pName, flags, 0, (char*)0,        0) char[n];
        #else
            return ::new(   pName, flags, 0, __FILE__, __LINE__) char[n];
#endif
}


void* allocator::allocate(size_t n, size_t alignment, size_t offset, int flags)
{
#if EASTL_DLL
    // We currently have no support for implementing flags when
            // using the C runtime library operator new function. The user
            // can use SetDefaultAllocator to override the default allocator.
            EA_UNUSED(offset); EA_UNUSED(flags);

            size_t adjustedAlignment = (alignment > EA_PLATFORM_PTR_SIZE) ? alignment : EA_PLATFORM_PTR_SIZE;

            void* p = new char[n + adjustedAlignment + EA_PLATFORM_PTR_SIZE];
            void* pPlusPointerSize = (void*)((uintptr_t)p + EA_PLATFORM_PTR_SIZE);
            void* pAligned = (void*)(((uintptr_t)pPlusPointerSize + adjustedAlignment - 1) & ~(adjustedAlignment - 1));

            void** pStoredPtr = (void**)pAligned - 1;
            EASTL_ASSERT(pStoredPtr >= p);
            *(pStoredPtr) = p;

            EASTL_ASSERT(((size_t)pAligned & ~(alignment - 1)) == (size_t)pAligned);

            return pAligned;
#elif (EASTL_DEBUGPARAMS_LEVEL <= 0)
    std::cout << "Allocated " << n << " bytes" << std::endl;
    void* allocated_mem = (void*)mem_ptr;
    mem_ptr += n;
    return allocated_mem;
#elif (EASTL_DEBUGPARAMS_LEVEL == 1)
    return ::new(alignment, offset,    pName, flags, 0, (char*)0,        0) char[n];
        #else
            return ::new(alignment, offset,    pName, flags, 0, __FILE__, __LINE__) char[n];
#endif

#undef pName  // See above for the definition of this.
}


void allocator::deallocate(void* p, size_t n)
{
#if EASTL_DLL
    if (p != nullptr)
            {
                void* pOriginalAllocation = *((void**)p - 1);
                delete[](char*)pOriginalAllocation;
            }
#else
    std::cout << "Deallocated " << n << " bytes" << std::endl;
    //delete[](char*)p;
#endif
}


inline bool operator==(const allocator&, const allocator&)
{
    return true; // All allocators are considered equal, as they merely use global new/delete.
}


inline bool operator!=(const allocator&, const allocator&)
{
    return false; // All allocators are considered equal, as they merely use global new/delete.
}

}