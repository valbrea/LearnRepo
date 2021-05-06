#include<iostream>
#include<queue>
using namespace std;

int main(){
    int n;
    queue<char> password;
    char c;
    cin >> n;
    char d = cin.get();  //吃掉输入n之后打入的那个回车符
    while (n--){
        while (1){
            c = cin.get();
            if (c == '\n')
                break;
            password.push(c);
        }

        while (!password.empty()){
            c = password.front();
            if (c == ' '){
                cout << ' ';
                password.pop();
                continue;
            }
            else{
                if (c == 'z')
                    c = 'a';
                else if (c == 'Z')
                    c = 'A';
                else if ((c >= 65 && c < 90) || (c >= 97 && c < 122))
                    c = char(c + 1);
                // printf("%c",c);
                password.pop();
            }
        }
        cout << endl;
    }

    return 0;
}
