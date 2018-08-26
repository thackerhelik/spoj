/*
Maintain a segment tree with 3 values
number of matches
number of open
number of close
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;

char s[MAXN];

struct node{
    int match, open, closed;
};

struct node segtree[4*MAXN];

void init();

void build(int node, int be, int en){
    if(be == en){
        if(s[be] == '('){
            segtree[node].match = 0;
            segtree[node].open = 1;
            segtree[node].closed = 0;
        }
        else{
            segtree[node].match = 0;
            segtree[node].open = 0;
            segtree[node].closed = 1;
        }
        return;
    }
    int mid = (be + en) >> 1;
    build(2*node, be, mid);
    build(2*node + 1, mid + 1, en);
    int match = min(segtree[2*node].open, segtree[2*node + 1].closed);
    segtree[node].match = segtree[2*node].match + segtree[2*node + 1].match + match;
    segtree[node].open = segtree[2*node].open + segtree[2*node + 1].open - match;
    segtree[node].closed = segtree[2*node].closed + segtree[2*node + 1].closed - match;
    return;
}

int query(){
    return segtree[1].match;
}

void update(int node, int be, int en, int pos){
    if(be == en){
        if(s[pos] == '('){
            s[pos] = ')';
            segtree[node].match = 0;
            segtree[node].open = 0;
            segtree[node].closed = 1;
        }
        else{
            s[pos] = '(';
            segtree[node].match = 0;
            segtree[node].open = 1;
            segtree[node].closed = 0;
        }
        return;
    }
    int mid = (be + en) >> 1;
    if(pos <= mid)update(2*node, be, mid, pos);
    else update(2*node + 1, mid + 1, en, pos);
    int match = min(segtree[2*node].open, segtree[2*node + 1].closed);
    segtree[node].match = segtree[2*node].match + segtree[2*node + 1].match + match;
    segtree[node].open = segtree[2*node].open + segtree[2*node + 1].open - match;
    segtree[node].closed = segtree[2*node].closed + segtree[2*node + 1].closed - match;
    return;
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int ct = 10;
    int ctr = 0;
    while(ct--) {

        cout << "Test " << ++ctr << ":" << endl;

        init();
        int n, q, x;
        cin >> n;

        for(int i = 1; i <= n; ++i)cin >> s[i];

        build(1, 1, n);

        cin >> q;
        while (q--) {
            cin >> x;
            if (x == 0) {
                int ans = query();
                cout << (ans << 1 == n ? "YES" : "NO") << endl;
            } else {
                update(1, 1, n, x);
            }
        }
    }
}

void init() {
    for(int i = 0; i < 4*MAXN; ++i){
        segtree[i].match = segtree[i].open = segtree[i].closed = 0;
    }
    return;
}
