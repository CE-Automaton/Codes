#include <bits/stdc++.h>
#define inf 1000000000000000000LL
#define mod 1000000007
using namespace std;
const int N = 1e5+5;
int n, m, u, v, q, k, id, in[N], out[N];
long long dis[N], w, ansl[N], ansr[N];
struct qwq {
	int t;
	long long w;
	bool operator <(const qwq& A) const {
		return A.w < w;
	}
};
vector <qwq> to[N];
vector <int> nxt[N], ret[N];
priority_queue <qwq> qq;
queue <int> kk;

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
	read(n), read(m), read(q), read(k), read(id);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), read(w), to[u].push_back(qwq{v, w}), to[v].push_back(qwq{u, w});
	for(int o = 1; o <= q; ++o) {
		read(v), read(u);
		for(int i = 1; i <= n; ++i)
			dis[i]=inf, nxt[i].clear(), ret[i].clear(), in[i]=out[i]=0, ansl[i]=ansr[i]=0;
		dis[u]=0;
		qq.push(qwq{u, 0});
		while(!qq.empty()) {
			qwq it = qq.top(); qq.pop();
			if(dis[it.t] > it.w) continue;
			for(qwq y : to[it.t]) 
				if(it.w+y.w < dis[y.t]) {
					dis[y.t]=it.w+y.w;
					qq.push(qwq{y.t, dis[y.t]});
				}
		}
		for(int i = 1; i <= n; ++i)
			for(qwq y : to[i]) 
				if(dis[i]+y.w == dis[y.t])
					nxt[y.t].push_back(i), ret[i].push_back(y.t)/*, cout<<y.t<<"->"<<i<<"\n"*/, ++in[i], ++out[y.t];
		for(int i = 1; i <= n; ++i)
			if(in[i] == 0)
				kk.push(i);
		ansl[v]=1;
		while(!kk.empty()) {
			int it = kk.front(); kk.pop();
			for(int i = 0; i < nxt[it].size(); ++i) {
				int y = nxt[it][i];
				ansl[y]=upd(ansl[y]+ansl[it]);
				--in[y];
				if(in[y] == 0)
					kk.push(y);
			}
		}
		if(k == 0) 
			write(ansl[u], '\n');
		else {
			for(int i = 1; i <= n; ++i)
				if(out[i] == 0)
					kk.push(i);
			ansr[u]=1;
			while(!kk.empty()) {
				int it = kk.front(); kk.pop();
				for(int i = 0; i < ret[it].size(); ++i) {//clear过的vector不能直接用冒号 
					int y = ret[it][i];
					ansr[y]=upd(ansr[y]+ansr[it]);
					--out[y];
					if(out[y] == 0)
						kk.push(y);
				}
			}
			int ans = (ansl[u] == 1 ? 0 : ansl[u]);
			for(int i = 1; i <= n; ++i)
				for(qwq y : to[i]) 
					if(dis[i]+y.w != dis[y.t] && y.t != u)
						ans=upd(ans+1LL*ansl[y.t]*ansr[i]%mod)/*, cout<<y.t<<" "<<i<<"! "<<ansl[y.t]<<" "<<ansr[i]<<"\n"*/;
			write(ans, '\n');
		}
//		for(int i = 1; i <= n; ++i)
//			write(i, ' '), write(dis[i], ' '), write(ansl[i], ' '), write(ansr[i], '\n');
	}
	return 0;
}
