#include <bits/stdc++.h>
using namespace std;

class DisjointSetNode
{
public:
    int parent;
    int node_rank;
};

//Path compression
int FindParent(int v, vector<DisjointSetNode> &dset)
{
    if (dset[v].parent != v)
    {
        dset[v].parent = FindParent(dset[v].parent, dset);
    }
    return dset[v].parent;
}

//Union by rank
void UnionNodes(int a, int b, vector<DisjointSetNode> &dset)
{

    int parent_a = FindParent(a, dset);
    int parent_b = FindParent(b, dset);

    if (parent_a == parent_b)
    {
        return;
    }

    //attach smaller rank tree under root of higher rank tree
    if (dset[parent_a].node_rank < dset[parent_b].node_rank)
    {
        dset[parent_a].parent = parent_b;
    }
    else if (dset[parent_a].node_rank > dset[parent_b].node_rank)
    {
        dset[parent_b].parent = parent_a;
    }
    else
    {
        dset[parent_b].parent = parent_a;
        dset[parent_a].node_rank++;
    }
}

int main()
{
    int n;
    cin >> n;

    vector<DisjointSetNode> dset(n + 1);

    for (int i = 1; i <= n; i++)
    {
        dset[i].parent = i;
        dset[i].node_rank = 0;
    }

    int q;
    cin >> q;
    int a, b;

    //merge
    for (int i = 0; i < q; i++)
    {
        cin >> a >> b;
        UnionNodes(a, b, dset);
    }

    //print component leader
    for (int i = 1; i <= n; i++)
    {
        cout << dset[i].parent << " ";
    }
}
