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
const int N=5e5+10,mod=998244353;
int n,m,a[N],b[N];
vector<int>to[N];
int f[N][2];
void dfs(int u,int fa=0){
	if(b[u])f[u][0]=a[u],f[u][1]=1;
	else f[u][0]=1;
	for(int v:to[u])if(v^fa){
		dfs(v,u);
		debug(u,v,f[u][0],f[u][1]);
		int f0=f[u][0],f1=f[u][1];
		f[u][0]=(1ll*f0*f[v][0]-1ll*f1*f[v][1]%mod*a[u]%mod*a[u])%mod;
		f[u][1]=(1ll*f1*f[v][0]+1ll*f0*f[v][1]-2ll*f1*f[v][1]%mod*a[u])%mod;
	}
	debug(u,f[u][0],f[u][1]);
}
int main(){
	freopen("online.in","r",stdin);
	freopen("online.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int x;m--;){
		scanf("%d",&x);
		if(++b[x]>1)puts("0"),exit(0);
	}
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		to[u].push_back(v),to[v].push_back(u);
	}
	dfs(1);
	cout<<(f[1][0]+mod)%mod<<endl;
	return 0;
}
