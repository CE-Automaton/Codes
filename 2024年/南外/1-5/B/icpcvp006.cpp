#include<bits/stdc++.h>
using namespace std;
using ll=long long;
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
const int N=5e5+10;
int n,m,a[N],b[N];
int kk=1,head[N],ans[N];
struct edges{
	int to,id,nex;
}edge[N*2];
int deg[N],in[N],out[N];
void add(int u,int v,int id){
	deg[u]++,deg[v]++;
	edge[++kk]={v,id,head[u]},head[u]=kk;
	edge[++kk]={u,id,head[v]},head[v]=kk;
}
void cover(int i){
	in[edge[i].to]++,out[edge[i^1].to]++;
	if(i%2==0)ans[edge[i].id]=1;
	else ans[edge[i].id]=0;
}
void topo(){
	queue<int>q;
	for(int i=1;i<=n;i++){
		if(deg[i]==1&&(in[i]<a[i]||out[i]<b[i]))q.push(i);
	}
	for(int u;!q.empty();){
		u=q.front(),q.pop();
		for(int i=head[u];i;i=edge[i].nex){
			int v=edge[i].to;
			if(~ans[edge[i].id])continue;
			if(in[u]<a[u])cover(i^1);
			else cover(i);
			if(--deg[v]==1&&(in[v]<a[v]||out[v]<b[v]))q.push(v);
		}
	}
}
int dep[N],vis[N];
void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i;i=edge[i].nex){
		int v=edge[i].to;
		if(~ans[edge[i].id])continue;
		if(!vis[v])cover(i),dep[v]=dep[u]+1,dfs(v);
		else if(dep[u]>dep[v])cover(i);
	}
}
int main(){
	freopen("degree.in","r",stdin);
	freopen("degree.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	for(int u,v,i=1;i<=m;i++){
		scanf("%d%d",&u,&v),add(u,v,i);
	}
	fill(ans+1,ans+1+m,-1);
	topo();
	for(int i=1;i<=n;i++)if(!vis[i])dfs(i);
	for(int i=1;i<=n;i++){
		if(in[i]<a[i]||out[i]<b[i])cout<<-1<<endl,exit(0);
	}
	for(int i=1;i<=m;i++)printf("%d%c",!!ans[i],"\n "[i<m]);
	return 0;
}
