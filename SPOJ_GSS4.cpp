/*
Square root can be taken only 6 times for 1e18 so till that we update full upto leaf
else we just put everything as 1 afterwards
take care of x > y case
Time complexity: query is logn update is logn but initial 6 queries should be O(n) so 6*n + logn
total q*(logn + (6*n + logn))
*/
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)

typedef long long int ll;
const ll inf = 1e9;

const int MAXN = 100005;
ll segtree[4*MAXN];
ll ct[4*MAXN];
ll a[MAXN];

void init(){
	memset(segtree, 0, sizeof(segtree));
	memset(ct, 0, sizeof(ct));
	memset(a, 0, sizeof(a));
}

void build(ll node, ll be, ll en){
	if(be == en){
		segtree[node] = a[be];
		return;
	}
	ll mid = (be + en) >> 1;
	build(2*node, be, mid);
	build(2*node + 1, mid + 1, en);
	segtree[node] = segtree[2*node] + segtree[2*node + 1];
	return;
}

ll query(ll node, ll be, ll en, ll l, ll r){
	if(be > r || en < l)return 0;
	if(be >= l && en <= r){
		return segtree[node];
	}
	ll mid = (be + en) >> 1;
	ll p1 = query(2*node, be, mid, l, r);
	ll p2 = query(2*node + 1, mid + 1, en, l, r);
	return (p1 + p2);
}

void update(ll node, ll be, ll en, ll l, ll r){
	if(be > r || en < l)return;
	if(be == en){
		a[be] = (int)sqrt(a[be]);
		segtree[node] = a[be];
		return;
	}
	if(be >= l && en <= r){
		//increase count
		//if count is > 6 then no need to update return en - be + 1
		ct[node]++;
		if(ct[node] > 10){
			segtree[node] = (en - be + 1);
			return;
		}
	}
	ll mid = (be + en) >> 1;
	update(2*node, be, mid, l, r);
	update(2*node + 1, mid + 1, en, l, r);
	segtree[node] = segtree[2*node] + segtree[2*node+1];
	return; 
}

int main(){
    #if ONLINE_JUDGE
        ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	#endif

    ll i, n, q, x, l, r;
    ll ctr = 1;
    while(cin >> n){
    	init();
    	cout << "Case #" << ctr++ << ":" << endl;
	    for(i = 1; i <= n; ++i)cin >> a[i];
	    build(1, 1, n);
		cin >> q;
		for(i = 1; i <= q; ++i){
			cin >> x >> l >> r;
			if(l > r)swap(l, r);
			if(x == 0){
				update(1, 1, n, l, r);
			}
			else{
				ll ans = query(1, 1, n, l, r);
				cout << ans << endl;
			}
		}
		cout << endl;
	}
	cout << endl;
    return 0;
}
