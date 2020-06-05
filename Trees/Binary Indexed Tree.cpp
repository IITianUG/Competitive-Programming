#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000
int BIT[MAXN + 1];

int getSum(int idx)
{
    int sum = 0;
    while (idx > 0)
    {
        sum += BIT[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

void update(int idx, int val, int MaxIdx)
{
    while (idx <= MaxIdx)
    {
        BIT[idx] += val;
        idx += (idx & -idx);
    }
}

int readSingle(int idx)
{
    int sum = BIT[idx];
    if (idx > 0)
    {
        int z = idx - (idx & -idx);
        idx--;
        while (idx != z)
        {
            sum -= BIT[idx];
            idx -= (idx & -idx);
        }
    }
    return sum;
}

int setBitNumber(int n)
{
    if (n == 0)
        return 0;

    int msb = 0;
    while (n != 0)
    {
        n = n / 2;
        msb++;
    }

    return (1 << msb);
}

//find largest index with given cumulative frequency
int findIdx(int cumFre, int MaxIdx)
{
    int idx = 0;
    int bitMask = setBitNumber(MaxIdx);

    while (bitMask != 0)
    {
        int tIdx = idx + bitMask;
        bitMask >>= 1;
        if (tIdx > MaxIdx)
        {
            continue;
        }
        if (cumFre >= BIT[tIdx])
        {
            idx = tIdx;
            cumFre -= BIT[tIdx];
        }
    }

    if (cumFre != 0)
    {
        return -1;
    }
    else
    {
        return idx;
    }
}

int main()
{
    int n;
    cin >> n;

    int x;

    for (int i = 1; i <= n; i++)
    {
        cin >> x;
        update(i, x, n);
    }

    for (int i = 1; i <= n; i++)
    {
        cout << readSingle(i) << " ";
    }
    cout << endl;

    int q;
    cin >> q;
    int choice, idx, val;

    while (q--)
    {
        cin >> choice;

        if (choice == 1)
        {
            //get Sum
            cin >> idx;
            cout << getSum(idx) << endl;
        }
        else if (choice == 2)
        {
            //update index
            cin >> idx >> val;
            update(idx, val, n);
        }
        else if (choice == 3)
        {
            //get index for cumulative frequency
            cin >> val;
            cout << findIdx(val, n) << endl;
        }
    }
}
