#include <bits/stdc++.h>
using namespace std;
int d[35][35], p[35][35];
int dd[35][35];
int n;
map<string, int> dict;
map<int, string> dict_;

void print()
{
#ifdef _LOC_
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (p[i][j] > 100000)
                cout << "inf" << '\t';
            else
                cout << p[i][j] << '\t';
        cout << endl;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (d[i][j] > 100000)
                cout << "inf" << '\t';
            else
                cout << d[i][j] << '\t';
        cout << endl;
    }
#endif
    return;
}
void find_path(int s, int e)
{
    if (s == e)
    {
        cout << dict_[s];
        return;
    }
    else if (p[s][e] == s)
        cout << dict_[s];
    else
        find_path(s, p[s][e]);
    cout << "->(" << dd[p[s][e]][e] << ")->" << dict_[e];
}

int main()
{
#ifdef _LOC_
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    cin >> n;
    string a, b;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        dict[a] = i;
        dict_[i] = a;
    }

    memset(d, 0x3f, sizeof d);
    for (int i = 0; i < n; i++)
        // for (int j = 0; j < n; j++)
        //     p[i][j] = -1; //floyd中的可达性可以通过
        d[i][i] = 0;
    int m;
    cin >> m;
    while (m--)
    {
        int tmp;
        cin >> a >> b >> tmp;
        int i = dict[a], j = dict[b];
        if (d[i][j] > tmp)
        {
            d[j][i] = d[i][j] = tmp;
            p[i][j] = i, p[j][i] = j;
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dd[i][j] = d[i][j];
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][j] > d[i][k] + d[k][j])
                {
                    p[i][j] = p[k][j];
                    d[i][j] = d[i][k] + d[k][j];
                }
    print();

    cin >> m;
    while (m--)
    {
        cin >> a >> b;
        find_path(dict[a], dict[b]);
        cout << endl;
    }
#ifdef _LOC_
    fclose(stdout);
#endif
}
