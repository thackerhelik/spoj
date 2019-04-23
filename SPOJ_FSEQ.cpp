/*
Notice that the sequence is Fibonacci sequence.
After getting the cycle (brute), find next greater element for each.
Then apply dp to solve for each index.
*/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

/*USAGE
ordered_set X;
X.insert(1);
X.insert(3);
cout << *X.find_by_order(1) << endl; //3
cout << X.order_of_key(-5) << endl; //0
cout << X.order_of_key(1) << endl; //0
cout << (end(X) == X.order_of_key(100)) << endl; //true since utne elements nahi hai
*/

#define ll long long int

const int nax = 2e6 + 5;
ll dp[nax];
vector<int>nxt;

ll solve(int idx){
	if(dp[idx] != -1)return dp[idx];
	if(nxt[idx] == 0)return 1;
	ll ans = 1 + solve(nxt[idx]);
	return dp[idx] = ans;
}

int main(){
	int t;
	cin >> t;
	for(int tt = 1; tt <= t; ++tt){
		nxt.clear();
		cout << "Case " << tt << ": ";
		int m;
		cin >> m;
		if(m == 1){
			cout << 1 << endl;
			continue;
		}
		int cycle = 0;
		vector<ll>values;
		vector<ll>v;
		int a = 0;
		int b = 1 % m;
		values.push_back(a);
		values.push_back(b);
		int c;
		bool flag = false;
		while(1){
			c = (a + b) % m;
			values.push_back(c);
			a = b;
			b = c;
			if(a == 0 && b == 1)
				break;
		}

		values.pop_back();
		values.pop_back();
	
		for(auto it: values){
			v.push_back(it);
		}
		for(auto it: values){
			v.push_back(it);
		}

		// for(auto it: v){
		// 	cout << it << " ";
		// }
		// cout << endl;

		nxt.resize(v.size());

		stack<pair<int, int>>s;

		s.push({v[0], 0});
		for(int i = 1; i < v.size(); ++i){
			while(!s.empty() && v[i] > s.top().first){
				nxt[s.top().second] = i;
				s.pop();
			}
			s.push({v[i], i});
		}

		memset(dp, -1, sizeof(dp));

		ll ans = 0;

		for(int i = 0; i < values.size(); ++i){
			ans = ans + solve(i);
		}

		cout << ans << endl;

	}
	return 0;
}
