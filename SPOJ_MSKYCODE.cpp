/*
To find subsets of 4 having gcd = 1, we can find subsets of 4 having gcd > 1 and subtract it from nC4.
Calculating gcd > 1 can be done by finding the count of numbers divisible by i (i from 2 to max)
so countC4 gives such numbers having gcd = i (greater than 1)
Now, we can multiply the count by mobius function since it will include all numbers having odd unique primes and subtract all 
numbers having even unique primes, and ignores the non square-free numbers.
*/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

#define endl '\n'
#define fo(i,n) for(i=0;i<n;++i)
#define forr(i,n) for(i=n-1;i>=0;--i)
#define rep(i,a,b) for(i=a;i<=b;++i)
#define per(i,a,b) for(i=b;i>=a;--i)

#define ffs(a) __builtin_ffs(a) // find first set
#define clz(a) __builtin_clz(a) // count leading zeroes
#define ctz(a) __builtin_ctz(a) // count trailing zeroes
#define popc(a) __builtin_popcount(a) // count set bits
#define popcll(a) __builtin_popcountll(a) //count set bits for long long int

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define yolo "debug_statement"

typedef long long int ll;
typedef long double ld;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

const ll inf = 1e9;
const ld eps = 1e-9;
const ld pi=acos(-1);
const ll mod=1000000007;

ll powmod(ll a,ll b,ll mo=mod){ll res=1;a%=mo; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mo;a=a*a%mo;}return res;}

inline ll inv_(ll a) {return powmod(a, mod-2, mod);}
inline ll add(ll a, ll b){a%=mod; b%=mod; a+=b;if(a>=mod)a-=mod;return a;}
inline ll mul(ll a, ll b){a%=mod; b%=mod; return a*1ll*b%mod;}
inline ll sub(ll a, ll b){a%=mod; b%=mod; a-=b;if(a<0)a+=mod;return a;}

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

const int nax = 10005;
int mobius[nax];
bool prime[nax];

void mobius_function(){
	for(int i = 0; i < nax; ++i){prime[i] = 1; mobius[i] = 1;}
	prime[0] = prime[1] = false;
	for(int i = 2; i < nax; ++i){
		if(prime[i]){
			mobius[i] = -1;
			for(int j = 2*i; j < nax; j += i){
				prime[j] = false;
				mobius[j] = mobius[j] * -1;
				int quotient = j / i;
				if(quotient % i == 0)
					mobius[j] = 0;
			}
		}
	}
}

ll NC4(int n){
	ll ans = (1ll*n*(n - 1)*(n - 2)*(n - 3))/(4ll*3*2*1);
	return ans;
}

int main(){
    #if ONLINE_JUDGE
        ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	#endif

    mobius_function();

    int n;
    while(cin >> n){
 		vector<int>v;
    	v.resize(n);
    	int count[10001] = {0};
    	for(int i = 0; i < n; ++i){
    		cin >> v[i];	
    		count[v[i]]++;
    	}
    	for(int i = 2; i <= 10000; ++i){
    		for(int j = 2*i; j <= 10000; j += i){
    			count[i] += count[j];
    		}
    	}
    	ll ans = 0;
    	for(int i = 2; i <= 10000; ++i){
    		ans = ans + mobius[i] * NC4(count[i]);
    	}
    	cout << NC4(n) + ans << endl;
    }
            

    //#if !ONLINE_JUDGE
    //    cout << fixed << setprecision(12) << "-------------------------------------------------\n";
    //    cout << double(clock())/CLOCKS_PER_SEC << " seconds" << endl;
    //#endif
    return 0;
}

