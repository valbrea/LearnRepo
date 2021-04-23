#include <iostream>
#include <vector>
#include <map>
using namespace std;
 
int main () {
	int n;
	cin >> n;
	for (int i = 0; i != n; ++i) {
		map <int, int> ploy;
		int index, value, over = 0;
		while (cin >> value >> index) {
			if (index < 0)
				over++;
			else {
				pair <map <int, int>::iterator, bool> ret = 
						ploy.insert(make_pair(index, value));
				if (!ret.second)
					ret.first -> second += value;
			}
			if (over == 2)
		 		break;
		}
		for (map <int, int>::reverse_iterator riter = ploy.rbegin();
				riter != ploy.rend(); ++riter) {
			if (riter -> second != 0)
				cout << "[ " << riter -> second << ' ' << riter -> first << " ] ";  
		}
		cout << endl;
	}	
	return 0;
}
