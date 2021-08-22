#include <iostream>
#include <vector>
using namespace std;

int d, n;
struct Rubbish{
    int x;
    int y;
    int counts;
};
int bestplot,maxrubbishs;
vector<Rubbish> v(21);

void enumerate() {
    bestplot=0; 
    maxrubbishs=0;
    for(int i=0; i<1025; i++) {
        for (int j=0; j<1025; j++) {
            int tem=0;
            for(int k=0; k<n; k++) {
                if (v[k].x<=i+d && v[k].x>=i-d && v[k].y<=j+d && v[k].y>=j-d) {
                    tem += v[k].counts;
                }
            }
            if (maxrubbishs<tem){
                maxrubbishs=tem;
                bestplot=1;
            }
            else if (maxrubbishs==tem){
                bestplot++;
            }
        }
    }
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        cin >> d;
        cin >> n;
        for(int i=0; i<n; i++) {
            cin >> v[i].x >> v[i].y >>v[i].counts;
        }       
        enumerate();
        cout << bestplot << ' ' << maxrubbishs << endl;
    }
    return 0;
}