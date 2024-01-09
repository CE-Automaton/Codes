#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
struct edge{
	int u,v,w;
	bool operator<(const edge&a)const{
		return w<a.w;
	}
};
struct nd{
	int c1,v1;
	int c2,v2;
};
struct change{
	nd a;int tar;
};
edge w[500005];
int n,m,ccc,q;
int fa[500005];
vector<pair<int,int> > to[500005];
int ff[500005];
int fv[500005];
nd p[500005];
int col[500005];
int tim[500005];
int rt(int x){return fa[x]==x?x:fa[x]=rt(fa[x]);}
void dfs(int x,int ffa){
	for(auto v:to[x]){
		if(v.first==ffa)continue;
		ff[v.first]=x;fv[v.first]=v.second;
		dfs(v.first,x);
	}
	return ;
}
vector<pair<int,int> > h[1000005];
void M(int l,int r,int L,int R,int x,int id,int v){
	if(L>r or R<l)return ;
	if(L<=l and R>=r){
		h[x].push_back({id,v});
		return ;
	}
	int mid=(l+r)>>1;
	M(l,mid,L,R,x*2,id,v);M(mid+1,r,L,R,x*2+1,id,v);
	return ;
}
int ans[500005];
int now;
void Q(int l,int r,int x){
	int hist=now;
	vector<change> rec;
	for(auto v:h[x]){
		if(p[v.first].c1!=v.second)now=min(now,p[v.first].v1);
		else now=min(now,p[v.first].v2);
		int y=ff[v.first];
		if(y){
			if(col[y]){
				if(col[y]!=v.second)now=min(now,fv[v.first]);
			}else{
			    nd pre=p[y];
				if(pre.c1==v.second)p[y].v1=min(p[y].v1,fv[v.first]);
				else if(pre.c2==v.second){
					p[y].v2=min(p[y].v2,fv[v.first]);
					if(p[y].v2<p[y].v1){
						swap(p[y].v1,p[y].v2);
						swap(p[y].c1,p[y].c2);
					}
				}else{
					if(fv[v.first]<p[y].v2){
						p[y].v2=fv[v.first];
						p[y].c2=v.second;
					}
					if(p[y].v2<p[y].v1){
						swap(p[y].v1,p[y].v2);
						swap(p[y].c1,p[y].c2);
					}
				}
				rec.push_back((change){pre,y});
			}
		}
		col[v.first]=v.second;
	}
	if(l==r){
		ans[l]=now;
	}else{
	    int mid=(l+r)>>1;
	    Q(l,mid,x*2);Q(mid+1,r,x*2+1);
	}
	for(int i=rec.size()-1;i>=0;i--)p[rec[i].tar]=rec[i].a;
	for(auto v:h[x])col[v.first]=0;
	now=hist;
	return ;
}
signed main(){
	freopen("noip.in","r",stdin);
	freopen("noip.out","w",stdout);
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>ccc>>q;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		cin>>w[i].u>>w[i].v>>w[i].w;
	}
	sort(w+1,w+1+m);
	for(int i=1;i<=m;i++){
		if(rt(w[i].u)==rt(w[i].v))continue;
		fa[rt(w[i].u)]=rt(w[i].v);
		to[w[i].u].push_back({w[i].v,w[i].w});
		to[w[i].v].push_back({w[i].u,w[i].w});
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)p[i]=(nd){0,INT_MAX,0,INT_MAX};
	for(int i=1;i<=n;i++){
		cin>>col[i];tim[i]=0;
	}
	for(int i=1;i<=q;i++){
		int u,x;cin>>u>>x;
		if(tim[u]!=0 or i!=1)M(1,q,tim[u]==0?1:tim[u],i-1,1,u,col[u]);
		col[u]=x;tim[u]=i;
	}
	for(int i=1;i<=n;i++)M(1,q,tim[i],q,1,i,col[i]);
	now=INT_MAX;
	for(int i=1;i<=n;i++)col[i]=0;
	Q(1,q,1);
	for(int i=1;i<=q;i++)cout<<ans[i]<<'\n';
	return 0;
}
