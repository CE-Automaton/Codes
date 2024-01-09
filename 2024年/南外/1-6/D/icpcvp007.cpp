#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#define N 250001
#define M 480
#define mod 998244353
using namespace std;
const int inf = (int)(1e9);
int read() {
    char c = 0;
    int sum = 0;

    while (c < '0' || c > '9')
        c = getchar();

    while ('0' <= c && c <= '9')
        sum = sum * 10 + c - '0', c = getchar();

    return sum;
}
void Adder(int &x, int d) {
    x += d;

    if (x >= mod)
        x -= mod;

    return;
}
void Adder2(int &x, int d) {
    x += d;

    if (x < 0)
        x += mod;

    return;
}
int MD(int x) {
    return x >= mod ? x - mod : x;
}
int MD2(int x) {
    return x < 0 ? x + mod : x;
}
int n, q, lengths, lengs, lengs2, maxn, szt, ans, block[N + 1], a[N + 1], s[N + 1], DP[N + 1], DP2[N + 1],
    fa[N + 1], depth[N + 1], depths[N + 1], cnt[N + 1], L[N + 1], R[N + 1], sl[N + 1], sr[N + 1], delta[N + 1],
    F[N + 1], dp[M + 1][N + 1], nt[N + 1], nt2[N + 1], hs[N + 1], top[N + 1], sz[N + 1], hs2[N + 1], top2[N + 1],
    sz2[N + 1], dfn[N + 1], rev[N + 1], dfn2[N + 1], rev2[N + 1], nts[N + 1], nts2[N + 1], dst[N + 1],
    dst2[N + 1], tr[N + 1], S[N + 1], num[N + 1], num2[N + 1];
vector<int>E[N + 1];
vector<int>E2[N + 1];
int find(int x, int d) {
    while (dst[x] <= d)
        x = nts[x];

    return rev[num[x] - d];
}
int find2(int x, int d) {
    while (dst2[x] <= d)
        x = nts2[x];

    return rev2[num2[x] - d];
}
int calc(int x, int d) {
    if (tr[x] <= d)
        return S[x];

    int l = find(x, min(depth[d], depths[x])), r = find2(x, min(depth[d], depths[x])),
        rst = MD2(MD2(DP2[x] - DP2[nt2[r]]) - MD2(DP[x] - DP[nt[l]]));

    if (d < l)
        Adder2(rst, -MD2(s[r] - s[l - 1]));
    else if (d < r)
        Adder2(rst, -MD2(s[r] - s[d]));

    return 1ll * rst * rst % mod;
}
int query(int l, int r, int d) {
    int res = 0;

    if (block[r] - block[l] <= 1) {
        for (int i = l; i <= r; ++i)
            Adder(res, calc(i, d));
    } else {
        for (int i = l; i <= min(block[l]*szt, n); ++i)
            Adder(res, calc(i, d));

        for (int i = block[l] + 1; i <= block[r] - 1; ++i)
            Adder(res, dp[i][d]);

        for (int i = (block[r] - 1) * szt + 1; i <= r; ++i)
            Adder(res, calc(i, d));
    }

    return res;
}
void dfs(int x) {
    sz[x] = 1;

    for (int i = 0; i < E[x].size(); ++i) {
        dfs(E[x][i]), sz[x] += sz[E[x][i]];

        if (sz[E[x][i]] > sz[hs[x]])
            hs[x] = E[x][i];
    }

    return;
}
void dfs2(int x) {
    dfn[x] = ++lengs, rev[dfn[x]] = x;

    if (hs[x])
        top[hs[x]] = top[x], dfs2(hs[x]);

    for (int i = 0; i < E[x].size(); ++i)
        if (E[x][i] != hs[x])
            top[E[x][i]] = E[x][i], dfs2(E[x][i]);

    return;
}
void dfs3(int x) {
    sz2[x] = 1;

    for (int i = 0; i < E2[x].size(); ++i) {
        dfs3(E2[x][i]), sz2[x] += sz2[E2[x][i]];

        if (sz2[E2[x][i]] > sz2[hs2[x]])
            hs2[x] = E2[x][i];
    }

    return;
}
void dfs4(int x) {
    dfn2[x] = ++lengs2, rev2[dfn2[x]] = x;

    if (hs2[x])
        top2[hs2[x]] = top2[x], dfs4(hs2[x]);

    for (int i = 0; i < E2[x].size(); ++i)
        if (E2[x][i] != hs2[x])
            top2[E2[x][i]] = E2[x][i], dfs4(E2[x][i]);

    return;
}
int main() {
    int l, r, pv;
    n = read(), q = read(), szt = sqrt(n), depth[1] = 1;

    while ((n - 1) / szt + 1 > M)
        szt++;

    for (int i = 1; i <= n; ++i)
        block[i] = (i - 1) / szt + 1;

    for (int i = 1; i <= n; ++i)
        a[i] = read(), s[i] = MD(s[i - 1] + a[i]), R[i] = -1;

    depths[1] = depth[1] = 1;

    for (int i = 2; i <= n; ++i) {
        fa[i] = read(), depths[i] = depth[i] = depth[fa[i]] + 1, R[fa[i]] = i;

        if (!L[fa[i]])
            L[fa[i]] = i;
    }

    for (int i = n; i >= 2; --i)
        depths[fa[i]] = max(depths[fa[i]], depths[i]);

    maxn = depth[n];

    for (int i = 1; i <= n; ++i) {
        sr[depth[i]] = i;

        if (!sl[depth[i]])
            sl[depth[i]] = i;
    }

    for (int i = 1; i <= maxn; ++i)
        if (block[sl[i]] + 1 <= block[sr[i]] - 1) {
            for (int j = block[sl[i]] + 1; j <= block[sr[i]] - 1; ++j) {
                for (int k = 1; k <= n; ++k)
                    F[k] = 0;

                for (int k = (j - 1) * szt + 1; k <= min(j * szt, n); ++k)
                    F[k] = k, delta[k] = 0;

                for (int k = min(j * szt, n) + 1; k <= n; ++k)
                    F[k] = F[fa[k]];

                for (int k = (j - 1) * szt + 1; k <= n; ++k) {
                    if (F[k])
                        dp[j][k] = MD(dp[j][k - 1] + (2ll * delta[F[k]] + a[k]) * a[k] % mod), Adder(delta[F[k]], a[k]);
                    else
                        dp[j][k] = dp[j][k - 1];
                }
            }
        }

    pv = 0;

    for (int i = n; i >= 1; --i) {
        if (depth[i] != depth[i + 1])
            pv = 0;

        if (L[i] <= R[i])
            pv = L[i];

        nt[i] = pv;
    }

    pv = 0;

    for (int i = 1; i <= n; ++i) {
        if (depth[i] != depth[i - 1])
            pv = 0;

        if (L[i] <= R[i])
            pv = R[i];

        nt2[i] = pv;
    }

    for (int i = n; i >= 1; --i)
        DP[i] = MD(DP[nt[i]] + s[i - 1]), DP2[i] = MD(DP2[nt2[i]] + s[i]);

    for (int i = 1; i <= n; ++i) {
        if (nt[i])
            E[nt[i]].push_back(i);

        if (nt2[i])
            E2[nt2[i]].push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        if (!nt[i])
            dfs(i), top[i] = i, dfs2(i);

        if (!nt2[i])
            dfs3(i), top2[i] = i, dfs4(i);
    }

    for (int i = 1; i <= n; ++i)
        nts[i] = nt[top[i]], nts2[i] = nt2[top2[i]], num[i] = dfn[i] + depth[i], num2[i] = dfn2[i] + depth[i];

    for (int i = 1; i <= n; ++i) {
        if (nts[i])
            dst[i] = depth[nts[i]];
        else
            dst[i] = inf;

        if (nts2[i])
            dst2[i] = depth[nts2[i]];
        else
            dst2[i] = inf;
    }

    for (int i = n; i >= 1; --i) {
        tr[i] = i;

        for (int j = L[i]; j <= R[i]; ++j)
            tr[i] = max(tr[i], tr[j]);

        S[i] = a[i];

        for (int j = L[i]; j <= R[i]; ++j)
            Adder(S[i], S[j]);
    }

    for (int i = 1; i <= n; ++i)
        S[i] = 1ll * S[i] * S[i] % mod;

    while (q--) {
        l = read()^ans, r = read()^ans, ans = 0;

        if (l <= min(sr[depth[l]], r))
            ans += query(l, min(sr[depth[l]], r), r);

        if (depth[l] != maxn) {
            if (!nt[l] && sl[depth[l] + 1] <= min(sr[depth[l] + 1], r))
                Adder(ans, query(sl[depth[l] + 1], min(sr[depth[l] + 1], r), r));
            else if (sl[depth[l] + 1] <= min(nt[l] - 1, r))
                Adder(ans, query(sl[depth[l] + 1], min(nt[l] - 1, r), r));
        }

        printf("%d\n", ans);
    }

    return 0;
}
