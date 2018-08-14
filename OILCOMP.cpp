/*
Solved using max flow. Konig's theorem extention for weighted general graphs
Learnt basic flow from this https://www.topcoder.com/community/data-science/data-science-tutorials/maximum-flow-section-1/
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 405;
const int inf = 1000000000;

int sum = 0;

int n, w, h;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

map<pair<int,int>, int>m;

int capacity[MAXN][MAXN];
vector<int> adj[MAXN];
bool used[MAXN];

int a[MAXN][MAXN];

int source, sink;

int bfs(){

    int from[MAXN];

    for(int i = 0; i < MAXN; ++i)from[i] = -1;

    queue<int>q;
    q.push(source);
    used[source] = true;
    while(!q.empty()){
        int front = q.front();
        q.pop();
        for(auto it: adj[front]){
            if(!used[it] && capacity[front][it] > 0){
                q.push(it);
                used[it] = true;
                from[it] = front;
                if(it == sink){
                    goto br;
                }
            }
        }
    }

    br:

    int where = sink, path_cap = inf, prev;

    while(from[where] > -1){
        prev = from[where];
        path_cap = min(path_cap, capacity[prev][where]);
        where = prev;
    }

    where = sink;
    while(from[where] > -1){
        prev = from[where];
        capacity[prev][where] -= path_cap;
        capacity[where][prev] += path_cap;
        where = prev;
    }
    if(path_cap == inf)return 0;
    else return path_cap;

}

int max_flow(){
    int flow = 0;

    while(true){
        memset(used, false, sizeof(used));
        int path_capacity = bfs();
        if(path_capacity == 0)break;
        else flow += path_capacity;
    }

    return flow;
}


int isvalid(int x, int y){
    return (x >= 0 && x < h && y >= 0 && y < w);
}

void init(){
    sum = 0;
    m.clear();
    for(int i = 0; i < MAXN; ++i){
        used[i] = false;
        adj[i].clear();
        for(int j = 0; j < MAXN; ++j){
            capacity[i][j] = 0;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int te; 
    cin >> te;
    int ctr = 1;

    while(te--){

        cout << "Case " << ctr++ << ": "; 

        init();

        cin >> w >> h;      
        n = w * h;
        int ct = 1;

        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                m.insert({{i, j}, ct++});
            }
        }

        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                cin >> a[i][j];
                sum += a[i][j];
            }
        }

        source = 0;
        sink = ct;

        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                if(i % 2 == 0 && j % 2 == 0){
                    int idx = m[{i, j}];

                    for(int k = 0; k < 4; ++k){
                        int x = i + dx[k];
                        int y = j + dy[k];
                        if(isvalid(x, y)){
                            int idx2 = m[{x, y}];
                            adj[idx].push_back(idx2);
                            adj[idx2].push_back(idx);
                            capacity[idx][idx2] = inf;
                            capacity[idx2][idx] = 0;
                        }
                    }
                }
                else if(i % 2 != 0 && j % 2 != 0){
                    int idx = m[{i, j}];

                    for(int k = 0; k < 4; ++k){
                        int x = i + dx[k];
                        int y = j + dy[k];
                        if(isvalid(x, y)){
                            int idx2 = m[{x, y}];
                            adj[idx].push_back(idx2);
                            adj[idx2].push_back(idx);
                            capacity[idx][idx2] = inf;
                            capacity[idx2][idx] = 0;
                        }
                    }
                }
            }
        }

        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                int ad = i + j;
                int idx = m[{i, j}];
                if(ad % 2 == 0){
                    //connect to source
                    adj[source].push_back(idx);
                    capacity[source][idx] = a[i][j];
                    capacity[idx][source] = 0;
                }
                else{
                    //connect to sink
                    adj[idx].push_back(sink);
                    capacity[idx][sink] = a[i][j];
                    capacity[sink][idx] = 0;
                }
            }
        }   

        int ans = max_flow();
        cout << sum - ans << endl;
    }

    return 0;
}
