#include <bits/stdc++.h>
using namespace std;
#define MAX_N 100000
//number of nodes in segment tree is 2*N-1
long long segtree[4 * MAX_N];
long long lazy[4 * MAX_N];

int A[MAX_N + 1];

void updateRange(int node, int st, int en, int l, int r, int val)
{
    if (lazy[node] != 0)
    {
        segtree[node] += (en - st + 1) * lazy[node];
        if (st != en)
        {
            //mark children as lazy
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (st > en or st > r or en < l)
        return;
    if (st >= l and en <= r)
    {
        segtree[node] += (en - st + 1) * val;
        if (st != en)
        {
            lazy[node * 2] += val;
            lazy[node * 2 + 1] += val;
        }
        return;
    }
    int mid = (st + en) / 2;
    updateRange(node * 2, st, mid, l, r, val);
    updateRange(node * 2 + 1, mid + 1, en, l, r, val);
    segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
}

long long queryRange(int node, int st, int en, int l, int r)
{
    if (st > en or st > r or en < l)
        return 0;
    if (lazy[node] != 0)
    {
        segtree[node] += (en - st + 1) * lazy[node];
        if (st != en)
        {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (st >= l and en <= r)
        return segtree[node];
    int mid = (st + en) / 2;
    long long p1 = queryRange(node * 2, st, mid, l, r);
    long long p2 = queryRange(node * 2 + 1, mid + 1, en, l, r);
    return (p1 + p2);
}

void buildSegTree(int node, int st, int en)
{
    if (st == en)
    {
        segtree[node] = A[st];
    }
    else
    {
        int mid = (st + en) / 2;

        buildSegTree(2 * node, st, mid);
        buildSegTree(2 * node + 1, mid + 1, en);

        segtree[node] = segtree[2 * node] + segtree[2 * node + 1];
    }
}

int main()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> A[i];
    }

    //1-based Segment Tree
    buildSegTree(1, 1, n);

    int q, choice, l, r, val;
    cin >> q;

    while (q--)
    {
        cin >> choice;

        //query range
        if (choice == 1)
        {
            cin >> l >> r;
            cout << queryRange(1, 1, n, l, r) << endl;
        }
        //update range
        else if (choice == 2)
        {
            cin >> l >> r >> val;
            updateRange(1, 1, n, l, r, val);
        }
    }
}
