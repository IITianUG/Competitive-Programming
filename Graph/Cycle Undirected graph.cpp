#include<bits/stdc++.h>
using namespace std;
//cycle in undirected graph
vector<vector<int>> adj;
vector<int> color;
vector<int> parent;
int cycle_start, cycle_end;

bool Dfs(int v, int par) {
    color[v]=1;

    for (int u: adj[v]) {
        //skip edge to parent
        if (u==par) {
            continue;
        }
        if (color[u]==0) {
            parent[u]=v;
            if (Dfs(u, parent[u])) {
                return true;
            }
        }
        else if (color[u]==1) {
            //found cycle
            cycle_start=u;
            cycle_end=v;
            return true;
        }
    }

    color[v]=2;
    return false;
}

vector<int> FindCycle(int n) {
    color.resize(n+1, 0);
    parent.resize(n+1, -1);
    cycle_start=-1;

    for (int i=1;i<=n;i++) {
        if (color[i]==0 && Dfs(i, parent[i])) {
            break;
        }
    }

    vector<int> cycle;

    if (cycle_start==-1) {
        return cycle;
    }

    cycle.push_back(cycle_start);

    for (int v = cycle_end;v!=cycle_start;v=parent[v]) {
        cycle.push_back(v);
    }
    cycle.push_back(cycle_start);
    reverse(cycle.begin(), cycle.end());

    return cycle;
}

int main() {
    int n;
    cin>>n;

    adj.resize(n+1);

    int m;
    cin>>m;
    int x, y;

    for (int i=0;i<m;i++) {
        cin>>x>>y;
        //undirected
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> cycle = FindCycle(n);

    if (cycle.size()==0) {
        cout<<"No cycle"<<endl;
    }
    else {
        cout<<"Cycle exists "<<endl;
        for (int i=0;i<cycle.size();i++) {
            cout<<cycle[i]<<" ";
        }
        cout<<endl;
    }
}
