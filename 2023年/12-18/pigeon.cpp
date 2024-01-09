#include <bits/stdc++.h>
#define inf 10000000
using namespace std;
const int N = 2.5e3 + 5, M = 3e5 + 5;
int n, m, s, t, cnt = 1, fir[N], vis[N], ans, sum[N];
vector <int> too[N];
struct qwq {
	int to, w;
} b[M];
struct bian {
    int u, v, w;
} a[M];

template <typename T>
void read(T& x) {
    x = 0;
    int f = 0;
    char c = getchar();
    while (c < '0' || c > '9') f |= (c == '-'), c = getchar();
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    x = (f ? -x : x);
}
int lne;
char put[105];
template <typename T>
void write(T x, char ch) {
    lne = 0;
    if (x < 0)
        putchar('-'), x = -x;
    do {
        put[++lne] = x % 10, x /= 10;
    } while (x);
    while (lne) putchar(put[lne--] ^ 48);
    putchar(ch);
}

void edge(int x, int y, int ww) {
	b[++cnt]=qwq {y, ww};
	too[x].push_back(cnt);
	b[++cnt]=qwq {x, 0};
	too[y].push_back(cnt);
}
int bfs() {
    queue<int> qwq;
    memset(vis, 0, sizeof vis);
	memset(fir, 0, sizeof fir);
    qwq.push(s);
    vis[s] = 1;
    while (!qwq.empty()) {
        int it = qwq.front();
        qwq.pop();
        for (int y : too[it])
            if (b[y].w > 0 && !vis[b[y].to])
                vis[b[y].to] = vis[it] + 1, qwq.push(b[y].to);
    }
    return vis[t];
}
int dfs(int x, int in) {
    if (x == t)
        return in;
    int out = 0;
    for(int& j = fir[x]; j < too[x].size(); ++j) {
		int i = too[x][j];
        if(b[i].w > 0 && vis[b[i].to] == vis[x] + 1) {
            int qwq = dfs(b[i].to, min(in, b[i].w));
            if (!qwq)
                continue;
            in -= qwq;
            out += qwq;
            b[i].w -= qwq;
            b[i^1].w += qwq;
            if (in == 0)
                break;
        }
	}
    if (out == 0)
        vis[x] = 0;
    return out;
}
int comp(bian A, bian B) { return A.w < B.w; }

signed main() {
    freopen("pigeon.in", "r", stdin);
    freopen("pigeon.out", "w", stdout);
    read(n), read(m);
    s = n + n + 1, t = n + n + 2;
    for (int i = 1; i <= m; ++i) read(a[i].u), read(a[i].v), read(a[i].w), ++a[i].w;
    sort(a + 1, a + 1 + m, comp);
    for (int i = 1; i <= n; ++i) edge(s, i, 1), edge(i + n, t, 1);
    int l = 0;
    for (int i = 1; i <= m;) {
        int j = i;
        while (j <= m && a[j].w == a[i].w) edge(a[j].u, a[j].v + n, 1), ++j;
        while (bfs()) ans += dfs(s, inf);
        // write(ans, '\n');
        for (int j = l + 1; j <= ans; ++j) sum[j] = a[i].w;
        i = j, l = ans;
    }
    for (int i = 1; i <= n; ++i) write(sum[i]-1, ' ');
    return 0;
}
//非but近似正解,都是在残量网络上跑网络流,只不过std是高贵的O(nm)做法