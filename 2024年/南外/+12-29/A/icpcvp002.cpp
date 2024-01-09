#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pii pair<int,int>
#define x first
#define y second
inline int read(){
	int x=0;bool f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    if(f)return x;return ~(x-1);
}
int n,m,a[500005];
ll ans;
vector<int> g[500005];
struct ST{
	vector<pii> t[2000005];
	int laz[2000005];
	void mdf(int p,int v){
		laz[p]+=v;
		for(int i=0;i<t[p].size();i++)t[p][i].x+=v;
	}
	void pushdown(int p){
		if(!laz[p])return;
		mdf(p<<1,laz[p]),mdf(p<<1|1,laz[p]);
		laz[p]=0;
	}
	void ins(int p,pii v){
		if(t[p].empty()||t[p].back().x!=v.x){
			if(t[p].size()<m)t[p].push_back(v);
		}
		else t[p][t[p].size()-1].y+=v.y;
	}
	void pushup(int p){
		t[p].clear();pii nw={0,0};
		int l1=t[p<<1].size(),l2=t[p<<1|1].size(),j=0;
		for(int i=0;i<l1;i++){
			while(j<l2&&t[p<<1|1][j].x<=t[p<<1][i].x){
				ins(p,t[p<<1|1][j]),++j;
			}
			ins(p,t[p<<1][i]);
		}
		while(j<l2)ins(p,t[p<<1|1][j]),++j;
	}
	void build(int p,int l,int r){
		if(l==r){
			t[p].push_back({-l+1,1});
			return;
		}
		int mid=l+r>>1;
		build(p<<1,l,mid),build(p<<1|1,mid+1,r);
		pushup(p);
	}
	void change(int p,int l,int r,int L,int R,int v){
		if(l<=L&&R<=r){
			mdf(p,v);return;
		}
		int mid=L+R>>1;pushdown(p);
		if(l<=mid)change(p<<1,l,r,L,mid,v);
		if(r>mid)change(p<<1|1,l,r,mid+1,R,v);
		pushup(p);
	}
	int ask(int p,int l,int r,int L,int R,int k){
		if(l<=L&&R<=r){
			int res=0;
			for(auto i:t[p])if(i.x+k<=m)res+=i.y;
			return res;
		}
		int mid=L+R>>1,ans=0;pushdown(p);
		if(l<=mid)ans+=ask(p<<1,l,r,L,mid,k);
		if(r>mid)ans+=ask(p<<1|1,l,r,mid+1,R,k);
		return ans;
	}
}t;
int main(){
	freopen("shovel.in","r",stdin);
	freopen("shovel.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		x=a[x],y=a[y];
		if(x<y)swap(x,y);
		g[x].push_back(y);
	}
	t.build(1,1,n);
	for(int i=1;i<=n;i++){
		for(auto j:g[i])t.change(1,1,j,1,n,-1);
		ans+=t.ask(1,1,i,1,n,i);
	}
	cout<<ans;
}
