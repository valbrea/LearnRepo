#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    const double salary_per_hour(10.00);
    const double rate(1.5);
    const double tax1(0.15), tax2(0.2), tax3(0.25);
    double work_time(0), salary(0), tax(0);
    cout << "Enter your working hours per week." << endl;
    cin >> work_time;
    if (work_time > 40)
        work_time = (work_time - 40) * rate + 40;
    salary = work_time * salary_per_hour;
    if (salary > 300)
        tax = (salary - 300) * tax2 + 300 * tax1;
    else if (salary > 450)
        tax = (salary - 450) * tax3 + 300 * tax1 + 150 * tax2;
    else
        tax = salary * tax1;
    
    cout << setw(12) << "Total_Salary" << setw(12) << "Tax" << setw(12) << "Net_Income" << endl;
    cout << setw(12) << salary << setw(12) << tax << setw(12) << salary - tax << endl;
    
    return 0;
}