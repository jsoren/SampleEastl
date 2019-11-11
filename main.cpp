#define EASTL_USER_DEFINED_ALLOCATOR
#include <EASTL/vector.h>
#include <EASTL/fixed_vector.h>

#include <iostream>

int main()
{
    {
        std::cout << "vector" << std::endl;
        eastl::vector<int> vec;
        for (int i = 0; i < 5; ++i)
        {
            vec.push_back(i);
            std::cout << vec[i] << std::endl;
        }
    }

    {
        std::cout << "fixed_vector" << std::endl;
        eastl::fixed_vector<int, 5> fixedVector;
        for (int i = 0; i < 5; ++i)
        {
            fixedVector.push_back(i);
            std::cout << fixedVector[i] << std::endl;
        }
    }
}