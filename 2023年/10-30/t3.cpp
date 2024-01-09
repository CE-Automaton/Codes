#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 2e2+5, M = 4.1e4+5;
int n, r, g, b, gs, dp[N][M], tot, u, v, ans, vis[N], sum, rt, siz[N], mxs[N], toto, zhan[N], dfn[N], ddfn[N];
char s[N];
unordered_map <int, int> t;
vector <int> to[N];

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
int ask(int i, int j, int k) {
	return i*(b+1)*(g+1)+j*(g+1)+k;
}
void getrt(int x, int fa) {
	siz[x]=1;
	mxs[x]=0;
	for(int y : to[x]) 
		if(y != fa && !vis[y]) {
			getrt(y, x);
			mxs[x]=max(mxs[x], siz[y]);
		}
	mxs[x]=max(mxs[x], sum-siz[x]);
	if(mxs[x] < mxs[rt])
		rt=x;
}
void getsiz(int x, int fa) {
	siz[x]=1;
	for(int y : to[x]) 
		if(y != fa && !vis[y]) {
			getsiz(y, x);
			siz[x]+=siz[y];
		}
}
void ddfs(int x, int fa) {
	zhan[++toto]=x;
	for(int y : to[x])
		if(y != fa && !vis[y]) 
			ddfs(y, x); 
	ddfn[x]=toto;
} 
void dfs(int x) {
	toto=0;
	ddfs(x, x);
	for(int i = r; i >= 0; --i)
	for(int j = b; j >= 0; --j)
	for(int k = g; k >= 0; --k) 
		dp[toto][ask(i, j, k)]=0;
	dp[toto][0]=1;
	for(int ii = toto-1; ii >= 0; --ii) {
		int qwq = zhan[ii+1];
		for(int j = 0; j <= tot; ++j)
			dp[ii][j]=dp[ddfn[qwq]][j];
		for(int i = (s[qwq] == 'r'); i <= r; ++i)
		for(int j = (s[qwq] == 'b'); j <= b; ++j)
		for(int k = (s[qwq] == 'g'); k <= g; ++k) {
			int tt = ask(i, j, k), ttt = ask(i-(s[qwq] == 'r'), j-(s[qwq] == 'b'), k-(s[qwq] == 'g'));
			dp[ii][tt]=upd(dp[ii][tt]+dp[ii+1][ttt]);
		}
	}
	for(int j = 1; j <= tot; ++j)
		ans=upd(ans+dp[0][j])/*, cout<<x<<"! "<<i<<" "<<j<<" "<<k<<" "<<dp[x][ask(i, j, k)]<<"\n"*/;
	vis[x]=1;
	for(int y : to[x])
		if(!vis[y]) {
			getsiz(y, 0);
			sum=siz[y];
			rt=0;
			getrt(y, 0);
			dfs(rt);
		}
}

signed main() {
//	freopen("yuukei.in", "r", stdin);
//	freopen("yuukei.out", "w", stdout);
	read(n), read(r), read(b), read(g);
	tot=ask(r, b, g);
	scanf("%s", s+1);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	mxs[0]=n+1;
	sum=n;
	getrt(1, 0);
	dfs(1);
	write(ans, '\n');
	return 0;
}
