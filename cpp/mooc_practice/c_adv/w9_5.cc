/*
编程题＃5：走出迷宫
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)
注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
当你站在一个迷宫里的时候，往往会被错综复杂的道路弄得失去方向感，如果你能得到迷宫地图，事情就会变得非常简单。 
假设你已经得到了一个n*m的迷宫的图纸，请你找出从起点到出口的最短路。

输入
第一行是两个整数n和m(1 <= n,m <= 100)，表示迷宫的行数和列数。
接下来n行，每行一个长为m的字符串，表示整个迷宫的布局。字符'.'表示空地，'#'表示墙，'S'表示起点,'T'表示出口。

输出
输出从起点到出口最少需要走的步数。(你不能起出迷宫外)

样例输入
3 3
S#T
.#.
...

样例输出
6
*/
#include <iostream>
#include <cstring>

using namespace std;

int route(int x, int y);
int min(int a, int b);
int m(0), n(0), steps(10000); // steps用来存放返回步数;
// 二维数组动态分配 phis相当于一个100*100的二维数组指针，用于存放x,y到终点需要多少步
int **phis = new int *[m];
char **maze = new char *[m];
struct coords
{
    int x;
    int y;
};

int main()
{

    cin >> m >> n;
    for (int i(0); i < n; ++i)
    {
        phis[i] = new int[n];
        memset(phis[i], -1, n * sizeof(int)); // 先将phis初始化为-1
    }
    for (int i(0); i < n; ++i)
    {
        maze[i] = new char[n];
        memset(maze[i], 0, n * sizeof(char)); // 将maze初始化为0
    }

    coords start, exit;
    for (int i(0); i < n; ++i)
        for (int j(0); j < m; ++j)
        {
            cin >> maze[i][j];     // 录入迷宫地图
            if (maze[i][j] == 'S') // 录入起点坐标
            {
                start.x = i;
                start.y = j;
            }
            else if (maze[i][j] == 'T') // 录入终点坐标
            {

                exit.x = i;
                exit.y = j;
            }
        }
    cout << route(start.x, start.y) << endl;

    return 0;
}

int route(int x, int y)
{

    if (phis[x][y] != -1)
        return phis[x][y]; // 如果以前走过这里，就直接返回phis里的值

    if (maze[x][y] == 'T') // 如果x,y就是终点,返回0步
        return 0;

    // 枚举4个方向，对于每个方向,只能往不是'#'且在边界里的地方走，可行范围是 0 <= x < m 且 0 <= y < n
    if ((x + 1 < m) && maze[x + 1][y] != '#') // 下且x + 1不会撞'#'且不会走出边界，因为可行范围是 0 <= x < m 且 0 <= y < n， 所以这里没有等号
    {
        maze[x][y] = '#';                        // 记录位置， 把走过的地方也记录成#，这样就不会再走了
        steps = min(steps, 1 + route(x + 1, y)); // 递归计算，返回值+1是因为走了一步， 且把目前存放的最低步数steps，与新返回的steps(返回值+1)做一个最小值比较，取低的那个。
        maze[x][y] = '.';                        // 撤销记录
    }
    else if ((y + 1 < n) && maze[x][y + 1] != '#') // 右
    {
        maze[x][y] = '#';                        // 记录位置， 把走过的地方也记录成#，这样就不会再走了
        steps = min(steps, 1 + route(x, y + 1)); // 递归计算
        maze[x][y] = '.';                        // 撤销记录
    }
    else if ((x - 1 >= 0) && maze[x - 1][y] != '#') // 上
    {
        maze[x][y] = '#';                        // 记录位置， 把走过的地方也记录成#，这样就不会再走了
        steps = min(steps, 1 + route(x - 1, y)); // 递归计算
        maze[x][y] = '.';                        // 撤销记录
    }
    else if ((y - 1 >= 0) && maze[x][y - 1] != '#') // 左
    {
        maze[x][y] = '#';                        // 记录位置， 把走过的地方也记录成#，这样就不会再走了
        steps = min(steps, 1 + route(x, y - 1)); // 递归计算
        maze[x][y] = '.';                        // 撤销记录
    }
    phis[x][y] = steps; // 记录当前这个点到终点所需要的步数
    return steps;
}
int min(int a, int b)
{
    return (a < b ? a : b);
}