/*
keep 3 values in node which will act as modulo classes along with a lazy value
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

struct node{
    int z, o, t;
    int lazy;
};

struct node segtree[4*MAXN];
int a[MAXN];

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void build(int node, int be, int en){
    if(be == en) {
        segtree[node].z = 1;
        segtree[node].o = 0;
        segtree[node].t = 0;
        segtree[node].lazy = 0;
        return;
    }
    int mid = (be + en) >> 1;
    build(2*node, be, mid);
    build(2*node + 1, mid + 1, en);
    segtree[node].z = segtree[2*node].z + segtree[2*node + 1].z;
    segtree[node].o = segtree[2*node].o + segtree[2*node + 1].o;
    segtree[node].t = segtree[2*node].t + segtree[2*node + 1].t;
}

int query(int node, int be, int en, int l, int r){
    if(be > r || en < l){
        return 0;
    }
    if(segtree[node].lazy % 3){
        segtree[node].lazy %= 3;
        int temp = segtree[node].lazy;
        for(int tet = 0; tet < temp; ++tet){
            int t = segtree[node].o;
            segtree[node].o = segtree[node].z;
            segtree[node].z = segtree[node].t;
            segtree[node].t = t;
        }
        segtree[node].lazy = 0;
        if(be != en){
            segtree[2*node].lazy += temp;
            segtree[2*node + 1].lazy += temp;
            segtree[2*node].lazy %= 3;
            segtree[2*node + 1].lazy %= 3;
        }
    }
    if(be >= l && en <= r){
        return segtree[node].z;
    }
    int mid = (be + en) >> 1;
    int p1 = query(2*node, be, mid, l, r);
    int p2 = query(2*node + 1, mid + 1, en, l, r);
    return (p1 + p2);
}

void update(int node, int be, int en, int l, int r){



    if(segtree[node].lazy % 3){
        segtree[node].lazy %= 3;
        int temp = segtree[node].lazy;
        for(int tet = 0; tet < temp; ++tet){
            int t = segtree[node].o;
            segtree[node].o = segtree[node].z;
            segtree[node].z = segtree[node].t;
            segtree[node].t = t;
        }
        segtree[node].lazy = 0;
        if(be != en){
            segtree[2*node].lazy += temp;
            segtree[2*node + 1].lazy += temp;
            segtree[2*node].lazy %= 3;
            segtree[2*node + 1].lazy %= 3;
        }
    }

    if(be > r || en < l)return;

    if(be >= l && en <= r){
        int t = segtree[node].o;
        segtree[node].o = segtree[node].z;
        segtree[node].z = segtree[node].t;
        segtree[node].t = t;
        if(be != en){
            segtree[2*node].lazy++;
            segtree[2*node + 1].lazy++;
            segtree[2*node].lazy %= 3;
            segtree[2*node + 1].lazy %= 3;
        }
        return;
    }

    int mid = (be + en) >> 1;
    update(2*node, be, mid, l, r);
    update(2*node + 1, mid + 1, en, l, r);
    segtree[node].z = segtree[2*node].z + segtree[2*node + 1].z;
    segtree[node].o = segtree[2*node].o + segtree[2*node + 1].o;
    segtree[node].t = segtree[2*node].t + segtree[2*node + 1].t;
}

int main(){

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, q, x, l, r;
    cin >> n >> q;

    for(int i = 1; i <= n; ++i)a[i] = 0;

    build(1, 1, n);

    for(int i = 0; i < q; ++i){

        cin >> x >> l >> r;
        l++; r++;
        if(l > r)swap(&l, &r);

        if(x == 0){
            update(1, 1, n, l, r);
        }else{
            cout << query(1, 1, n, l, r) << endl;
        }
    }


    return 0;
}
