#include <bits/stdc++.h>
using namespace std;
#define MAX_NODES 100000
#define INF 1000000000
vector<pair<int, int>> g[MAX_NODES + 1];
//Time complexity - O (E log E)

vector<int> Dijkstra(int src, int n)
{
    vector<int> d(n + 1, INF);

    d[src] = 0;
    //min heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push(make_pair(0, src));

    while (!q.empty())
    {
        int v = q.top().second;
        int cur_d = q.top().first;
        q.pop();

        //check if this is the valid pair
        if (cur_d > d[v])
        {
            continue;
        }

        for (int j = 0; j < g[v].size(); j++)
        {
            int to = g[v][j].first;
            int len = g[v][j].second;

            if (d[v] + len < d[to])
            {
                //do not remove old pairs from the queue
                d[to] = d[v] + len;
                q.push(make_pair(d[to], to));
            }
        }
    }
    return d;
}

int main()
{
    int n, m;
    cin >> n >> m;
    int x, y, w;

    for (int i = 0; i < m; i++)
    {
        cin >> x >> y >> w;
        //assuming undirected graph
        g[x].push_back(make_pair(y, w));
        g[y].push_back(make_pair(x, w));
    }

    int src;
    cin >> src;

    vector<int> d = Dijkstra(src, n);

    for (int i = 1; i <= n; i++)
    {
        cout << d[i] << " ";
    }
}
