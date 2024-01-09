#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define all(a) (a).begin(),(a).end()
#ifdef DEBUG
template<class T>
ostream& operator << (ostream &out,vector<T> a){
	out<<'[';
	for(T x:a)out<<x<<',';
	return out<<']';
}
template<class T>
vector<T> ary(T *a,int l,int r){
	return vector<T>{a+l,a+1+r};
}
template<class T>
void debug(T x){
	cerr<<x<<endl;
}
template<class T,class...S>
void debug(T x,S...y){
	cerr<<x<<' ',debug(y...);
}
#else
#define debug(...) void()
#endif
const int N=1e5+10;
int n,m;
vector<int>to[N],tr[N];
namespace Tree{
	int dep[N],fa[N],siz[N],top[N],son[N];
	void dfs1(int u){
		dep[u]=dep[fa[u]]+1;
		for(int v:to[u])if(v^fa[u]){
			fa[v]=u,dfs1(v);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])son[u]=v;
		}
	}
	void dfs2(int u,int t){
		top[u]=t;
		if(son[u])dfs2(son[u],t);
		for(int v:to[u])if(v^fa[u]&&v^son[u])dfs2(v,v);
	}
	int LCA(int u,int v){
		for(;top[u]^top[v];u=fa[top[u]]){
			if(dep[top[u]]<dep[top[v]])swap(u,v);
		}
		return dep[u]<dep[v]?u:v;
	}
	int sum[N];
	void link(int u,int v){
		if(dep[u]<dep[v])swap(u,v);
		if(fa[u]==v)return;
		if(fa[fa[u]]==v||fa[u]==fa[v]){
			tr[u].push_back(v),tr[v].push_back(u);
		}else{
			int t=LCA(u,v);
			sum[u]++,sum[t]--;
			sum[v]++,sum[fa[t]]--;
		}
	}
	void init(){
		dfs1(1),dfs2(1,1);
	}
	void push1(int u=1){
		for(int v:to[u])if(v^fa[u]){
			push1(v);
			sum[u]+=sum[v];
		}
	}
	int tot[N];
	void push2(int u=1){
		tot[u]=!!sum[u];
		for(int v:to[u])if(v^fa[u]){
			push2(v);
			tot[u]+=tot[v];
		}
	}
	int count(int u,int v){
		if(fa[u]==v)return tot[1]-tot[u];
		else if(fa[v]==u)return tot[v];
		else return 0;
	}
	bool count(int u){
		return !!sum[u];
	}
}
using Tree::count;
bool chk(int u,int v){
	return find(all(tr[u]),v)!=tr[u].end();
}
ll ans;
int rt,siz[N],mx[N],vis[N],dep[N],dis[N];
void dfs1(int u,int fa=0){
	siz[u]=1,mx[u]=0;
	for(int v:to[u])if(v^fa&&!vis[v]){
		dfs1(v,u);
		siz[u]+=siz[v];
		mx[u]=max(mx[u],siz[v]);
	}
}
void dfs2(int s,int u,int fa=0){
	mx[u]=max(mx[u],s-siz[u]);
	for(int v:to[u])if(v^fa&&!vis[v]){
		dfs2(s,v,u);
	}
	if(mx[u]<mx[rt])rt=u;
}
void dfs3(int u,int fa=0){
	dep[u]=dep[fa]+1;
	for(int v:to[u])if(v^fa){
		if(!vis[v])dfs3(v,u);
		else dep[v]=dep[u]+1;
	}
}
namespace Jump{
	const int K=__lg(N)+1;
	int tag[N],anc[K][N];
	vector<int>pos;
	void dfs(int u,int fa=0,int las=0){
		pos.push_back(u);
		anc[0][u]=fa;
		for(int v:tr[u])if(v==las)anc[0][u]=v;
		tag[u]=tag[anc[0][u]];
		if(fa!=rt&&anc[0][u]==rt)tag[u]=1;
		for(int v:to[u])if(v^fa){
			if(!vis[v])dfs(v,u,fa);
			else{
				pos.push_back(v),anc[0][v]=u;
				for(int w:tr[v])if(w==fa)anc[0][v]=w;
				tag[v]=tag[anc[0][v]];
				if(u!=rt&&anc[0][v]==rt)tag[v]=1;
			}
		}
	}
	void init(int u){
		pos.clear(),dfs(u);
		for(int i=1;(1<<i)<=n;i++){
			for(int u:pos)anc[i][u]=anc[i-1][anc[i-1][u]];
		}
		// debug(ary(anc[0],1,n));
	}
	int jump(int u,int t){
		int ans=0;
		for(int i=__lg(dep[u]-dep[t]+1);~i;i--){
			if(dep[anc[i][u]]>=dep[t])u=anc[i][u],ans+=1<<i;
		}
		return ans+(dep[u]>dep[t]);
	}
}
using Jump::jump;
void dfs4(int s,int u,int fa=0){
	dis[u]=jump(u,s),siz[u]=1;
	for(int v:to[u])if(v^fa){
		if(!vis[v]){
			dfs4(s,v,u);
			siz[u]+=siz[v];
		}else{
			dis[v]=jump(v,s);
		}
	}
}
struct BIT1{
	int c[N];
	vector<pair<int,int>>upd;
	void add(int x,int y){
		upd.push_back({x,-y});
		for(;x;x^=x&-x)c[x]+=y;
	}
	int get(int x,int y=0){
		for(;x<=n;x+=x&-x)y+=c[x];
		return y;
	}
	int count(){
		return upd.size();
	}
	void clr(int lim=0){
		for(int x,y;upd.size()>lim;upd.pop_back()){
			for(tie(x,y)=upd.back();x;x^=x&-x)c[x]+=y;
		}
	}
};
struct BIT2{
	int c[N];
	vector<pair<int,int>>upd;
	void add(int x,int y){
		upd.push_back({x,-y});
		for(;x<=n;x+=x&-x)c[x]+=y;
	}
	int get(int x,int y=0){
		for(;x;x^=x&-x)y+=c[x];
		return y;
	}
	int count(){
		return upd.size();
	}
	void clr(int lim=0){
		for(int x,y;upd.size()>lim;upd.pop_back()){
			for(tie(x,y)=upd.back();x<=n;x+=x&-x)c[x]+=y;
		}
	}
};
namespace Solve1{
	BIT1 A;
	void query(int u,int fa,int t=0,int p=0){
		if(count(fa,u))t=u,p=0;
		if(t){
			// debug(u,t,p,jump(u,t),A.get(max(0,jump(u,t)-dep[t]+p+1)+1));
			ans+=A.get(max(0,jump(u,t)-dep[t]+p+1)+1);
		}
		for(int v:to[u])if(v^fa&&!vis[v]){
			int tt=t,pp=p;
			for(int w:tr[v]){
				if(dep[v]==dep[w]&&count(u,w))tt=v,pp=1;
			}
			query(v,u,tt,pp);
		}
	}
	void insert(int w,int u,int fa){
		A.add(dep[u]+1,w);
		for(int v:to[u])if(v^fa&&!vis[v]){
			insert(w,v,u);
		}
	}
	void solve(int u){
		A.add(dep[u]+1,1);
		for(int v:to[u])if(!vis[v])insert(1,v,u);
		for(int v:to[u])if(!vis[v]){
			insert(-1,v,u),query(v,u),insert(1,v,u);
		}
		A.clr();
	}
}
namespace Solve2{
	BIT2 A[2];
	void update(int t,int w,int u,int fa=0){
		A[t].add(dis[u]+1,w);
		for(int v:to[u])if(v^fa&&!vis[v]){
			update(t,w,v,u);
		}
	}
	void query(int u,int fa=0,int t=0,int d=0){
		if(t){
			// debug(u,t,d,dis[t],ans,d-dis[t]-1+1);
			ans+=A[0].get(max(0,d-dis[t]-1+1));
			ans+=A[1].get(max(0,d-dis[t]-Jump::tag[t]+1));
			// debug(ans);
		}
		int fi=0,se=0;
		for(int v:to[u])if(v^fa){
			if(count(u,v)){
				// debug("edge",u,v);
				if(!fi)fi=v;
				else if(!se)se=v;
				else if(dis[v]<dis[fi])fi=v;
				else if(dis[v]<dis[se])se=v;
			}
		}
		if(dis[se]<dis[fi])swap(fi,se);
		// debug(u,t,d);
		for(int v:to[u])if(v^fa&&!vis[v]){
			if(t)query(v,u,t,d+1);
			else if(fi&&v!=fi)query(v,u,fi,2);
			else if(se&&v!=se)query(v,u,se,2);
			else if(count(v,u))query(v,u,u,1);
			else query(v,u);
		}
	}
	int tag[N];
	void solve(int u){
		if(!count(u))A[0].add(dis[u]+1,1);
		for(int v:to[u])if(!vis[v])tag[v]=u;
		for(int v:to[u])if(!vis[v]&&!count(u,v)){
			update(0,1,v,u);
		}
		for(int v:to[u])if(!vis[v]&&!count(v,u)){
			int las=A[0].count();
			for(int w:tr[v])if(tag[w]==u){
				update(1,1,w,u),update(0,-1,w,u);
			}
			// debug(rt,v,ary(Tree::sum,1,n));
			query(v,u);
			A[0].clr(las),A[1].clr();
		}
		A[0].clr();
	}
}
namespace Solve3{
	BIT1 A[2];
	void update(int t,int w,int u,int fa=0){
		A[t].add(dep[u]+1,w);
		for(int v:to[u])if(v^fa&&!vis[v]){
			update(t,w,v,u);
		}
	}
	void query(int o,int t,int p,int u,int fa=0){
		// debug(u,t,jump(u,t));
		ans+=A[o].get(jump(u,t)+p+1);
		for(int v:to[u])if(v^fa&&!vis[v]){
			query(o,t,p,v,u);
		}
	}
	int tag[N];
	vector<int>o[N];
	void solve(int u){
		A[0].add(dep[u]+1,1),A[1].add(dep[u]+1,1);
		int cur=0;
		for(int v:to[u])if(!vis[v]){
			tag[v]=u;
			if(!count(u,v))update(1,1,v,u);
			else if(cur)cur=-1;
			else cur=v;
		}
		if(count(u)){
			for(int v:to[u])if(!vis[v])update(0,1,v,u);
		}else{
			for(int v:to[u])if(!vis[v]&&v^cur)update(0,1,v,u);
		}
		for(int v:to[u])if(!vis[v]&&!count(u,v)){
			int las=A[0].count(),pos=A[1].count();
			update(0,-1,v,u),update(1,-1,v,u);
			int fi=0,se=0;
			for(int w:tr[v]){
				if(count(u,w))(fi?se:fi)=w;
			}
			// debug(v,fi,se,tr[v]);
			if(fi&&se){
				query(0,v,1,v);
			}else if(fi){
				if(tag[fi]==u){
					o[fi].push_back(v);
				}else query(0,v,1,v);
			}else{
				if(count(u))query(0,u,1,v);
				else if(!cur)query(0,u,1,v);
				else if(cur>0)query(1,u,1,v);
				else query(0,u,1,v);
			}
			// debug(v,ans);
			A[0].clr(las),A[1].clr(pos);
		}
		A[1].clr();
		for(int v:to[u])if(!vis[v]){
			if(o[v].empty())continue;
			int las=A[0].count();
			if(v^cur||count(u))update(0,-1,v,u);
			update(1,1,v,u);
			for(int w:o[v]){
				int las=A[0].count();
				update(0,-1,w,u);
				// debug("st",v,w,ans);
				query(0,w,1,w);
				// debug("mid",v,w,ans);
				if(v^cur||count(u))query(1,u,1,w);
				// debug("ed",v,w,ans);
				A[0].clr(las);
			}
			A[0].clr(las),A[1].clr();
			o[v].clear();
		}
		for(int v:to[u])if(!vis[v]){
			if(count(v,u)){
				// debug(u,v,siz[v]);
				ans+=siz[v];
			}
		}
		A[0].clr(),A[1].clr();
	}
}
void solve(int u){
	rt=0,dfs1(u),dfs2(siz[u],u),vis[u=rt]=1;
	dfs3(u),Jump::init(u),dfs4(u,u);
	Solve1::solve(u);
	Solve2::solve(u);
	Solve3::solve(u);
	// debug("root",u,ans);
	// if(u==9)exit(0);
	for(int v:to[u])if(!vis[v])solve(v);
}
int main(){
	freopen("sayaka.in","r",stdin);
	freopen("sayaka.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		to[u].push_back(v),to[v].push_back(u);
	}
	Tree::init();
	for(int u,v;m--;){
		scanf("%d%d",&u,&v);
		Tree::link(u,v);
	}
	for(int i=1;i<=n;i++){
		sort(tr[i].begin(),tr[i].end());
	}
	Tree::push1();
	Tree::push2();
	// debug("sum",ary(Tree::sum,1,n));
	if(!Tree::tot[1])puts("0"),exit(0);
	mx[0]=n+1,dep[0]=-1,solve(1);
	cout<<ans<<endl;
	return 0;
}
