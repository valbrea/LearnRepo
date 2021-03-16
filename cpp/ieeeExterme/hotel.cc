#include <iostream>

using namespace std;

int main()
{
    int t_times(0), m_floor(0), n_room(0), k_switch(0), count(0);
    int c_correct[100000]; 

    cin >> t_times;
    for (int i(0); i < t_times; ++i)
    {
        count = 0;
        cin >> m_floor >> n_room >> k_switch;

        for (int j(0); j < m_floor; ++j)
        {
            cin >> c_correct[j];
        }
        for (int i(0); i < m_floor - 1; ++i)
        {
            for (int j(0); j < m_floor - 1 - i; ++j)
            {
                int temp(0);
                if (c_correct[j] > c_correct[j + 1])
                {
                    temp = c_correct[j];
                    c_correct[j] = c_correct[j + 1];
                    c_correct[j + 1] = temp;
                }
            }
        }
        for (int i(0); i < k_switch; ++i)
        {
            count += n_room - c_correct[i];
        }
        for (int i(k_switch); i < m_floor; ++i)
        {
            count += c_correct[i];
        }
        cout << count << endl;
    }
    return 0;
}
