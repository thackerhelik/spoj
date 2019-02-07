/*
Sort the projects according to deadline.
Then maintain a priority queue so whenever we have to remove some time we can choose the one with highest a value
so that total cost can be minimized.
*/
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define fo(i,n) for(i=0;i<n;++i)

#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define pb push_back

typedef long long int ll;
typedef long double ld;

struct helik{
	ll a, b, d;
	helik(): a(-1), b(-1), d(-1) {}
	helik(int aa, int bb, int dd): a(aa), b(bb), d(dd) {}
	bool operator < (const helik& rhs) const{
		return d < rhs.d;
	}
};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);

    ll t, n, i;
    ll a, b, d;
    cin >> t;
    while(t--){
    	ld cost = 0.00;
    	ll time = 0;
        cin >> n;

    	vector<struct helik>v(n);
    	fo(i, n){
    		cin >> a >> b >> d;
            v[i] = helik(a, b, d);
        }

        priority_queue< pair<ll,ll> >pq;

        sort(all(v));

        fo(i, n){
            time = time + v[i].b;
            pq.push({v[i].a, v[i].b});
            if(time <= v[i].d)continue;
            while(1){
                pair<ll,ll>p = pq.top();
                pq.pop();
                if(time - p.second <= v[i].d){
                    p.second = p.second - (time - v[i].d);
                    cost = cost + 1.0*(time - v[i].d)/p.first;
                    time = v[i].d;
                    pq.push(p);
                    break;
                }
                else{
                    cost = cost + 1.0*(p.second)/p.first;
                    time = time - p.second;
                }
            }
        }
    	cout << fixed << setprecision(2) << cost << endl;
    }        

    return 0;
}

