#include <bits/stdc++.h>
using namespace std;
 
#define endl '\n'
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i) 

const int MAXN = 40001;
int tre[4*MAXN];
int lazy[4*MAXN];
int a[MAXN];
int n, q;
 
void init(){
	for(int i = 0; i < 4*MAXN; ++i)
		tre[i] = lazy[i] = 0;
}
 
int prime(int x){
	int i;
	if(x < 2)return false;
	for(i = 2; i <= sqrt(x); ++i)
		if(x % i == 0)
			return false;
	return true;
}
 
void build(int node, int be, int en){
	if(be == en){
		if(prime(a[be]))tre[node] = 1;
		else tre[node] = 0;
		return;
	}
	int mid = (be + en) >> 1;
	build(2*node, be, mid);
	build(2*node + 1, mid + 1, en);
	tre[node] = tre[2*node] + tre[2*node + 1];
	return;
}
 
void update(int node, int be, int en, int l, int r, bool primes){
	if(lazy[node] == 1){
		tre[node] = en - be + 1;
		if(be != en){
			lazy[2*node] = lazy[2*node + 1] = 1;
		}
		lazy[node] = 0;
	}
	else if(lazy[node] == -1){
		tre[node] = 0;
		if(be != en){
			lazy[2*node] = lazy[2*node + 1] = -1;
		}
		lazy[node] = 0;
	}
	if(be > r || en < l)return;
	if(be >= l && en <= r){
		if(primes)tre[node] = en - be + 1;
		else tre[node] = 0;
		if(primes && be != en){
			lazy[2*node] = 1;
			lazy[2*node + 1] = 1;
		}
		else if(be != en){
			lazy[2*node] = -1;
			lazy[2*node + 1] = -1;
		}
		return;
	}
	int mid = (be + en) >> 1;
	update(2*node, be, mid, l, r, primes);
	update(2*node + 1, mid + 1, en, l, r, primes);
	tre[node] = tre[2*node] + tre[2*node + 1];
	return;
}
 
int query(int node, int be, int en, int l, int r){
	if(lazy[node] == 1){
		tre[node] = en - be + 1;
		if(be != en){
			lazy[2*node] = lazy[2*node + 1] = 1;
		}
		lazy[node] = 0;
	}
	else if(lazy[node] == -1){
		tre[node] = 0;
		if(be != en){
			lazy[2*node] = lazy[2*node + 1] = -1;
		}
		lazy[node] = 0;
	}
	if(be > r || en < l)return 0;
	if(be >= l && en <= r){
		return tre[node];
	}
	int mid = (be + en) >> 1;
	int p1 = query(2*node, be, mid, l, r);
	int p2 = query(2*node + 1, mid + 1, en, l, r);
	return (p1 + p2);
}
 
int main(){
    #if ONLINE_JUDGE
        ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	#endif
        int tc;
        cin >> tc;
    for(int it = 1; it <= tc; ++it){
    		
    		init();
 
    		cout << "Case " << it << ": " << endl;
    	    int i;
		    cin >> n >> q;
		    
		    for(i = 1; i <= n; ++i){
		    	cin >> a[i];
		    }
		    
		    build(1, 1, n);
 
		    int t, l, r, v;
		    while(q--){
		    	cin >> t;
		    	if(t == 0){
		    		cin >> l >> r >> v;
		    		if(prime(v))
		    			update(1, 1, n, l, r, true);
		    		else
		    			update(1, 1, n, l, r, false);
		    	}
		    	else{
		    		cin >> l >> r;
		    		int ans = query(1, 1, n, l, r);
		    		cout << ans << endl;
		    	}
		    }
    }
    return 0;
}
