#include <bits/stdc++.h>
using namespace std;
//Worst case space complexity (for function call stack) - O (log n)

int qPartition(vector<int> &arr, int l, int r)
{
    int pivot = arr[r];
    int i = l - 1;

    for (int j = l; j < r; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);
    return i + 1;
}

void quickSort(vector<int> &arr, int l, int r)
{

    while (l < r)
    {
        int idx = qPartition(arr, l, r);

        if (idx - l < r - idx)
        {
            //recursive call for smaller part
            quickSort(arr, l, idx - 1);
            //tail call optimization for larger part
            //quickSort(arr, idx + 1, r)
            l = idx + 1;
        }
        else
        {
            //recursive call for smaller part
            quickSort(arr, idx + 1, r);
            //tail call optimization for larger part
            //quickSort(arr, l, idx - 1)
            r = idx - 1;
        }
    }
}

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    quickSort(arr, 0, n - 1);

    cout << "Printing array sorted using Quicksort\n";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}
