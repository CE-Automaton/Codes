#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3e5+5;
int t, n, m, u, v, ans, zhan[N], pd[N], in[N], inn[N], dfn[N], low[N], sum[N], ll[N], pp, op, nr[N], yyn[N], bbb[N];
LL w, dis[N], disn[N];
struct qwq {
	int x; LL ww;
	bool operator <(const qwq& A) const {
		return A.ww < ww;
	}
};
struct tt {
	int t, d; LL w;
};
vector <tt> to[N], az[N]/*最短路图*/, ha[N]/*1到n的最短路建图*/, kk[N];
priority_queue<qwq> q;
queue <int> aaa;

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
void tarjan(int x, int fa) {
	dfn[x]=low[x]=++op;
	for(int i = 0; i < kk[x].size(); ++i) {
		int y = kk[x][i].t;
		if(y == fa) continue;
		if(!dfn[y]) {
			tarjan(y, x);
			low[x]=min(low[x], low[y]);
			if(low[y] > dfn[x])
				pd[kk[x][i].d]=1;
		}
		else
			low[x]=min(low[x], dfn[y]);
	}
}
void sol() {
	read(n), read(m);
	bbb[0]=0;
	for(int i = 1; i <= n; ++i)
		to[i].clear(), az[i].clear(), ha[i].clear(), kk[i].clear(),
		dis[i]=inf, disn[i]=inf, dfn[i]=low[i]=in[i]=inn[i]=sum[i]=nr[i]=0, yyn[i]=1;
	op=0;
	for(int i = 1; i <= m; ++i)
		read(u), read(v), read(w), to[u].push_back(tt {v, i, w}),
		to[v].push_back(tt {u, i, w}), pd[i]=bbb[i]=0;
	dis[1]=0;
	q.push(qwq {1, 0});
	while(!q.empty()) {
		qwq it = q.top(); q.pop();
		if(it.ww > dis[it.x]) continue;
		for(int i = 0; i < to[it.x].size(); ++i) {
			int y = to[it.x][i].t;
			if(dis[y] > it.ww+to[it.x][i].w)
				dis[y]=it.ww+to[it.x][i].w, q.push(qwq {y, dis[y]});
		}
	}
	disn[n]=0;
	q.push(qwq {n, 0});
	while(!q.empty()) {
		qwq it = q.top(); q.pop();
		if(it.ww > disn[it.x]) continue;
		for(int i = 0; i < to[it.x].size(); ++i) {
			int y = to[it.x][i].t;
			if(disn[y] > it.ww+to[it.x][i].w)
				disn[y]=it.ww+to[it.x][i].w, q.push(qwq {y, disn[y]});
		}
	}
	// debug(dis[n], disn[1], "!?\n");
	for(int x = 1; x <= n; ++x) 
		for(int i = 0; i < to[x].size(); ++i) {
			int y = to[x][i].t;
			if(dis[x]+to[x][i].w == dis[y])
				az[x].push_back(tt {y, to[x][i].d, to[x][i].w}), ++in[y];
			if(dis[x]+disn[y]+to[x][i].w == dis[n]) 
				ha[x].push_back(tt {y, to[x][i].d, to[x][i].w}), ++inn[y],
				kk[x].push_back(tt {y, to[x][i].d, to[x][i].w}),
				kk[y].push_back(tt {x, to[x][i].d, to[x][i].w});
		}
	tarjan(1, 0);
	pp=0;
	aaa.push(1);
	while(!aaa.empty()) {
		int it = aaa.front(); aaa.pop();
		for(int i = 0; i < ha[it].size(); ++i) {
			int y = ha[it][i].t;
			if(pd[ha[it][i].d])
				ll[++pp]=ha[it][i].d, sum[y]=pp+1;
			else
				sum[y]=sum[it];
			--inn[y];
			if(!inn[y]) 
				aaa.push(y);
		}
	}
	sum[0]=0x3f3f3f3f;
	sum[1]=1;
	aaa.push(1);
	while(!aaa.empty()) {
		int it = aaa.front(); aaa.pop();
		if(dfn[it])
			nr[it]=yyn[it]=it;
		for(int i = 0; i < az[it].size(); ++i) {
			int y = az[it][i].t;
			--in[y];
			if(sum[nr[it]] < sum[nr[y]])
				nr[y]=nr[it];
			if(sum[yyn[it]] > sum[yyn[y]])
				yyn[y]=yyn[it];
			yyn[y]=max(yyn[it], yyn[y]);
			if(!in[y]) 
				aaa.push(y);
		}
	}
	ans=0;
	for(int x = 1; x <= n; ++x) 
		for(int i = 0; i < to[x].size(); ++i) {
			int y = to[x][i].t;
			if(dis[x]+disn[y]+to[x][i].w == dis[n]+1) {
				// debug(x, y, sum[nr[x]], sum[nr[y]], sum[yyn[x]], sum[yyn[y]], "!?!?!?!?!?!?\n");
				if(abs(sum[nr[x]]-sum[nr[y]])) {
					if(sum[nr[x]] > sum[nr[y]])
						++bbb[sum[nr[y]]], --bbb[sum[nr[x]]];
					else
						++bbb[sum[nr[x]]], --bbb[sum[nr[y]]];
				}
				if(abs(sum[nr[x]]-sum[yyn[y]])) {
					if(sum[nr[x]] > sum[yyn[y]])
						++bbb[sum[yyn[y]]], --bbb[sum[nr[x]]];
					else
						++bbb[sum[nr[x]]], --bbb[sum[yyn[y]]];
				}
				if(abs(sum[yyn[x]]-sum[nr[y]])) {
					if(sum[yyn[x]] > sum[nr[y]])
						++bbb[sum[nr[y]]], --bbb[sum[yyn[x]]];
					else
						++bbb[sum[yyn[x]]], --bbb[sum[nr[y]]];
				}
				if(abs(sum[yyn[x]]-sum[yyn[y]])) {
					if(sum[yyn[x]] > sum[yyn[y]])
						++bbb[sum[yyn[y]]], --bbb[sum[yyn[x]]];
					else
						++bbb[sum[yyn[x]]], --bbb[sum[yyn[y]]];
				}
			}
		}
	// for(int i = 1; i <= pp; ++i) 
	// 	write(ll[i], ' ');
	// putchar('\n');
	for(int i = 1; i <= pp; ++i) {
		bbb[i]+=bbb[i-1];
		if(bbb[i])
			zhan[++ans]=ll[i];
	}
	// write(n, ' '), write(m ,'!'), 
	write(ans), putchar('\n');
	if(ans) {
		sort(zhan+1, zhan+1+ans);
		for(int i = 1; i <= ans; ++i)
			write(zhan[i]), putchar(i == ans ? '\n' : ' ')/*。。。蓝的盆*/;
	}
}

signed main() {
	File("vacation");
	read(t);
	while(t--)
		sol();
	return 0;
}
