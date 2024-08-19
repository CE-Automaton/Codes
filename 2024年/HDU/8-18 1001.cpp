#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3e5+5;
int n, k, s, t, a[N], b[N], ans[N], u, v, cnt=1, ca, wa, w[N*2], c[N*2], to[N*2], nxt[N*2], fir[N], vis[N], dis[N], h[N], lst[N], ansm, ansn;
struct qwq {
    int t, d;
    bool operator <(const qwq& A) const {
        return A.d < d;
    }
};
priority_queue <qwq> q;

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}
void addedge(int x, int y, int cb, int wb) {
    to[++cnt]=y, c[cnt]=cb, w[cnt]=wb, nxt[cnt]=fir[x], fir[x]=cnt;
    to[++cnt]=x, c[cnt]=0, w[cnt]=-wb, nxt[cnt]=fir[y], fir[y]=cnt;
}
void dijkstra(int x) {
    for(int i = 1; i <= 2*n+2; ++i)
        dis[i]=inf;
    dis[x]=0;
    q.push(qwq {x, 0});
    while(!q.empty()) {
        qwq it = q.top(); q.pop();
        if(it.d > dis[it.t]) continue;
        for(int y = fir[it.t]; y; y=nxt[y])
            if(c[y] && it.d+w[y]+h[it.t]-h[to[y]] < dis[to[y]]) {
                lst[to[y]]=y;
                dis[to[y]]=w[y]+it.d+h[it.t]-h[to[y]];
                q.push(qwq {to[y], dis[to[y]]});
            }
    }
}
void spfa() {//垃圾BellmanFord远不如SPFA/fn
    queue<int> q;
    h[s] = 0, vis[s]=1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u]=0;
        for(int y = fir[u]; y; y=nxt[y]) {
            int v = to[y];
            if (c[y] && h[v] > h[u] + w[y]) {
                h[v] = h[u] + w[y];
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

signed main() {
	int q = 0;
    read(q);
    while(q--) {
        read(n);
        for(int i = 1; i <= n; ++i)
            read(a[i]);
        int sum = 0;
        for(int i = 1; i <= n; ++i)
            read(b[i]), sum+=b[i];
        for(int i = 1; i <= 2*n+2; ++i)
            h[i]=inf, fir[i]=0, ans[i]=0;
        cnt=1;
        s=2*n+1, t=2*n+2;
        for(int i = 1; i <= n; ++i)
            addedge(s, i+i-1, 1, 0), addedge(i+i-1, i+i, 1, -b[i]), addedge(i+i, t, 1, 0);
        for(int i = 1; i <= n; ++i)
            for(int j = i+1; j <= n; ++j)
                if(a[i] > a[j])
                    addedge(i+i, j+j-1, 1, 0);
        spfa();
        ansm=ansn=0;
        while(1) {
            dijkstra(s);
            if(dis[t] == inf) break;
            int mn = inf;
            for(int i = t; i != s; i=to[lst[i]^1])
                mn=min(mn, c[lst[i]]);
            ansm+=mn;
            for(int i = t; i != s; i=to[lst[i]^1])
                ansn+=mn*w[lst[i]], c[lst[i]]-=mn, c[lst[i]^1]+=mn;
            ans[ansm]=-ansn;
            for(int i = 1; i <= n; ++i)
                h[i]+=dis[i];
        }
        for(int i = 2; i <= n; ++i)
            ans[i]=max(ans[i], ans[i-1]);
        for(int i = 1; i <= n; ++i)
            write(sum-ans[i], ' ');
        putchar('\n');
    }
    return 0;
}