#include <bits/stdc++.h>
#define inf 1000000007
#define int long long 
using namespace std;
const int N = 5e2+5;
int n, m, a[N][N], s, t, cnt, fir[800005], nxt[800005], to[800005], val[800005], vis[800005], ans;
char ss[N][N];

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
	cnt=1;
	read(n), read(m);
	s=n+m+1, t=n+m+2;
	for(int i = 1; i <= n; ++i)
		scanf("%s", ss[i]+1), edge(s, i, 1);
	for(int i = 1; i <= m; ++i)
		edge(n+i, t, 1);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			a[i][j]=((ss[i][j] == 'B')^(ss[i+1][j] == 'B')^(ss[i][j+1] == 'B')^(ss[i+1][j+1] == 'B'));
	for(int i = 1; i < n; ++i)
		for(int j = 1; j < m; ++j)
			if(a[i][j] && a[i][m] && a[n][j])
				edge(i, n+j, 1);
	while(bfs())
		ans+=dfs(s, inf);
//	write(ans, '\n');
	a[n][m]^=(ans&1);
	ans=-ans;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			ans+=a[i][j];
	write(ans, '\n');
	return 0;
}