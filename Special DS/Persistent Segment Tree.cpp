#include <bits/stdc++.h>
using namespace std;
#define MAX_N 100000
#define MAX_VER 100000
int A[MAX_N + 1];

struct vertex
{
    vertex *l, *r;
    long long sum;

    vertex(int val)
        : l(NULL), r(NULL), sum(val)
    {
    }

    vertex(vertex *l, vertex *r)
        : l(l), r(r), sum(0)
    {
        if (l)
            sum += l->sum;
        if (r)
            sum += r->sum;
    }
};
// root pointers for all versions
vertex *version[MAX_VER];

vertex *update(vertex *t, int tl, int tr, int pos, int new_val)
{
    if (tl == tr)
        return new vertex(new_val);

    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new vertex(update(t->l, tl, tm, pos, new_val), t->r);
    else
        return new vertex(t->l, update(t->r, tm + 1, tr, pos, new_val));
}

long long get_sum(vertex *t, int tl, int tr, int l, int r)
{
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return t->sum;

    int tm = (tl + tr) / 2;
    return get_sum(t->l, tl, tm, l, min(r, tm)) + get_sum(t->r, tm + 1, tr, max(l, tm + 1), r);
}

vertex *buildSegTree(int tl, int tr)
{
    if (tl == tr)
        return new vertex(A[tl]);

    int tm = (tl + tr) / 2;

    return new vertex(buildSegTree(tl, tm), buildSegTree(tm + 1, tr));
}

int main()
{
    int version_num = 0;

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> A[i];
    }

    version[version_num++] = buildSegTree(1, n);

    int q, choice, l, r, val, v;
    cin >> q;

    while (q--)
    {
        cin >> choice;

        //query range for a version
        if (choice == 1)
        {
            cin >> l >> r >> v;
            if (v >= version_num)
            {
                cout << "Incorrect version" << endl;
                continue;
            }
            cout << get_sum(version[v], 1, n, l, r) << endl;
        }
        //point update to new value
        else if (choice == 2)
        {
            cin >> l >> val;
            version[version_num++] = update(version[version_num - 1], 1, n, l, val);
        }
    }
}
