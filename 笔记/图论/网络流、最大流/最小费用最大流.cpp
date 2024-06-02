#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e4+5;
int n, m, s, t, u, v, cnt=1, w[N*2], c[N*2], vis[N], dis[N], h[N], lst[N], dd[N], ansm, ansn;
struct qwq {
    int t, d;
    bool operator <(const qwq& A) const {
        return A.d < d;
    }
};
vector <qwq> to[N];
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
void dijkstra(int x) {
    for(int i = 1; i <= n; ++i)
        dis[i]=inf;
    dis[x]=0;
    q.push(qwq {x, 0});
    while(!q.empty()) {
        qwq it = q.top(); q.pop();
        if(it.d > dis[it.t]) continue;
        for(qwq y : to[it.t])
            if(c[y.d] && it.d+w[y.d]+h[it.t]-h[y.t] < dis[y.t]) {
                lst[y.t]=it.t;
                dd[y.t]=y.d;
                dis[y.t]=w[y.d]+it.d+h[it.t]-h[y.t];
                q.push(qwq {y.t, dis[y.t]});
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
        for(qwq y : to[u]) {
            int v = y.t;
            if (c[y.d] && h[v] > h[u] + w[y.d]) {
                h[v] = h[u] + w[y.d];
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

signed main() {
	read(n), read(m), read(s), read(t);
    for(int i = 1; i <= m; ++i)
        read(u), read(v), ++cnt, read(c[cnt]), read(w[cnt]), 
        to[u].push_back(qwq {v, cnt}), ++cnt, w[cnt]=-w[cnt-1], c[cnt]=0, 
        to[v].push_back(qwq {u, cnt});
    for(int i = 1; i <= n; ++i)
        h[i]=inf;
    spfa();
    while(1) {
        dijkstra(s);
        if(dis[t] == inf) break;
        // debug(dis[t], '\n');
        int mn = inf;
        for(int i = t; i != s; i=lst[i])
            mn=min(mn, c[dd[i]]);
        ansm+=mn;
        for(int i = t; i != s; i=lst[i])
            ansn+=mn*w[dd[i]], c[dd[i]]-=mn, c[dd[i]^1]+=mn;
        for(int i = 1; i <= n; ++i)
            h[i]+=dis[i];
    }
    write(ansm, ' '), write(ansn, '\n');
    return 0;
}