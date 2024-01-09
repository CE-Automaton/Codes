#include <bits/stdc++.h>
using namespace std;
int n, m, cnt, xx, yy, aa, bb, s, t, fir[2405], nxt[4000005], to[4000005], val[4000005], vis[2405], ans;

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
	for(int i = 1; i <= n+m+2; ++i) vis[i]=0;
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
	read(n), read(m);
	cnt=1;
	s=n+m+2, t=n+m+1;
	for(int i = 1; i <= n; ++i) {
		read(xx), read(yy);
		edge(s, i, xx);
		ans+=xx;
		for(int j = 1; j <= yy; ++j)
			read(aa), read(bb), edge(i, aa+n, bb);
	}
	for(int i = 1; i <= m; ++i) 
		read(xx), edge(i+n, t, xx);
	while(bfs())
		ans-=dfs(s, 1999999999);
	write(max(ans, 0), '\n');
	return 0;
}