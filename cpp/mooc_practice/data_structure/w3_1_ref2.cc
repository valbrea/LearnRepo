#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
 
using namespace std;
 
const int MAX_STR_LEN = 200;
 
void solution();
 
int main()
{
    int T = 0;
    int t = 0;
 
    cin >> T;
    getchar();
    while (t < T)
    {
        solution();
        t++;
    }
 
    system("pause");
    return 0;
}
 
void solution()
{
    int i = 0;
    char str[MAX_STR_LEN];
    cin.getline(str, MAX_STR_LEN);
    while (str[i] != '\0')
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] == 'Z' ? 'A' : str[i] + 1;
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] == 'z' ? 'a' : str[i] + 1;
        }
        i++;
    }
    cout << str << endl;
}
