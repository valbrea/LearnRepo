#include <iostream>

using namespace std;

int main() {
    int t_queries(0), n_numbers(0);
    float w1[2][5000], w2[2][5000];
    int y_label[5000] = {0};
    cin >> t_queries >> n_numbers;
    for (int i(0); i < t_queries; i++)
    {
        for(int j(0); j < n_numbers; j++)
        {
            cin >> w1[i][j] >> w2[i][j] >> y_label;
        }
    }

    return 0;
}