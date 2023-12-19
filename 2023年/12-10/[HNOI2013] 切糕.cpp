#include <bits/stdc++.h>
#define inf 1000000007
#define int long long 
using namespace std;
int n, m, r, s, t, cnt=1, w, d, fir[800005], nxt[800005], to[800005], val[800005], vis[800005], ans, 
fx[4][2]={{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

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
	for(int i = 1; i <= r*n*m+2; ++i) vis[i]=0;
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
int ask(int rr, int xx, int yy) {
	return (rr-1)*n*m+(xx-1)*m+yy;
}

signed main() {
	read(n), read(m), read(r);
	read(d);
	s=r*n*m+2, t=r*n*m+1;
	for(int o = 1; o <= r; ++o)
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j) 
				read(w), edge((o == 1 ? s : ask(o-1, i, j)), ask(o, i, j), w);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) 
			edge(ask(r, i, j), t, inf);
	for(int o = d+1; o <= r; ++o)
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j) 
				for(int p = 0; p <= 3; ++p) {
					int x = i+fx[p][0], y = j+fx[p][1];
					if(x < 1 || x > n || y < 1 || y > m) continue;
					edge(ask(o, i, j), ask(o-d, x, y), inf);
					if(o+d+1 <= r)
						edge(ask(o+d+1, x, y), ask(o, i, j), inf);
				}
	while(bfs())
		ans+=dfs(s, inf)/*, cout<<ans<<"\n"*/;
	write(ans, '\n'); 
	return 0;
}