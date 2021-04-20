#include <iostream>
int main()
{
    char temp = 'A';
    for (int i(0); i < 6; ++i)
    {
        for (int j(0); j < i + 1; ++j, ++temp)
        {
            std::cout << temp;
        }
        std::cout << std::endl;
    }

    return 0;
}