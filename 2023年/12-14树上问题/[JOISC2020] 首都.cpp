#include <bits/stdc++.h>
using namespace std;
const int N = 4e5+5;
int n, k, u, v, ccc[N], vis[N], mxs[N], siz[N], rt, sum, fir[N], nxt[N], to[N], cnt, 
tot, zhan[N], ans, az, up[N], vvv[N], bl[N];
vector <int> pnt[N];

void edge(int x, int y) {
	nxt[++cnt]=fir[x];
	to[cnt]=y;
	fir[x]=cnt;
}
void get_rt(int x, int fa) {
	siz[x]=mxs[x]=1;
	for(int i = fir[x], y = to[i]; i; i=nxt[i], y=to[i]) 
		if(y != fa && vis[y] == 0) {
			get_rt(y, x);
			siz[x]+=siz[y];
			mxs[x]=max(mxs[x], siz[y]);
		}
	mxs[x]=max(mxs[x], sum-siz[x]);
	if(mxs[x] <= mxs[rt])
		rt=x;
}
void get_siz(int x, int fa) {
	siz[x]=1;
	up[x]=fa, bl[x]=bl[fa];
	for(int i = fir[x], y = to[i]; i; i=nxt[i], y=to[i]) 
		if(y != fa && vis[y] == 0) 
			get_siz(y, x), siz[x]+=siz[y];
}
void sol(int x) {
	az=0;
	while(tot)
		vvv[zhan[tot]]=0, --tot;
	queue <int> q;
	for(int y : pnt[ccc[x]]) {
		if(bl[y]^x) return ;
		q.push(y), vvv[y]=1;
		zhan[++tot]=y;
	}
	while(!q.empty()) {
		int now = q.front(); q.pop();
		if(now == x) continue; 
		if(!vvv[up[now]]) {
			int col = ccc[up[now]];
			for(int y : pnt[col]) 
				if(bl[y]^x) return ;
				else if(!vvv[y])
					vvv[y]=1, q.push(y), zhan[++tot]=y;
			++az;
		}
	}
	ans=min(ans, az);
}
void dfs(int x) {
	// cout<<x<<" "<<vis[x]<<"???\n";
	bl[x]=x;
	get_siz(x, x);
	vis[x]=1;
	sol(x);
	for(int i = fir[x], y = to[i]; i; i=nxt[i], y=to[i]) 
		if(vis[y] == 0) {
			sum=siz[y], rt=0;
			get_rt(y, x);
			dfs(rt);
		}
}

signed main() {
	scanf("%d%d", &n, &k);
	for(int i = 2; i <= n; ++i)
		scanf("%d%d", &u, &v), edge(u, v), edge(v, u);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &ccc[i]), pnt[ccc[i]].push_back(i);
	sum=n, mxs[0]=1000000000;
	ans=k-1;
	get_rt(1, 0);
	dfs(rt);
	printf("%d\n", ans);
	return 0;
}
