#include <bits/stdc++.h>
using namespace std;
#define MAXN (int)(1e6)
int B = 257;
int M = (1e9) + 9;
long long powers[MAXN];

void calc_pow(int n)
{
    powers[0] = 1;

    for (int i = 1; i < n; i++)
    {
        powers[i] = (powers[i - 1] * B) % M;
    }
}

vector<int> RabinKarp(string txt, string pat)
{
    int n = txt.length();
    int m = pat.length();
    vector<int> ans;

    if (n < m)
    {
        return ans;
    }

    calc_pow(m);

    long long hp = 0;
    long long ht = 0;

    for (int i = 0; i < m; i++)
    {
        hp = (hp * B + pat[i]) % M;
        ht = (ht * B + txt[i]) % M;
    }

    int en = (n - m);
    for (int i = 0; i <= en; i++)
    {
        if (hp == ht)
        {
            //check character by character
            bool done = true;
            for (int j = 0; j < m; j++)
            {
                if (txt[i + j] != pat[j])
                {
                    done = false;
                    break;
                }
            }
            if (done)
            {
                ans.push_back(i);
            }
        }
        if (i < en)
        {
            ht = (ht - (txt[i] * powers[m - 1]) % M + M) % M;
            ht = (ht * B) % M;
            ht = (ht + txt[i + m]) % M;
        }
    }
    return ans;
}

int main()
{

    string txt, pat;
    cin >> txt >> pat;

    vector<int> ans = RabinKarp(txt, pat);

    cout << "Pattern found at indexes: ";
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
}
