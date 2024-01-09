#include <bits/stdc++.h>
#define inf 1000000007
#define int long long 
using namespace std;
const int N = 5e1+3;
int n, a, aa, aaa, b, bb, bbb, s, t, cnt=1, fir[800005], nxt[800005], to[800005], val[800005], vis[800005], ans, sum;
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
	val[cnt]=ww;
}
int bfs() {
	queue<int> qwq;
	for(int i = 1; i <= n+2; ++i) vis[i]=0;
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
	while(scanf("%lld%lld%lld%lld%lld%lld%lld", &n, &a, &aa, &aaa, &b, &bb, &bbb) != EOF) {
		++a, ++aa, ++b, ++bb; 
		sum=ans=0;
		s=n+1, t=n+2;
		cnt=1;
		edge(s, a, aaa);
		edge(s, b, bbb);
		edge(aa, t, aaa);
		edge(bb, t, bbb);
		for(int i = 1; i <= n; ++i)
			scanf("%s", ss[i]+1);
		for(int i = 1; i <= n; ++i)
			for(int j = 1+i; j <= n; ++j)
				if(ss[i][j] == 'O')
					edge(i, j, 1);
				else
					if(ss[i][j] == 'N')
						edge(i, j, inf);
		while(bfs())
			ans+=dfs(s, inf);
		cnt=1;
		for(int i = 1; i <= n+2; ++i)
			fir[i]=0;
		swap(b, bb);
		edge(s, a, aaa);
		edge(s, b, bbb);
		edge(aa, t, aaa);
		edge(bb, t, bbb);
		for(int i = 1; i <= n; ++i)
			for(int j = 1+i; j <= n; ++j)
				if(ss[i][j] == 'O')
					edge(i, j, 1);
				else
					if(ss[i][j] == 'N')
						edge(i, j, inf);
		while(bfs())
			sum+=dfs(s, inf);
//			cout<<sum<<" "<<ans<<" "<<aaa+bbb<<"\n";
		if(sum != ans || sum != aaa+bbb)
			puts("No");
		else
			puts("Yes");
		for(int i = 1; i <= n+2; ++i)
			fir[i]=0;
	}
	return 0;
}