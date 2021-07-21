#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <functional>
using namespace std;
#define MAXSIZE 1000
int G[MAXSIZE][MAXSIZE];
int in[MAXSIZE];
int vist[MAXSIZE];
int e_num,v_num;
priority_queue<int,vector<int>,greater<int> > q;
int main() {
	scanf("%d%d",&v_num,&e_num);
	for (int i = 0; i < e_num; i++) {
		int a,b; scanf("%d%d",&a,&b);
		G[a][b] = 1;
		in[b]++;
	}
	int flag = 0;
	for (int i = 1; i <= v_num; i++) if (in[i] == 0) {
		q.push(i);
		vist[i] = 1;
	}
	while (!q.empty()){
		int t = q.top(); q.pop();
		for (int i = 1; i <= v_num; i++) if (G[t][i]) {
			in[i]--;
			if (in[i] == 0 && !vist[i]) {
				q.push(i);
				vist[i] = 1;
			}
		}
		if (flag) cout << ' ';
		cout << 'v' << t; flag = 1;
	}
	return 0;
}
