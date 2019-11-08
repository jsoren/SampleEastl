#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec;
    for (int i = 0; i < 5; ++i)
    {
        vec.push_back(i);
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}