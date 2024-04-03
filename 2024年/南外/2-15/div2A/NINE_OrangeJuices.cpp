#include <bits/stdc++.h>
#define ll long long
#define MAXN 300010
#define Rand (1LL * (1LL << 10) * rand() + rand())
using namespace std;
int n, T;
ll ans, A[MAXN], sum;
map<ll, int> mp;
vector<int> G[MAXN];
void Rd(int &res) {
    res = 0;
    char ch = getchar();
    while ('0' > ch || ch > '9') ch = getchar();
    while ('0' <= ch && ch <= '9') res = (res << 3) + (res << 1) + (ch - '0'), ch = getchar();
}
int main() {
    srand(time(NULL));
    Rd(T);
    while (T--) {
        Rd(n);
        mp.clear();
        for (int i = 1; i <= n; i++) G[i].clear();
        ans = sum = 0;
        for (int x, i = 1; i <= n; i++) {
            Rd(x);
            G[x].push_back(i);
        }
        for (int i = 1; i <= n; i++) {
            if (G[i].empty())
                continue;
            ll res = 0;
            const int sz = G[i].size();
            for (int j = 0; j < sz - 1; j++) A[G[i][j]] = Rand, res ^= A[G[i][j]];
            A[G[i][sz - 1]] = res;
        }
        mp[0] = 1;
        for (int i = 1; i <= n; i++) {
            sum ^= A[i];
            ans += mp[sum]++;
        }
        printf("%lld\n", ans);
    }
    return 0;
}

