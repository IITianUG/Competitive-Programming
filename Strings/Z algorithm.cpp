#include <bits/stdc++.h>
using namespace std;
//Time Complexity - O(n)

vector<int> z_function(string s)
{
    int n = s.length();

    vector<int> z(n, 0);

    int l = 0, r = 0;

    for (int i = 1; i < n; i++)
    {
        //within boundaries of currently known string
        if (i <= r)
        {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            z[i]++;
        }

        //boundary changed
        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main()
{
    string txt, pat;
    cin >> txt >> pat;

    vector<int> z = z_function(pat + '$' + txt);
    vector<int> ans;

    for (int i = 0; i < txt.length(); i++)
    {
        int val = z[i + pat.length() + 1];
        if (val == pat.length())
        {
            ans.push_back(i);
        }
    }

    cout << "Pattern found at positions: ";
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
}
