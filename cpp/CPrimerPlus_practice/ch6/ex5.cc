#include <iostream>
int main()
{
    for (int i(0); i < 5; ++i)
    {
        char temp = 'A';
        for (int j(0); j < 4 - i; ++j)
        {
            std::cout << ' ';
        }
        for (int j(4 - i); j < 5; ++j, ++temp)
        {
            std::cout << temp;
        }
        temp--;
        temp--;
        for (int j(6); j < i + 6; ++j, --temp)
        {
            std::cout << temp;
        }
        std::cout << std::endl;
    }

    return 0;
}