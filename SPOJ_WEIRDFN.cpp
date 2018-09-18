/*input
Time limit is too strict.
Basically maintain two priority queues left and right
and you can then find minimum element easily.
*/
#include <bits/stdc++.h>
 
using namespace std;
 
#define endl '\n'
 
typedef long long int ll;
 
const ll mod=1000000007;
 
int main(){
 
 
    ll val, i, t, a, b, c, n, s;
    scanf("%lld", &t);
    
    while(t--){
 		
	    priority_queue<ll>lefts;
	    priority_queue<ll>rights;
 
 		scanf("%lld%lld%lld%lld", &a,&b,&c,&n);
 
    	s = 1;
        lefts.push(1);

    	for(i = 2; i <= n; i++){
            ll mid = lefts.top();
       		val = (a*mid + b*i + c)%mod;
    		s = s + val;
    		
            if(mid < val){
                rights.push(-val);
            }
            else{
                lefts.push(val);
            }

    		  
            while(lefts.size() > rights.size() + 1){
                rights.push(-1*lefts.top());
                lefts.pop();
            }
            while(rights.size() > lefts.size()){
                lefts.push(rights.top()*-1);
                rights.pop();
            }

    	}
 
 		printf("%lld\n", s);
    	
    }        
 
    return 0;
}
 
 
