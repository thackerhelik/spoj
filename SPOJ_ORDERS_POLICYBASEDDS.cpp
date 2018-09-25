/*
we start from right to left
initially take all postions to be zero
now if right element has to move x positions to left its final position has to be i - input[i]
so we find the (i - input[i])th zero. this can be done in various ways. Here we used ordered set
*/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

#define endl '\n'

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
cout << (end(X) == X.order_of_key(100)) << endl; //true
*/

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
	    int n, i;
	    cin >> n;
	    int arr[n];
	    int ans[n];

		ordered_set X;

		for(i = 0; i < n; ++i)
			X.insert(i);            
		
		for(i = 0; i < n; ++i){
			cin >> arr[i];
		}

		for(i = n - 1; i >= 0; --i){
			int val = i - arr[i];
			ans[i] = *X.find_by_order(val);
			X.erase(ans[i]);
		}

		for(i = 0; i < n; ++i)
			cout << ans[i] + 1 << " ";
		cout << endl;
	}

    return 0;
}

