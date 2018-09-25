/*
we start from right to left
initially take all postions to be zero and build a BIT on the number of zeros
Now that we find the i - input[i] th zero and update it to become 0
Find the i - input[i] th zero by binary searching on the query result returned by BIT
*/

#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

const int MAXN = 200005;
int BIT[MAXN], a[MAXN], ans[MAXN], n;

void update(int x, int delta){
	for(;x<=n;x+=x&-x)
		BIT[x] += delta;
}

int query(int x){
	int sum = 0;
	for(;x>0;x-=x&-x)
		sum += BIT[x];
	return sum;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);

	int t;
	cin >> t;

	while(t--){

	    cin >> n;

	    for(int i = 1; i <= n; ++i){
	    	ans[i] = 0;
	    	a[i] = 0;	
	    	BIT[i] = 0;
	    }

	    for(int i = 1; i <= n; ++i){
	    	update(i, 1);
	    }

	    for(int i = 1; i <= n; ++i)cin >> a[i];

	    for(int i = n; i > 0; --i){
	    	int val = i - a[i];
	    	int lo = 1, hi = n, res = -1;
	    	while(lo <= hi){
	    		int mid = (lo + hi) >> 1;
	    		int kitne = query(mid);
	    		if(kitne == val){
	    			res = mid;
	    			hi = mid - 1;
	    			// break;
	    		}
	    		else if(kitne > val){
	    			hi = mid - 1;
	    		}
	    		else{
	    			lo = mid + 1;
	    		}
	    	}
	    	ans[i] = res;
	    	update(res, -1);
	    }

	    for(int i = 1; i <= n; ++i)cout << ans[i] << " ";
	    cout << endl;
	
	}

    return 0;
}

