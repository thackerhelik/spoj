/*
if we increment by x say we have a, b, c, d then before it was (a2+b2+c2+d2) not it becomes (a2+b2+c2+d2) + 4*x*x + 2*x*(a+b+c+d) so maintain sum and also square sum in each node along with lazy values
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

struct node{
    long long int squaresum;
    long long int sum;
    long long int lazy;
    long long int setlazy;
};

struct node segtree[4*MAXN];
long long int a[MAXN];

void init(){
    memset(a, false, sizeof(a));
    for(int i = 0; i < 4*MAXN; ++i){
        segtree[i].sum = segtree[i].squaresum = segtree[i].lazy = segtree[i].setlazy = 0;
    }
    return;
}

void build(int node, int be, int en){
    if(be == en){
        segtree[node].sum = a[be];
        segtree[node].squaresum = a[be]*a[be];
        segtree[node].lazy = 0;
        segtree[node].setlazy = 0;
        return;
    }
    int mid = (be + en) >> 1;
    build(2*node, be, mid);
    build(2*node + 1, mid + 1, en);
    segtree[node].sum = segtree[2*node].sum + segtree[2*node + 1].sum;
    segtree[node].squaresum = segtree[2*node].squaresum + segtree[2*node + 1].squaresum;
    segtree[node].lazy = 0;
    segtree[node].setlazy = 0;
    return;
}

long long int query(int node, int be, int en, int l, int r){

    if(be > r || en < l)return 0;

    if(segtree[node].lazy){

        long long int x = segtree[node].lazy;

        segtree[node].squaresum = segtree[node].squaresum + 2LL*x*(segtree[node].sum) + (en - be + 1)*1LL*x*x;
        segtree[node].sum = segtree[node].sum + (en - be + 1)*1LL*x;

        segtree[node].lazy = 0;

        if(be != en){
            segtree[2*node].lazy = x;
            segtree[2*node].lazy = x;
        }

    }

    if(segtree[node].setlazy){

        long long int x = segtree[node].setlazy;

        segtree[node].sum = (en - be + 1)*1LL*x;
        segtree[node].squaresum = (en - be + 1)*1LL*x*x;

        segtree[node].setlazy = 0;

        if(be != en){
            segtree[2*node].setlazy = x;
            segtree[2*node + 1].setlazy = x;
        }

    }

    if(be >= l && en <= r){
        return segtree[node].squaresum;
    }

    int mid = (be + en) >> 1;
    long long int p1 = query(2*node, be, mid, l, r);
    long long int p2 = query(2*node + 1, mid + 1, en, l, r);
    return (p1 + p2);
}

void update(int node, int be, int en, int l, int r, int xx){

    if(be > r || en < l)return;

    if(segtree[node].lazy){

        long long int x = segtree[node].lazy;

        segtree[node].squaresum = segtree[node].squaresum + 2LL*x*(segtree[node].sum) + (en - be + 1)*1LL*x*x;
        segtree[node].sum = segtree[node].sum + (en - be + 1)*1LL*x;

        segtree[node].lazy = 0;

        if(be != en){
            segtree[2*node].lazy = x;
            segtree[2*node].lazy = x;
        }

    }

    if(segtree[node].setlazy){

        long long int x = segtree[node].setlazy;

        segtree[node].sum = (en - be + 1)*1LL*x;
        segtree[node].squaresum = (en - be + 1)*1LL*(segtree[node].sum);

        segtree[node].setlazy = 0;

        if(be != en){
            segtree[2*node].setlazy = x;
            segtree[2*node + 1].setlazy = x;
        }

    }

    if(be >= l && en <= r){
        segtree[node].squaresum = segtree[node].squaresum + 2LL*xx*(segtree[node].sum) + (en - be + 1)*1LL*xx*xx;
        segtree[node].sum = segtree[node].sum + (en - be + 1)*1LL*xx;

        if(be != en){
            segtree[2*node].lazy = xx;
            segtree[2*node + 1].lazy = xx;
        }
        return;
    }

    int mid = (be + en) >> 1;
    update(2*node, be, mid, l, r, xx);
    update(2*node + 1, mid + 1, en, l, r, xx);
    segtree[node].sum = segtree[2*node].sum + segtree[2*node + 1].sum;
    segtree[node].squaresum = segtree[2*node].squaresum + segtree[2*node + 1].squaresum;
    return;
}

void setupdate(int node, int be, int en, int l, int r, int xx){

    if(be > r || en < l)return;

    if(segtree[node].lazy){

        long long int x = segtree[node].lazy;

        segtree[node].squaresum = segtree[node].squaresum + 2LL*x*(segtree[node].sum) + (en - be + 1)*1LL*x*x;
        segtree[node].sum = segtree[node].sum + (en - be + 1)*1LL*x;

        segtree[node].lazy = 0;

        if(be != en){
            segtree[2*node].lazy = x;
            segtree[2*node].lazy = x;
        }

    }

    if(segtree[node].setlazy){

        long long int x = segtree[node].setlazy;

        segtree[node].sum = (en - be + 1)*1LL*x;
        segtree[node].squaresum = (en - be + 1)*1LL*x*x;

        segtree[node].setlazy = 0;

        if(be != en){
            segtree[2*node].setlazy = x;
            segtree[2*node + 1].setlazy = x;
        }

    }

    if(be >= l && en <= r){
        segtree[node].sum = (en - be + 1)*1LL*xx;
        segtree[node].squaresum = (en - be + 1)*1LL*xx*xx;
        if(be != en){
            segtree[2*node].setlazy = xx;
            segtree[2*node + 1].setlazy = xx;
        }
        return;
    }

    int mid = (be + en) >> 1;
    setupdate(2*node, be, mid, l, r, xx);
    setupdate(2*node + 1, mid + 1, en, l, r, xx);
    segtree[node].sum = segtree[2*node].sum + segtree[2*node + 1].sum;
    segtree[node].squaresum = segtree[2*node].squaresum + segtree[2*node + 1].squaresum;
    return;
}

int main(){

    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int te;
    cin >> te;
    for(int t = 1; t <= te; ++t) {

        init();

        cout << "Case " << t << ": " << endl;

        int n, q, st, nd, x, xx;

        cin >> n >> q;

        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        build(1, 1, n);


        while (q--) {
            cin >> x;
            if (x == 2) {
                cin >> st >> nd;
                long long int ans = query(1, 1, n, st, nd);
                cout << ans << endl;
            } else if (x == 1) {
                cin >> st >> nd >> xx;
                update(1, 1, n, st, nd, xx);
            } else {
                cin >> st >> nd >> xx;
                setupdate(1, 1, n, st, nd, xx);
            }
        }

    }

    return 0;
}
