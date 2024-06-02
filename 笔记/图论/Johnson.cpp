#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, m, s, u, v, w[N*2], dis[N], h[N];
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
            if(it.d+w[y.d]+h[it.t]-h[y.t] < dis[y.t]) {
                dis[y.t]=w[y.d]+it.d+h[it.t]-h[y.t];
                q.push(qwq {y.t, dis[y.t]});
            }
    }
}

signed main() {
	read(n), read(m)/*, read(s)*/;
    for(int i = 1; i <= m; ++i)
        read(u), read(v), read(w[i]), w[i+m]=w[i], 
        to[u].push_back(qwq {v, i})/*, 
        to[v].push_back(qwq {u, i+m})*/;
    for(int i = 1; i <= n; ++i)
        to[0].push_back(qwq {i, 0}), dis[i]=inf;
    for(int i = 1; i <= n; ++i)
        for(int j = 0; j <= n; ++j)
            for(qwq y : to[j])
                if(h[j]+w[y.d] < h[y.t]) {
                    if(i == n) {
                        puts("-1");
                        return 0;
                    }
                    h[y.t]=h[j]+w[y.d];
                }
    for(s = 1; s <= n; ++s) {
        dijkstra(s);
        LL ans = 0;
        for(int i = 1; i <= n; ++i)
            ans+=1LL*i*(dis[i] == inf ? inf-7 : dis[i]-h[s]+h[i]);
        write(ans, '\n');
    }
    return 0;
}