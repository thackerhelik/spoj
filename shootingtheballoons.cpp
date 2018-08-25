#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define fo(i,n) for(i=0;i<n;++i)

typedef long long int ll;

int main(){
    #if ONLINE_JUDGE
        ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	#endif

    ll n, k;
    cin >> n >> k;

    ll a[n];
    ll sum = 0, i;

    ll mn = 1000000001;

    fo(i, n)cin >> a[i], sum += a[i], mn = min(mn, a[i]);

    ll lo = 0, hi = sum, res = sum, mid;

    while(lo <= hi){
    	mid = (lo + hi) >> 1;
    	ll cursum = 0, left = 0, right = 0, kitne = 0;

    	while(1){

    		while(right < n && ( cursum + a[right] ) <= mid){
    			cursum += a[right];	
    			right++;
    		}

    		if(cursum <= mid)
		    	kitne = kitne + (right - left);

    		cursum -= a[left];
    		cursum = max(cursum, 0LL);
    		left++;
    		right = max(left, right);

    		if(left >= n)break;

    	}

    	if(kitne < k){
    		lo = mid + 1;
    	}
    	else{
    		res = mid;
    		hi = mid - 1;
    	}

    }        

    cout << res << endl;

    return 0;
}

