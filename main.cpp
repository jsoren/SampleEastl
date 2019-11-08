#include <iostream>
#include <EASTL/vector.h>
#include <EASTL/fixed_vector.h>

int main()
{
    eastl::vector<int> vec;
    for (int i = 0; i < 5; ++i)
    {
        vec.push_back(i);
    }

    for (int i = 0; i < 5; ++i)
    {
        std::cout << vec[i] << std::endl;
    }

    eastl::fixed_vector<int, 5> fixedVector;
    for (int i = 0; i < 5; ++i)
    {
        fixedVector.push_back(i);
    }

    for (int i = 0; i < 5; ++i)
    {
        std::cout << fixedVector[i] << std::endl;
    }
}