#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000
const int MAXK = log2(MAXN) + 1;
int logTable[MAXN + 1];
int sparseTable[MAXN][MAXK];
int A[MAXN + 1];

void preprocess(int n)
{
    logTable[1] = 0;

    for (int i = 2; i <= MAXN; i++)
    {
        logTable[i] = logTable[i / 2] + 1;
    }

    for (int i = 0; i < n; i++)
    {
        sparseTable[i][0] = A[i];
    }

    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 0; i + (1 << j) <= n; i++)
        {
            sparseTable[i][j] = min(sparseTable[i][j - 1], sparseTable[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int queryMin(int l, int r)
{
    int j = logTable[r - l + 1];

    return min(sparseTable[l][j], sparseTable[r - (1 << j) + 1][j]);
}

int main()
{
    int n;
    cin >> n;

    //0-based indexing
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }

    preprocess(n);

    int q;
    cin >> q;
    int l, r;

    while (q--)
    {
        cin >> l >> r;

        cout << queryMin(l, r) << endl;
    }
}
