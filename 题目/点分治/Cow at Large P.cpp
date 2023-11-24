#include <bits/stdc++.h>
using namespace std;
const int N = 7e4+5;
int n, u, v, ds[N], tr[N<<1], nx[N], p[N], vis[N], siz[N], rt, mxs[N], sum, ans[N], zhan[N], tot, too, zha[N];
vector <int> to[N];
queue <int> q;

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
void add(int x, int w) {
	while(x <= (n<<1))
		tr[x]+=w, x=x+(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x >= 1)
		ret+=tr[x], x=x-(x&(-x));
	return ret;
}
void get_rt(int x, int fa) {
	siz[x]=mxs[x]=1;
	for(int y : to[x])
		if(y != fa && !vis[y]) {
			get_rt(y, x);
			siz[x]+=siz[y];
			mxs[x]=(siz[y] > mxs[x] ? siz[y] : mxs[x]);
		}
	mxs[x]=max(mxs[x], sum-siz[x]);
	if(mxs[x] < mxs[rt])
		rt=x;
}
void get_son(int x, int fa) {
	p[x]=p[fa]+1;
	siz[x]=1;
	zhan[++tot]=x;
	for(int y : to[x])
		if(y != fa && !vis[y]) 
			get_son(y, x), siz[x]+=siz[y];
}
void dfs(int x) {
	p[x]=0;
	vis[x]=1;
	for(int o = 0, y = 0; o < to[x].size(); ++o) {
		y=to[x][o];
		if(!vis[y]) {
			tot=0;
			get_son(y, x);
			for(int j = 1; j <= tot; ++j)
				ans[zhan[j]]+=ask(p[zhan[j]]+n);
			for(int j = 1; j <= tot; ++j)
				add(nx[zhan[j]]-p[zhan[j]]+n, ds[zhan[j]]), 
				zha[++too]=zhan[j];
		}
	}
	ans[x]+=ask(p[x]+n);
	while(too)
		add(nx[zha[too]]-p[zha[too]]+n, -ds[zha[too]]), --too;
	add(nx[x]-p[x]+n, ds[x]);
	zha[++too]=x;
	for(int o = (int) to[x].size()-1, y = 0; o >= 0; --o) {
		y=to[x][o];
		if(!vis[y]) {
			tot=0;
			get_son(y, x);
			for(int j = 1; j <= tot; ++j)
				ans[zhan[j]]+=ask(p[zhan[j]]+n);
			for(int j = 1; j <= tot; ++j)
				add(nx[zhan[j]]-p[zhan[j]]+n, ds[zhan[j]]), 
				zha[++too]=zhan[j];
		}
	}
	while(too)
		add(nx[zha[too]]-p[zha[too]]+n, -ds[zha[too]]), --too;
	for(int y : to[x]) 
		if(!vis[y]) {
			sum=siz[y];
			rt=0;
			get_rt(y, x);
			dfs(rt);
		}
}

signed main() {
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u), ++ds[u], ++ds[v];
	for(int i = 1; i <= n; ++i)
		if(ds[i] == 1)
			q.push(i), p[i]=1;
	while(!q.empty()) {
		int it = q.front(); q.pop();
		for(int y : to[it])
			if(!p[y])
				p[y]=1, nx[y]=nx[it]+1, q.push(y);
	}
	for(int i = 1; i <= n; ++i)
		ds[i]=2-ds[i];
	mxs[0]=n+1;
	sum=n;
	get_rt(1, 0);
	dfs(rt);
	for(int i = 1; i <= n; ++i)
		write(ans[i], '\n');
	return 0;
}