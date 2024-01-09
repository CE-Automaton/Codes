#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 5e3+5;
int n, m, l[N], r[N], w[N], u, v, vis[N], cnt[N], fa[N];
vector <int> to[N];
struct qwq {
	int d, nw;
	bool operator <(const qwq& A) const {
		return A.nw < nw;
	}
}; 
priority_queue <qwq> q;

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
int find(int x) {
	return (fa[x] == x ? x : fa[x]=find(fa[x]));
}

signed main() {
	freopen("journey.in", "r", stdin);
	freopen("journey.out", "w", stdout);
	read(n), read(m);
	int pd = 1;
	for(int i = 1; i <= n; ++i) 
		read(l[i]), read(r[i]), read(w[i]), pd&=(l[i] == 1);
	if(pd) {
		for(int i = 1; i <= n; ++i)
			cnt[i]=1, fa[i]=1;
		for(int i = 1; i <= m; ++i) {
			read(u), read(v);
			u=find(u), v=find(v);
			if(u == v) continue;
			if(cnt[u] < cnt[v]) swap(u, v);
			fa[v]=u;
			cnt[u]+=cnt[v];
			w[u]=max(w[u], w[v]);
		}
		for(int i = 1; i <= n; ++i)
			write(w[find(i)], ' ');
	}
	else {
		if(n <= 3000) {
			for(int i = 1; i <= m; ++i)
				read(u), read(v), to[u].push_back(v), to[v].push_back(u);
			for(int i = 1; i <= n; ++i) {
				for(int j = 1; j <= n; ++j)
					vis[j]=inf;
				vis[i]=l[i];
				q.push(qwq {i, l[i]});
				int ans = w[i];
				while(!q.empty()) {
					qwq it = q.top();
					q.pop();
					ans=max(ans, w[it.d]);
					if(it.nw > vis[it.d]) continue;
					for(int y : to[it.d])
						if(r[y] >= max(l[y], it.nw) && vis[y] > max(l[y], it.nw))
							vis[y]=max(l[y], it.nw), q.push(qwq {y, max(l[y], it.nw)});
				}
				write(ans, ' ');
			}
		}
	}
	return 0;
}
