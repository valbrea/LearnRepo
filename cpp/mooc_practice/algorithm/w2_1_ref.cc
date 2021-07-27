#include <iostream>
using namespace std;

int getPaintNum(int paint[][17]){    //获得每次成功的喷涂数
    int num = 0;
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 17; j++)
            num += paint[i][j];
    }

    return num;
}

bool guessNum(int wall[][17], int paint[][17], int n){    //判断喷涂是否成功
    int c, r;

    //根据画板颜色和周围paint颜色值判断下一行paint的颜色值
    for (r = 1; r<n; r++)
        for (c = 1; c <= n; c++)
            paint[r + 1][c] = (wall[r][c] + paint[r][c] + paint[r - 1][c] + paint[r][c - 1] + paint[r][c + 1]) % 2;

    //判断最后一行能否被画成黄色   
    for (c = 1; c <= n; c++)
        if ((paint[n][c - 1] + paint[n][c] + paint[n][c + 1] + paint[n-1][c]) % 2 != wall[n][c])
            return(false);

    return(true);
}


void theLeastPaints(int wall[][17], int paint[][17], int n){    //输出最少喷涂数
    int leastNum = 16 * 17;  //最少喷涂砖块数

    int c, cTemp = 0;
    while (1){
        if (guessNum(wall, paint, n) == true){
            if (leastNum > getPaintNum(paint))
                leastNum = getPaintNum(paint);
        }

        //枚举第一行的所有情况，枚举方法：用二进制依次加1的进位方法模拟实现
        paint[1][1]++;
        c = 1;
        while (paint[1][c] > 1) {
            paint[1][c] = 0;

            c++; 
            if (c > cTemp)
                cTemp = c;

            paint[1][c]++;
        }
        if (cTemp > n)
            break;
    }

    if (leastNum == 16 * 17)
        cout << "inf" << endl;
    else
        cout << leastNum << endl;
}

int main(){
    int wall[16][17];    //墙的颜色矩阵，行数15+1，列数15+2；1表示白色，0表示黄色，都先置0
    int paint[16][17];   //涂画矩阵，行数15+1，列数15+2；0表示不涂画，1表示涂画，都先置0

    int t;
    int n;  //墙的大小
    char c; //墙的颜色
    cin >> t;
    while (t--){
        //矩阵初始化为 0，要专门初始化！！！
        for (int i = 0; i < 16; i++){
            for (int j = 0; j < 17; j++){
                wall[i][j] = 0;
                paint[i][j] = 0;
            }
        }

        cin >> n;
        for (int i = 1; i < n+1; i++){
            for (int j = 1; j < n+1; j++){
                cin >> c;
                if (c == 'w')
                    wall[i][j] = 1;
            }
        }

        theLeastPaints(wall, paint, n);
    }

    return 0;
}