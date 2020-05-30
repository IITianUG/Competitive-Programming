#include <bits/stdc++.h>
using namespace std;

vector<int> computeLPS(string s)
{
    int m = s.length();
    vector<int> lps(m, 0);

    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < m)
    {
        if (s[i] == s[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len > 0)
            {
                len = lps[len - 1];
            }
            else
            {
                //reached empty string and failed to expand
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

vector<int> KMP(string pat, string txt, vector<int> &lps)
{

    vector<int> ans;

    int m = pat.length();
    int n = txt.length();

    int i = 0; //index for txt
    int j = 0; //index for pat

    while (i < n)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == m)
        {
            ans.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < n && pat[j] != txt[i])
        {
            if (j > 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
    return ans;
}

int main()
{
    string txt, pat;
    cin >> txt >> pat;

    vector<int> lps = computeLPS(pat);

    for (int i = 0; i < lps.size(); i++)
    {
        cout << lps[i] << " ";
    }
    cout << endl;

    vector<int> ans = KMP(pat, txt, lps);

    cout << "Pattern found at positions: ";
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
}
