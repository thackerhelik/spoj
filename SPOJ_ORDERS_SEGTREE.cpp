/*
we start from right to left
initially take all postions to be zero and build a segment tree on it
We have 2 cases while querying
1. tree[leftchild] >= val then we have to go to that left child and search for the val
2. tree[leftchild] < val then we have to go to the right child and search for val - tree[leftchild]
*/
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

const int MAXN = 200005;

int st[4*MAXN];
int arr[MAXN];
int pos[MAXN];
int ans[MAXN];

void build(int node, int be, int en){
	if(be == en){
		pos[be] = 1;
		st[node] = 1;
		return;
	}
	int mid = (be + en) >> 1;
	build(2*node, be, mid);
	build(2*node + 1, mid + 1, en);
	st[node] = st[2*node] + st[2*node + 1];
}

void update(int node, int be, int en, int position){
	if(be == en){
		pos[be] = 0;
		st[node] = 0;
		return;
	}
	int mid = (be + en) >> 1;
	if(position <= mid)
		update(2*node, be, mid, position);
	else update(2*node + 1, mid + 1, en, position);
	st[node] = st[2*node] + st[2*node + 1];
}

int query(int node, int be, int en, int val){
	if(be == en){
		return be;
	}
	int position;
	int mid = (be + en) >> 1;
	if(st[2*node] >= val)
		position = query(2*node, be, mid, val);
	else
		position = query(2*node + 1, mid + 1, en, val - st[2*node]);
	return position;
}


int main(){
	ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);

	int t;
	cin >> t;
	while(t--){
		
		memset(st, 0, sizeof(st));

		int n;
	    cin >> n;
	    for(int i = 1; i <= n; ++i){
	    	pos[i] = 0;
	    	cin >> arr[i];
	    }        

	    build(1, 1, n);

	    for(int i = n; i >= 0; --i){
	    	int val = i - arr[i];
	    	int k = query(1, 1, n, val);
	    	ans[i] = k;
	    	update(1, 1, n, k);
	    }

	    for(int i = 1; i <= n; ++i){
	    	cout << ans[i] << " ";
	    }
	    cout << endl;
   	}

    return 0;
}

