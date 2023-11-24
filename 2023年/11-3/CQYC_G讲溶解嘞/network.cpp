#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 2e5+5;
int n, a, b, kkk, u, v, l, dis[2][2005][2005], cnt, cntt, tr[4000005], ans, fa[N], ccc[N];
struct qwq {
	int k, d;
	bool operator <(const qwq& A) const {
		return A.d < d;
	}
}zhan[2000005], zhann[2000005];
vector <qwq> to[2][N], hh[2000005];
priority_queue <qwq> q;
unordered_map <int, int> az, azz;
struct edge {
	int u, v, l;
}aa[N], bb[N];

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
void dij(int x) {
	for(int o = 0; o <= 1; ++o) {
		for(int i = 1; i <= n; ++i)
			dis[o][x][i]=inf;
		dis[o][x][x]=0;
		q.push(qwq {x, 0});
		while(!q.empty()) {
			qwq it = q.top();
			q.pop();
			if(it.d > dis[o][x][it.k])
				continue;
			for(qwq y : to[o][it.k]) {
				int ww = max(y.d, it.d);
				if(ww < dis[o][x][y.k])
					dis[o][x][y.k]=ww, q.push(qwq {y.k, ww});
			}
		}
	}
}
int comp(qwq A, qwq B) {
	return A.d < B.d;
}
void add(int x, int w) {
	while(x <= cntt)
		tr[x]+=w, x=x+(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x)
		ret+=tr[x], x=x-(x&(-x));
	return ret;
}
int compp(edge A, edge B) {
	return A.l < B.l;
}
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}

signed main() {
	freopen("network.in", "r", stdin);
	freopen("network.out", "w", stdout);
	read(n), read(a), read(b), read(kkk);
	if(n <= 2000) {
		for(int i = 1; i <= a; ++i)
			read(u), read(v), read(l), to[0][u].push_back(qwq {v, l}), to[0][l].push_back(qwq {u, l});
		for(int i = 1; i <= b; ++i)
			read(u), read(v), read(l), to[1][u].push_back(qwq {v, l}), to[1][l].push_back(qwq {u, l});
		for(int i = 1; i <= n; ++i)
			dij(i);
		for(int i = 1; i <= n; ++i)
			for(int j = i+1; j <= n; ++j) 
				if(dis[0][i][j] != inf) {
					if(az.find(dis[0][i][j]) == az.end()) {
						az[dis[0][i][j]]=++cnt;
						zhan[cnt].d=dis[0][i][j];
						zhan[cnt].k=1;
					}
					else
						++zhan[az[dis[0][i][j]]].k;
				}
		sort(zhan+1, zhan+1+cnt, comp);
		for(int i = 1; i <= cnt; ++i)
			az[zhan[i].d]=i;
		for(int i = 1; i <= n; ++i)
			for(int j = i+1; j <= n; ++j) 
				hh[az[dis[0][i][j]]].push_back(qwq {i, j});
			
		for(int i = 1; i <= n; ++i)
			for(int j = i+1; j <= n; ++j) 
				if(dis[1][i][j] != inf) {
					if(azz.find(dis[1][i][j]) == azz.end()) {
						azz[dis[1][i][j]]=++cntt;
						zhann[cntt].d=dis[1][i][j];
						zhann[cntt].k=1;
					}
					else
						++zhann[az[dis[1][i][j]]].k;
				}
		sort(zhann+1, zhann+1+cntt, comp);
		for(int i = 1; i <= cntt; ++i)
			azz[zhann[i].d]=i, add(i, zhann[i].k);
		ans=inf+inf;
		for(int i = 0, sm = 0; i <= cnt; ++i) {
			sm+=zhan[i].k;
			if(i)
				for(qwq y : hh[i])
					if(dis[1][y.k][y.d] != inf)
						add(azz[dis[1][y.k][y.d]], -1);
			int l = 0, r = cntt, as = -1;
			while(l <= r) {
				int mid = ((l+r)>>1);
				if(ask(mid)+sm >= kkk)
					as=mid, r=mid-1;
				else
					l=mid+1;
			}
			if(as != -1)
				ans=min(ans, zhan[i].d+zhann[as].d);
		}
		write(ans, '\n');
	}
	else {
		for(int i = 1; i <= a; ++i)
			read(aa[i].u), read(aa[i].v), read(aa[i].l);
		for(int i = 1; i <= b; ++i)
			read(bb[i].u), read(bb[i].v), read(bb[i].l);
		sort(aa+1, aa+1+a, compp);
		sort(bb+1, bb+1+b, compp);
		for(int i = 1; i <= n; ++i)
			fa[i]=i, ccc[i]=1;
		for(int i = 1; i <= a; ++i) {
			u=find(aa[i].u), v=find(aa[i].v);
			if(u == v) continue;
			zhan[++cnt]=qwq {ccc[u]*ccc[v], aa[i].l};
			if(ccc[u] < ccc[v])
				swap(u, v);
			fa[v]=u;
			ccc[u]+=ccc[v];
		}
		
		for(int i = 1; i <= n; ++i)
			fa[i]=i, ccc[i]=1;
		for(int i = 1; i <= b; ++i) {
			u=find(bb[i].u), v=find(bb[i].v);
			if(u == v) continue;
			zhann[++cntt]=qwq {ccc[u]*ccc[v], bb[i].l};
			if(ccc[u] < ccc[v])
				swap(u, v);
			fa[v]=u;
			ccc[u]+=ccc[v];
		}
		
		for(int i = 1; i <= cntt; ++i)
			add(i, zhann[i].k);
		for(int i = 0, sm = 0; i <= cnt; ++i) {
			sm+=zhan[i].k;
			int l = 0, r = cntt, as = -1;
			while(l <= r) {
				int mid = ((l+r)>>1);
				if(ask(mid)+sm >= kkk)
					as=mid, r=mid-1;
				else
					l=mid+1;
			}
			if(as != -1)
				ans=min(ans, zhan[i].d+zhann[as].d);
		}
		write(ans, '\n');
	} 
	return 0;
}
