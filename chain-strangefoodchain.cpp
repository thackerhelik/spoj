/*
Using Dsu and maintaining relations in equivalence class of 3
*/
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

int n, k;
int par[50005];
int r[50005];

void init(){
	for(int i = 0; i < 50005; ++i){
			par[i] = i;
			r[i] = 0;
	}
}

int dsu_find(int x){
	if(x == par[x])return x;
	int temp = par[x];
	par[x] = dsu_find(par[x]);
	r[x] = r[x] + r[temp];
	return par[x];
}

bool dsu_union(int x, int y, int rr){
	int px = dsu_find(x);
	int py = dsu_find(y);
	rr--;
	if(px == py){
		int temp = (r[x] - r[y]) % 3;
		if(temp < 0)temp += 3;
		if(temp != rr)return false;
		else return true;
	}
	else{
		par[px] = py;
		int temp = (r[x] - r[y] - rr + 3) % 3;
		if(temp < 0)r[px] = -temp;
		else r[px] = -temp + 3;
		return true;
	}
}

int main(){
    #if ONLINE_JUDGE
        ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	#endif

    int x, y, d, ans, te;
    cin >> te;
    while(te--){
    	ans = 0;
	    init();
    	cin >> n >> k;
    	for(int i = 0; i < k; ++i){
    		cin >> d >> x >> y;
    		if(x > n || y > n){ans++;continue;}
    		if(!dsu_union(x, y, d))ans++;
	    }
	    cout << ans << endl;
    }        

    return 0;
}

