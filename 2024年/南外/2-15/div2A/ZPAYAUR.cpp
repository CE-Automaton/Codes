#include <bits/stdc++.h>

using namespace std;

#define MS(a, b) memset(a, b, sizeof(a))
#define REP(a, b, c) for (register int a = b, _n = c; a <= _n; ++a)
#define DREP(a, b, c) for (register int a = b, _n = c; a >= _n; --a)
#define FOR(a, b, c) for (register int a = b, _n = c; a < _n; ++a)
#define EREP(a, b) for (register int a = head[b]; a; a = edge[a].nxt)

inline int rd () {
    int x = 0; bool f = 0; char IO = getchar();
    while ((IO < '0' || IO > '9') && IO != '-') IO = getchar();
    if (IO == '-') IO = getchar(), f = 1;
    while (IO >= '0' && IO <= '9') x = (x << 3) + (x << 1) + (IO ^ 48), IO = getchar();
    return f ? -x : x;
}

const int SIZE = 300005;

int n;
int a[SIZE], l[SIZE], r[SIZE], t[SIZE];

namespace P100 {
    int stk[SIZE], tp; // ´æÓÒ¶Ëµã
    int mi[SIZE], mx[SIZE];
    void solve () {
        t[n + 1] = 0;
        DREP (i, n, 1) {
            if (r[a[i]] == i) {
                stk[++tp] = i;
                mi[tp] = l[a[i]];
                mx[tp] = i;
            }
            mi[tp] = min(mi[tp], l[a[i]]);
            mx[tp] = max(mx[tp], r[a[i]]);
            if (l[a[i]] == i) {
                while (tp && mi[tp] == i) {
                    if (mx[tp] == stk[tp]) {
                        t[i] = 1 + t[stk[tp] + 1];
                        break;
                    } else {
                        --tp;
                        mx[tp] = max(mx[tp], mx[tp + 1]);
                        mi[tp] = min(mi[tp], mi[tp + 1]);
                    }
                }
            }
        }
        long long ans = 0;
        REP (i, 1, n) ans = ans + t[i];
        printf ("%lld\n", ans);
    }
}

void _main () {
    int T = rd();
    while (T--) {
        n = rd();
        REP (i, 1, n) l[i] = 0;
        REP (i, 1, n) {
            a[i] = rd();
            t[i] = 0;
            if (l[a[i]] == 0) l[a[i]] = i;
            r[a[i]] = i;
        }
        //REP (i, 1, n) cout << l[i] << " " << r[i] << endl;
        P100::solve();
    }
}

int main () {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    _main();
    return 0;
}
