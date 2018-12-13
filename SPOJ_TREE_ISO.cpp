/*
AHU Algorithm in VlogV --> can be improved to V by using radix sort instead of sort and doing something about map (use hashing)
https://www.win.tue.nl/~kverbeek/CPPS/material/.../CPPS-TreeIsomorphism.pptx
this link has the algorithm
my code is bad implementation of the algorithm
first find center of tree
theorem: any tree has exactly 1 or 2 centers
root both the tree at any random point
now find centers of both the trees
3 cases
1) both trees have 1 center
2) both trees have 2 centers
3) one tree has 1 center and other has 2 centers
in case of 3) we say it is not isomorphic (since the number of centers are different)
we have assign_names which is a faster way to assign knuth tuples
at every level we have to sort the knuth tuples and then assign it to node
if the tuples at both the roots are same then we have isomorphic trees
so for case 1) we just need to root the trees at their centers
for case 2) we root tree1 at center1 and tree2 at center1 and check --> if true then isomorphic
else we root tree1 at center2 and tree2 at center1 and check --> if true then isomorphic
else not isomorphic
*/
#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
using namespace std;

map<vector<int>,int>hm;
int c;
vector<int>adj[100005];
vector<int>adj2[100005];
int depth1[100005];
int depth2[100005];
int depth3[100005];
int n;

void init(){
	for(int i = 0; i <= n; ++i){
		adj[i].clear();
		adj2[i].clear();
		depth1[i] = depth2[i] = depth3[i] = 0;
	}
	hm.clear();
}

int assign_names(int node, int parent){
	if(sz(adj[node]) == 1)
		return 0;
	vector<int>A;
	for(auto it: adj[node]){
		if(it != parent){
			A.push_back(assign_names(it, node));
		}
	}
	sort(A.begin(), A.end());
	if(!hm.count(A))
		hm.insert({A, ++c});
	return hm[A];
}

int assign_names2(int node, int parent){
	if(sz(adj2[node]) == 1)
		return 0;
	vector<int>A;
	for(auto it: adj2[node]){
		if(it != parent){
			A.push_back(assign_names2(it, node));
		}
	}
	sort(A.begin(), A.end());
	if(!hm.count(A))
		hm.insert({A, ++c});
	return hm[A];	
}

void dfs(int node, int parent, int iter, int d){
	if(iter == 0)
		depth1[node] = d;
	else if(iter == 1)
		depth2[node] = d;
	else 
		depth3[node] = d;
	for(auto it: adj[node]){
		if(it != parent){
			dfs(it, node, iter, d + 1);
		}
	}
}

void dfs2(int node, int parent, int iter, int d){
	if(iter == 0)
		depth1[node] = d;
	else if(iter == 1)
		depth2[node] = d;
	else 
		depth3[node] = d;
	for(auto it: adj2[node]){
		if(it != parent){
			dfs2(it, node, iter, d + 1);
		}
	}	
}

vector<int>find_center(int root, int tree){
	vector<int>ret;
	if(tree == 0){
		depth1[root] = 0;
		dfs(root, -1, 0, 0);
		int mx1 = -1;
		int ender = -1;
		for(int i = 1; i <= n; ++i){
			if(depth1[i] > mx1){
				mx1 = depth1[i];
				ender = i;
			}
		}
		depth2[ender] = 0;
		dfs(ender, -1, 1, 0);
		int mx2 = -1;
		int ender2 = -1;
		for(int i = 1; i <= n; ++i){
			if(depth2[i] > mx2){
				mx2 = depth2[i];
				ender2 = i;
			}
		}
		int diameter = mx2;
		depth3[ender2] = 0;
		dfs(ender2, -1, 2, 0);
		if(diameter % 2 == 0){
			for(int i = 1; i <= n; ++i){
				if(depth2[i] == diameter/2 && depth3[i] == diameter/2){
					ret.push_back(i);
				}
			}
		}
		else{
			for(int i = 1; i <= n; ++i){
				if(depth2[i] == diameter/2 && depth3[i] == diameter/2 + 1)
					ret.push_back(i);
				if(depth2[i] == diameter/2 + 1 && depth3[i] == diameter/2)
					ret.push_back(i);
			}
		}
	}
	else{
		depth1[root] = 0;
		dfs2(root, -1, 0, 0);
		int mx1 = -1;
		int ender = -1;

		for(int i = 1; i <= n; ++i){
			if(depth1[i] > mx1){
				mx1 = depth1[i];
				ender = i;
			}
		}
		depth2[ender] = 0;
		dfs2(ender, -1, 1, 0);
		int mx2 = -1;
		int ender2 = -1;
		for(int i = 1; i <= n; ++i){
			if(depth2[i] > mx2){
				mx2 = depth2[i];
				ender2 = i;
			}
		}
		int diameter = mx2;
		depth3[ender2] = 0;
		dfs2(ender2, -1, 2, 0);
		if(diameter % 2 == 0){
			for(int i = 1; i <= n; ++i){
				if(depth2[i] == diameter/2 && depth3[i] == diameter/2){
					ret.push_back(i);
				}
			}
		}
		else{
			for(int i = 1; i <= n; ++i){
				if(depth2[i] == diameter/2 && depth3[i] == diameter/2 + 1)
					ret.push_back(i);
				if(depth2[i] == diameter/2 + 1 && depth3[i] == diameter/2)
					ret.push_back(i);
			}
		}	
	}
	return ret;
}

bool tree_isomorphism(int r, int s){

	vector<int>A = find_center(r, 0);
	vector<int>B = find_center(s, 1);

	if(sz(A) == 1 && sz(B) == 1){
		int a = assign_names(A[0], -1);
		int b = assign_names2(B[0], -1);
		if(a == b)return true;
	}
	else if(sz(A) == 2 && sz(B) == 2){
		int a = assign_names(A[0], -1);
		int b = assign_names2(B[0], -1);
		if(a == b)return true;
		a = assign_names(A[1], -1);
		b = assign_names2(B[0], -1);
		if(a == b){
			return true;
		}
	}

	return false;

}

int main(){

	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int t;
	cin >> t;
	while(t--){
		if(n)init();
		int x, y;
		int root1 = -1, root2 = -1;
		cin >> n;
		for(int i = 0; i < n - 1; ++i){
			cin >> x >> y;
			if(root1 == -1)root1 = x;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		for(int i = 0; i < n - 1; ++i){
			cin >> x >> y;
			if(root2 == -1)root2 = x;
			adj2[x].push_back(y);
			adj2[y].push_back(x);	
		}

		if(tree_isomorphism(root1, root2))cout << "YES" << endl;
		else cout << "NO" << endl;
	}

	return 0;
}
