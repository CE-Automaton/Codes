#include <bits/stdc++.h>
#define inf 2000000007
using namespace std;
const int N = 2e2+5, M = 1e6+5;
int n, m, k, s, t, u, v, c[N], cnt=1, fir[N<<4], nxt[M], to[M], val[M], vis[N<<4], ans;

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

void edge(int x, int y, int ww) {
	nxt[++cnt]=fir[x];
	fir[x]=cnt;
	to[cnt]=y;
	val[cnt]=ww;
	nxt[++cnt]=fir[y];
	fir[y]=cnt;
	to[cnt]=x;
	val[cnt]=0;
}
int bfs() {
	queue<int> qwq;
	for(int i = 1; i <= n*k*2; ++i) vis[i]=0;
	qwq.push(s);
	vis[s]=1;
	while(!qwq.empty()) {
		int it = qwq.front();
		qwq.pop();
		for(int i = fir[it]; i; i = nxt[i])
			if(val[i] > 0 && !vis[to[i]])
				vis[to[i]]=vis[it]+1, qwq.push(to[i]) ;
	}
	return vis[t];
}
int dfs(int x, int in) {
	if(x == t) return in;
	int out = 0; 
	for(int i = fir[x]; i; i = nxt[i])
		if(val[i] > 0 && vis[to[i]] == vis[x]+1) {
			int qwq = dfs(to[i], min(in, val[i]));
			if(!qwq) continue;
			in-=qwq;
			out+=qwq;
			val[i]-=qwq;
			val[i^1]+=qwq;
			if(in == 0)
				break;
		} 
	if(out == 0)
		vis[x]=0;
	return out;
}

signed main() {
	freopen("apers.in", "r", stdin);
	freopen("apers.out", "w", stdout);
	read(n), read(m), read(k);
	read(s), read(t);
	for(int i = 1; i <= n; ++i) {
		read(c[i]);
		for(int j = 1; j <= k; ++j) {
			edge((j-1)*2*n+i, (j-1)*2*n+i+n, c[i]);
			if(j < k)
				edge((j-1)*2*n+i, j*2*n+i+n, inf);
		}
	}
	for(int i = 1; i <= m; ++i) {
		read(u), read(v);
		for(int j = 1; j <= k; ++j)
			edge((j-1)*2*n+u+n, (j-1)*2*n+v, inf);
	}
	t=n+t;
	if(bfs() < k*2) {
		puts("-1");
		return 0;
	}
	t=(k-1)*n*2+t;
	while(bfs() && ans < inf)
		ans+=dfs(s, inf);
	if(ans >= inf)
		puts("-1");
	else
		write(ans, '\n');
	return 0;
}
