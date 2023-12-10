#include <bits/stdc++.h>
#define inf 1000000007
#define int long long 
using namespace std;
int n, m, s, t, cnt=1, tot, u, v, w, fir[800005], nxt[800005], to[800005], val[800005], vis[800005], ans, 
fx[5][2]={{-1, 0}, {1, 0}, {0, 1}, {0, -1}, {0, 0}}, sum;

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
	for(int i = 1; i <= 3*n*m+2; ++i) vis[i]=0;
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
	cnt=1;
	read(n), read(m);
	s=3*n*m+2, t=3*n*m+1;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			read(w), ++tot, edge(s, tot, w), sum+=w;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			read(w), edge((i-1)*m+j, t, w), sum+=w;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			read(w), ++tot, edge(s, tot, w), sum+=w;
			for(int o = 0; o <= 4; ++o) {
				int x = i+fx[o][0], y = j+fx[o][1];
				if(x < 1 || x > n || y < 1 || y > m) continue;
				edge(tot, (x-1)*m+y, inf);
			}
		}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			read(w), ++tot, edge(tot, t, w), sum+=w;
			for(int o = 0; o <= 4; ++o) {
				int x = i+fx[o][0], y = j+fx[o][1];
				if(x < 1 || x > n || y < 1 || y > m) continue;
				edge((x-1)*m+y, tot, inf);
			}
		}
//	write(tot, ' '), write(t,'\n');
	while(bfs())
		ans+=dfs(s, inf)/*, cout<<ans<<"\n"*/;
	write(sum-ans, '\n'); 
	return 0;
}
