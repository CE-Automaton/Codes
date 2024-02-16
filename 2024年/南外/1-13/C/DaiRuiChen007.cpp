#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5;
int n,m;
struct Graph {
	int ans,del,siz[MAXN],dsu[MAXN],deg[MAXN];
	bool mrk;
	void build(int x) {
		ans=(~x)?1:n,del=x,mrk=0;
		for(int i=1;i<=n;++i) siz[i]=1,dsu[i]=i,deg[i]=0;
	}
	int find(int x) { return x^dsu[x]?dsu[x]=find(dsu[x]):x; }
	void link(int u,int v) {
		if(u==del||v==del||!ans) return ;
		if(++deg[u]>=3||++deg[v]>=3) return ans=0,void();
		u=find(u),v=find(v);
		if(u==v) {
			if(~del) ans=0;
			else {
				if(!mrk&&ans==n) ans=siz[u],mrk=1;
				else ans=0;
			}
			return ;
		}
		if(siz[u]>siz[v]) swap(u,v);
		dsu[u]=v,siz[v]+=siz[u];
	}
}	o[5];
vector <int> G[MAXN];
signed main() {
	freopen("rings.in","r",stdin);
	freopen("rings.out","w",stdout);
	ios::sync_with_stdio(false);
	bool flg=0;
	cin>>n>>m;
	o[0].build(-1);
	for(int x,y;m--;) {
		cin>>x;
		if(~x) {
			cin>>y,++x,++y;
			if(!flg) {
				o[0].link(x,y);
				G[x].push_back(y);
				G[y].push_back(x);
				if(G[x].size()==3) {
					o[1].build(x);
					for(int i:{0,1,2}) o[i+2].build(G[x][i]);
					for(int u=1;u<=n;++u) for(int v:G[u]) if(v>u) {
						for(int t:{1,2,3,4}) o[t].link(u,v);
					}
					flg=true;
					continue;
				}
				if(G[y].size()==3) {
					o[1].build(y);
					for(int i:{0,1,2}) o[i+2].build(G[y][i]);
					for(int u=1;u<=n;++u) for(int v:G[u]) if(v>u) {
						for(int t:{1,2,3,4}) o[t].link(u,v);
					}
					flg=true;
					continue;
				}
			} else for(int i:{1,2,3,4}) o[i].link(x,y);
		} else {
			if(!flg) cout<<o[0].ans<<"\n";
			else {
				int ans=0;
				for(int i:{1,2,3,4}) ans+=o[i].ans;
				cout<<ans<<"\n";
			}
		}
	}
	return 0;
}
