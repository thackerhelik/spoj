/*
O(N^3) dp is easy. To convert to O(N^2) dp observe that dp states are highly overlapping
*/
#include <bits/stdc++.h>
using namespace std;

int dp[2005][2005];
int coins[2005];
int prefix_coins[2005];
int n;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int c, p;
	cin >> n;
	
	for(p = 1; p <= n; ++p)
		cin >> coins[n+1-p];
	
	for(p = 1; p <= n; ++p)
		prefix_coins[p] = prefix_coins[p - 1] + coins[p];
	
	
	for(c = 1; c <= n; ++c){
		for(p = 1; p <= n; ++p){
			dp[c][p] = max(dp[c][p], dp[c][p-1]);
			if((2*p-1) <= c)
				dp[c][p] = max(dp[c][p], prefix_coins[c] - dp[c - (2*p-1)][2*p-1]);
			if((2*p) <= c)
				dp[c][p] = max(dp[c][p], prefix_coins[c] - dp[c - (2*p)][2*p]);
		}
	}

	cout << dp[n][1] << endl;

	return 0;
}
