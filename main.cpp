#include <iostream>

#include <EASTL/vector.h>

int main()
{
    eastl::vector<int> vec;
    for (int i = 0; i < 5; ++i)
    {
        vec.push_back(i);
    }

    std::cout << "Hello, World!" << std::endl;

    for (int i = 0; i < 5; ++i)
    {
        std::cout << vec[i] << std::endl;
    }
}