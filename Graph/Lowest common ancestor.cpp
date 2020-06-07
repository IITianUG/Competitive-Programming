#include <bits/stdc++.h>
using namespace std;
//Binary Lifting
#define MAXN 100000
const int MAXK = ceil(log2(MAXN)) + 1;
int timer;
int tin[MAXN + 1];
int tout[MAXN + 1];
int up[MAXN + 1][MAXK];
vector<int> g[MAXN + 1];
int l;
//Time Complexity: O(N log N) preprocessing, O(log N) query

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;

    for (int i = 1; i <= l; i++)
    {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    for (int i = 0; i < g[v].size(); i++)
    {
        int u = g[v][i];
        if (u != p)
        {
            dfs(u, v);
        }
    }
    tout[v] = ++timer;
}

bool isAncestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (isAncestor(u, v))
    {
        return u;
    }
    if (isAncestor(v, u))
    {
        return v;
    }

    for (int i = l; i >= 0; i--)
    {
        if (!isAncestor(up[u][i], v))
        {
            u = up[u][i];
        }
    }
    return up[u][0];
}

void preprocess(int root, int n)
{
    timer = 0;
    l = ceil(log2(n));
    dfs(root, root);
}

int main()
{

    int n, m;
    cin >> n >> m;

    int x, y;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        //assuming undirected graph
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int root;
    cin >> root;

    preprocess(root, n);

    int q;
    cin >> q;

    while (q--)
    {
        cin >> x >> y;
        cout << lca(x, y) << endl;
    }
}
