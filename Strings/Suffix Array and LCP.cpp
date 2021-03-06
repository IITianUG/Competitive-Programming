#include <bits/stdc++.h>
using namespace std;
#define MAXN (1 << 16)
#define MAXLG 17
int sortIndex[MAXLG][MAXN];

//Time complexity of Suffix Array - O (n*(log n)^2)
//Time complexity of LCP Array - O (n)

struct entry
{
    pair<int, int> suffix;
    int originalIdx;
} L[MAXN];

int cmp(entry x, entry y)
{
    return x.suffix < y.suffix;
}

vector<int> buildSuffixArray(string s)
{
    int n = s.length();

    vector<int> suffixArr;

    if (n == 1)
    {
        suffixArr.push_back(0);
        return suffixArr;
    }

    for (int i = 0; i < n; i++)
    {
        //using ASCII value for ranking
        sortIndex[0][i] = s[i];
    }

    int step = 1;

    for (int cnt = 1; cnt < n; cnt *= 2)
    {
        for (int i = 0; i < n; i++)
        {
            L[i].suffix.first = sortIndex[step - 1][i];
            L[i].suffix.second = -1;

            if (i + cnt < n)
            {
                L[i].suffix.second = sortIndex[step - 1][i + cnt];
            }

            L[i].originalIdx = i;
        }

        sort(L, L + n, cmp);

        sortIndex[step][L[0].originalIdx] = 0;

        for (int i = 1; i < n; i++)
        {
            if (L[i].suffix == L[i - 1].suffix)
            {
                sortIndex[step][L[i].originalIdx] = sortIndex[step][L[i - 1].originalIdx];
            }
            else
            {
                sortIndex[step][L[i].originalIdx] = i;
            }
        }
        step++;
    }

    for (int i = 0; i < n; i++)
    {
        suffixArr.push_back(L[i].originalIdx);
    }

    return suffixArr;
}

vector<int> kasaiLCP(string s, vector<int> sa)
{
    int n = s.size();

    vector<int> lcp(n, 0);
    vector<int> sufinv(n, 0);

    for (int i = 0; i < n; i++)
    {
        sufinv[sa[i]] = i;
    }

    int h = 0;
    for (int i = 0; i < n; i++)
    {
        if (sufinv[i] == 0)
        {
            continue;
        }

        int k = sa[sufinv[i] - 1];

        while (i + h < n && k + h < n && s[i + h] == s[k + h])
        {
            h++;
        }
        lcp[sufinv[i]] = h;

        if (h > 0)
        {
            h--;
        }
    }
    return lcp;
}

int main()
{
    string s;
    cin >> s;

    int n = s.length();

    vector<int> suffixArr = buildSuffixArray(s);
    vector<int> lcp = kasaiLCP(s, suffixArr);

    cout << "Printing Suffix Array: ";
    for (int i = 0; i < n; i++)
    {
        cout << suffixArr[i] << " ";
    }
    cout << endl;

    cout << "Printing LCP Array: ";
    for (int i = 0; i < n; i++)
    {
        cout << lcp[i] << " ";
    }
}
