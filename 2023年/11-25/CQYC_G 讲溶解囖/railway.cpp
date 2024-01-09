#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 2e5+6;
int n, m, s[N], c, t, in[N], dis[N], disn[N], cnt[N], ooo[N], nmb;
long long ans[N];
struct qwq {
	int u, v, o;
};
struct qvq {
	int u, v;
	bool operator <(const qvq& A) const {
		return A.v < v;
	};
};
vector <int> too[N], op[N];
vector <qwq> to[N], ls[N];
vector <int> az[N], sum[N];
priority_queue <qvq> q;
queue <int> aaa;

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

signed main() {
	freopen("railway.in", "r", stdin);
	freopen("railway.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= m; ++i) {
		read(s[i]);
		read(c);
		az[i].push_back(c);
		sum[i].push_back(0);
		int now = 0, lst = c;
		for(int j = 1; j <= s[i]; ++j) {
			read(t), read(c);
			to[lst].push_back(qwq {c, t, i});
			ls[c].push_back(qwq {lst, t, i});
			az[i].push_back(c);
			t+=sum[i][now];
			sum[i].push_back(t);
			++now, lst=c;
		}
	}
	for(int i = 1; i <= n; ++i)
		dis[i]=inf;
	q.push(qvq {1, 0});
	dis[1]=0;
	while(!q.empty()) {
		qvq it = q.top(); q.pop();
		if(it.v != dis[it.u]) continue;
		for(qwq o : to[it.u])
			if(o.v+it.v < dis[o.u]) {
				dis[o.u]=o.v+it.v;
				q.push(qvq {o.u, o.v+it.v});
			}
	}
	
	for(int i = 1; i <= n; ++i)
		disn[i]=inf;
	q.push(qvq {n, 0});
	disn[n]=0;
	while(!q.empty()) {
		qvq it = q.top(); q.pop();
		if(it.v != disn[it.u]) continue;
		for(qwq o : ls[it.u])
			if(o.v+it.v < disn[o.u]) {
				disn[o.u]=o.v+it.v;
				q.push(qvq {o.u, o.v+it.v});
			}
	}
	for(int i = 1; i <= n; ++i)
		for(qwq o : to[i])
			if(dis[i]+o.v+disn[o.u] == dis[n])
				too[i].push_back(o.u), ++in[o.u], 
				op[o.u].push_back(o.o);
	aaa.push(1);
	while(!aaa.empty()) {
		int it = aaa.front();
		aaa.pop();
		cnt[it]=++nmb;
		ooo[nmb]=it;
		for(int y : too[it])
			if(!(--in[y])) 
				aaa.push(y);
	}
	for(int i = 2; i <= nmb; ++i) 
		for(int j : op[ooo[i]]) {
			int r = 0;
			for(r = 0; r <= s[j]; ++r) 
				if(az[j][r] == ooo[i])
					break;
			for(int p = 0; p < r; ++p) {
				int y = az[j][p], ww = sum[j][r]-sum[j][p];
				if(cnt[y] > i || !cnt[y]) continue;
				if(dis[y]+ww+disn[ooo[i]] == dis[n])
					ans[ooo[i]]=max(ans[ooo[i]], ans[y]+1LL*ww*ww);
			}
		}
	write(dis[n], ' ');
	write(ans[n], '\n');
	return 0;
}
