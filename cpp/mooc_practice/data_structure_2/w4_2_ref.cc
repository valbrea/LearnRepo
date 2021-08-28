#include<iostream>
#include<vector>
#include<utility>
#include<cmath>
using namespace std;
//!  此乃简易版
 //! 思路见：https://blog.csdn.net/Jeff_Winger/article/details/81459666
class loserTree
{
public:
	loserTree(int* thePlayer, int num) {
		if (num<2) { return; }
		player = thePlayer;
		n = num;
		tree = new int[n];
 
		int s = log(n - 1) / log(2);
		s = pow(2, s);
		lowext = 2 * (n - s);
		offset = 2 * s - 1;
		int i = 0;
		for (i = 2; i <= lowext; i += 2) {
			play((i + offset) / 2, i - 1, i);
		}
		if (n % 2 == 1) {
			play(n / 2, tree[(n - 1) / 2], lowext + 1);
			i = lowext + 3;
		}
		else {
			i = lowext + 2;
		}
		for (; i <= n; i += 2) {
			play((i - lowext + n - 1) / 2, i - 1, i);
		}
	}
	~loserTree() { delete[] tree; }
 
	void replay(int k, int value) {
		player[k] = value;
		int root = k <= lowext ? (k + offset) / 2 : (n - 1 + k - lowext) / 2;
		pair<int, int> re;
		for (; root >= 1; root /= 2) {
			re = compete(tree[root],tree[0]);
			tree[root] = re.second;
			tree[0] = re.first;
		}
 
	}
	void output() const {
		for (int i = 0; i<n; i++){
			cout << player[tree[i]] << " ";
		}
	}
 
private:
	int* tree;
	int* player;
	int  n;
 
	int lowext;
	int offset;
 
	pair<int, int> compete(int x, int y) {
		pair<int, int>re;
		re.first = player[x] <= player[y] ? x : y;
		re.second = player[x]>player[y] ? x : y;
		return re;
	}
	void play(int p, int left, int right) {
		pair<int, int> re = compete(left, right);
		tree[p] = re.second;   //loser
		while (p % 2 == 1 && p>1) {
			re = compete(tree[p / 2], re.first);
			tree[p / 2] = re.second;
			p /= 2;
		}
		tree[p / 2] = re.first; //winner
	}
};
int main()
{
	int n, m;
	cin >> n >> m;
	int* players = new int[n + 1];
	for (int i = 1; i <= n; i++) {
		cin >> players[i];
	}
	loserTree ltree(players, n);
	ltree.output();
	cout << endl;
	int index, value;
	for (int i = 1; i <= m; i++) {
		cin >> index >> value;
		ltree.replay(index+1, value);
		ltree.output();
		cout << endl;
	}
 
	delete[] players;
	return 0;
 
}