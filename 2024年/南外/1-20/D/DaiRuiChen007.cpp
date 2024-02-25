#include<bits/stdc++.h>
using namespace std;
namespace F {
const int MAXV=1e5+5,MAXE=5e5+5,inf=1e9;
struct Edge {
	int v,f,lst;
}	G[MAXE];
int S,T,tot=1,hd[MAXV],cur[MAXV],dep[MAXV];
void init() { tot=1,memset(hd,0,sizeof(hd)); }
void adde(int u,int v,int w) { G[++tot]={v,w,hd[u]},hd[u]=tot; }
void link(int u,int v,int w) { adde(u,v,w),adde(v,u,0); }
bool BFS() {
	memcpy(cur,hd,sizeof(cur)),memset(dep,-1,sizeof(dep));
	queue <int> Q;
	Q.push(S),dep[S]=0;
	while(!Q.empty()) {
		int u=Q.front(); Q.pop();
		for(int i=hd[u];i;i=G[i].lst) if(G[i].f&&dep[G[i].v]==-1) {
			dep[G[i].v]=dep[u]+1,Q.push(G[i].v);
		}
	}
	return ~dep[T];
}
int dfs(int u,int f) {
	if(u==T) return f;
	int r=f;
	for(int i=cur[u];i;i=G[i].lst) {
		int v=G[cur[u]=i].v;
		if(G[i].f&&dep[v]==dep[u]+1) {
			int g=dfs(v,min(r,G[i].f));
			if(!g) dep[v]=-1;
			G[i].f-=g,G[i^1].f+=g,r-=g;
		}
		if(!r) return f;
	}
	return f-r;
}
int Dinic() {
	int f=0;
	while(BFS()) f+=dfs(S,inf);
	return f;
}
}
const int MAXN=2005,inf=1e9;
int col[MAXN];
signed main() {
	freopen("deadline.in","r",stdin);
	freopen("deadline.out","w",stdout);
	F::init();
	int n,m,e;
	scanf("%d%d%d",&n,&m,&e);
	int s=F::S=n+2*m+1,t=F::T=n+2*m+2;
	for(int i=1;i<=m;++i) F::link(i,i+m,1);
	for(int i=1;i<=n;++i) {
		scanf("%d",&col[i]);
		if(col[i]) F::link(s,i+2*m,1);
		else F::link(i+2*m,t,1);
	}
	for(int u,v;e--;) {
		scanf("%d%d",&u,&v);
		if(col[u]) F::link(u+2*m,v,inf);
		else F::link(v+m,u+2*m,inf);
	}
	printf("%d\n",F::Dinic());
	return 0;
}
