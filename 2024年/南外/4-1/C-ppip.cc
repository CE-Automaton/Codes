#include <bits/stdc++.h>
using namespace std;
int n, a[55];
long long solve(vector<int> v)
{
    int m{v.size()};
    if (!m)
        return 1;
    bool ok[55][55]{};
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (min(a[i], a[j]) < a[v[0]] && max(a[i], a[j]) > a[v[0]])
            {
                int l = upper_bound(v.begin(), v.end(), i) - v.begin();
                int r = lower_bound(v.begin(), v.end(), j) - v.begin() - 1;
                if (l <= r)
                    ok[l + 1][r + 1] = 1;
            }
    long long dp[55]{};
    dp[0] = 1;
    for (int i = 1; i <= m; ++i)
    {
        dp[i] = dp[i - 1] << 1;
        for (int j = i; j; --j)
            dp[i] |= dp[j - 1] * ok[j][i];
    }
    return dp[m];
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    int mx = *max_element(a + 1, a + n + 1), mn = *min_element(a + 1, a + n + 1);
    int res = 0, l = 0, r = 0;
    for (int i = 1; i <= n; ++i)
    {
        res += (i == 1 || i == n || a[i] == mn || a[i] == mx);
        if (a[i] == mn || a[i] == mx)
        {
            if (!l)
                l = i;
            r = i;
        }
    }
    vector<int> v;
    for (int i = 2; i <= l; ++i)
        if (a[i] == a[1])
            v.push_back(i);
    auto A = solve(v);
    v.clear();
    for (int i = r; i < n; ++i)
        if (a[i] == a[n])
            v.push_back(i);
    auto B = solve(v);
    long long C{0};
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= i; ++j)
            C |= (A >> j & B >> i - j & 1) << i;
    for (int i = 0; i <= n; ++i)
        if (C >> i & 1)
            cout << i + res << " ";
}