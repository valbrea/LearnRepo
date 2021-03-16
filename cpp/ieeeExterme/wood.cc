#include <iostream>

using namespace std;

int main()
{
    int c_craft(0), n_slots(0), p_pile(0), w_wood(0);
    int t_table(0);

    cin >> c_craft >> n_slots >> p_pile >> w_wood;
    if (c_craft > w_wood)
    {
        cout << "0" << endl;
    }
    else
    {
        if (c_craft >= p_pile)
        {
            t_table = w_wood / c_craft;
        }
        else
        {
            // 2 4 4 12(13)
            int full(0), left_slot(0), left_wood(0);
            full = w_wood / p_pile;             // 几个满的口袋 3
            left_wood = w_wood - full * p_pile; //还剩多少木头 0
            if (w_wood % p_pile == 0)           // 如果整除
            {
                left_slot = n_slots - full; // 还剩几个空口袋 1(12)
            }
            else
            {
                left_slot = n_slots - full - 1; // 有个口袋装零碎木头 0(13)
            }

            while (left_slot >= 0 && full <= n_slots)
            {
                if (left_wood > c_craft)
                {
                    t_table++;
                    left_slot--;
                    left_wood -= c_craft;
                }
                else if ((left_slot == 0) && (left_wood < c_craft))
                {
                    left_wood = p_pile - (c_craft - left_wood);
                    t_table++;
                    full--;
                }
                else
                {
                    left_wood = p_pile - (c_craft - left_wood);
                    t_table++;
                    left_slot--;
                    full--;
                }
            }
            if (left_wood == c_craft)
            {
                t_table++;
            }
        }
        cout << t_table << endl;
    }

    return 0;
}