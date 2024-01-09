#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 2e4+5, V = 1e4+5, M = 5e6+5;
int n, a[N], b[N], c[N], viss[N], cnt=1, s, t, fir[N<<5], nxt[M], to[M], val[M], vis[N<<5], ans;

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
	val[cnt]=(ww^1);
}
int bfs() {
	queue<int> qwq;
	for(int i = 1; i <= t; ++i) vis[i]=0;
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
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= n; ++i)
		read(b[i]);
	for(int i = 1; i <= n; ++i)
		read(c[i]);
	s=20000+n*2+1, t=20000+n*2+2;
	for(int i = 1; i <= n; ++i) {
		int x = 1;
		if(!viss[a[i]])
			viss[a[i]]=1, x=0, ++ans;
		edge(s, i, x);
		edge(i+n, t, x);
		edge(i, a[i]+n+n, x);
		edge(i, b[i]+n+n, 1);
		edge(a[i]+n+n+10000, i+n, x);
		edge(c[i]+n+n+10000, i+n, 1);
	}
	for(int i = 1; i <= 10000; ++i)
		edge(i+n+n, i+n+n+10000, (!viss[i]));
	while(bfs())
		ans+=dfs(s, inf);
	write(ans, '\n');
	for(int i = 1; i <= 10000; ++i)
		for(int j = fir[i+n+n]; j; j=nxt[j])
			if(to[j] == i+n+n+10000 && !val[j]) 
				write(i, ' ');
	return 0;
}
