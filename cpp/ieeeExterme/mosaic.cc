#include <iostream>

using namespace std;

int main()
{
    int n_bathroom(0), cb(0), cp(0), money(0), m_b(0), m_p(0);
    int bi_blackTile[100] = {0}, pi_pinkTile[100] = {0};
    cin >> n_bathroom >> cb >> cp;
    for (int i(0); i < n_bathroom; i++)
    {
        cin >> bi_blackTile[i] >> pi_pinkTile[i];
    }
    int sum_b(0), sum_p(0);
    for (int i(0); i < n_bathroom; i++)
    {
        sum_b += bi_blackTile[i];
        sum_p += pi_pinkTile[i];
    }

    if (sum_b % 10 == 0)
    {
        m_b = sum_b / 10 * cb;
    }
    else
    {
        m_b = (sum_b / 10 + 1) * cb;
    }

    if (sum_p % 10 == 0)
    {
        m_p = sum_p / 10 * cp;
    }
    else
    {
        m_p = (sum_p / 10 + 1) * cp;
    }

    money = m_b + m_p;
    cout << money << endl;
    return 0;
}