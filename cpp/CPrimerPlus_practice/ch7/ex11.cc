#include <iostream>
#include <iomanip>
#include <ctype.h>
using namespace std;
int main()
{
    char category;
    double weight[3] = {0}, unit[3] = {2.05, 1.15, 1.09}, price[3] = {0};
    double temp(0), total(0), gross(0), pay(0), discount(0), express_fee(0);

    cout << "enter the category, 'q' for quit" << endl;
    while (cin >> category && category != 'q' && category != 'Q')
    {
        category = tolower(category);
        cout << "enter the weight(pounds) your want to buy for it." << endl;
        cin >> temp;
        if (temp <= 0)
        {
            cout << "error data!" << endl;
            break;
        }
        switch (category)
        {
        case 'a':
            weight[0] += temp;
            break;
        case 'b':
            weight[1] += temp;
            break;
        case 'c':
            weight[2] += temp;
            break;
        }
        cout << "enter the category, 'q' for quit" << endl;
    }

    for (int i(0); i < 3; ++i)
    {
        price[i] = weight[i] * unit[i];
        total += weight[i];
        gross += price[i];
    }

    if (total <= 5)
    {
        express_fee = 6.5;
    }
    else if (total <= 20)
    {
        express_fee = 14;
    }
    else
    {
        express_fee = 14 + 0.5 * (total - 20);
    }

    if (gross > 100)
        discount = gross * 0.05;
    else
        discount = 0;

    pay = gross + express_fee - discount;

    cout << "*****YOUR SHOPPING CART*****" << endl;
    cout << "a: " << unit[0] << " weight: " << weight[0] << " price: " << price[0] << endl;
    cout << "b: " << unit[1] << " weight: " << weight[1] << " price: " << price[1] << endl;
    cout << "c: " << unit[2] << " weight: " << weight[2] << " price: " << price[2] << endl;
    cout << "****************************" << endl;
    cout << "total weight: " << total << endl
        << "total price: " << gross << endl
        << "discount: " << discount << endl
        << "express fee: " << express_fee << endl
        << "payment: " << pay << endl;
    cout << "*****WELCOME NEXT TIME******" << endl;

    return 0;
}