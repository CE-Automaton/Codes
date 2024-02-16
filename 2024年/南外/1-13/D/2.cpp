#include <bits/stdc++.h>
using namespace std;
inline int read(){
	char c;int f=1,res=0;
	while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
const int N=5e5+5;
int n,m,f0[N],f1[N],a[N],b[N];
set<int> p[N];
inline void init(){
	sort(b+1,b+1+n);
	int t=unique(b+1,b+1+n)-(b+1);
	for(int i=1;i<=n;++i){
		a[i]=lower_bound(b+1,b+1+t,a[i])-b;
		p[a[i]].insert(i);
	}
}
struct dat{int a,b,c,ca,cb,u,v;}d[N<<2];
int ch[N<<2][2],rt,tot;
inline dat operator+(dat x,dat y){
	if(!x.c)return y;
	if(!y.c)return x;
	dat z={max(x.a,y.a),max(x.b,y.b),max(x.c,y.c),0,0,N,0};
	if(x.c==z.c){
		z.ca=x.ca;z.cb=x.cb;
		z.u=x.u;z.v=x.v;
	}else{
		z.a=max(z.a,x.ca);
		z.b=max(z.b,x.cb);
	}
	if(y.c==z.c){
		z.u=min(z.u,y.u);
		z.v=max(z.v,y.v);
		z.ca=max(z.ca,y.ca);
		z.cb=max(z.cb,y.cb);
	}else{
		z.a=max(z.a,y.ca);
		z.b=max(z.b,y.cb);
	}return z;
}
#define lc ch[x][0],l,mid
#define rc ch[x][1],mid+1,r
void build(int &x=rt,int l=1,int r=n){
	x=++tot;
	if(l==r){
		d[x]={0,0,a[l],f0[l],f1[l],l,l};
		return;	
	}int mid=l+r>>1;
	build(lc);build(rc);
	d[x]=d[ch[x][0]]+d[ch[x][1]];
}
dat ask(int lp,int rp,int x=rt,int l=1,int r=n){
	if(l>rp||r<lp)return {0,0,0,0,0,N,0};
	if(lp<=l&&r<=rp)return d[x];
	int mid=l+r>>1;
	return ask(lp,rp,lc)+ask(lp,rp,rc);
}
int st[N],tp;
inline void solve0(){
	for(int i=1;i<=n;++i){
		while(tp&&a[st[tp]]<=a[i])--tp;
		int u=*p[a[i]].upper_bound(st[tp]);
		f0[i]=i-u+1;st[++tp]=i;
	}st[tp=1]=n+1;a[n+1]=N;
	for(int i=n;i>=1;--i){
		while(tp&&a[st[tp]]<=a[i])--tp;
		int u=*(--p[a[i]].upper_bound(st[tp]));
		f1[i]=u-i+1;st[++tp]=i;
	}
}
int main(){
	freopen("spiral.in","r",stdin);
	freopen("spiral.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;++i)
		a[i]=b[i]=read();
	init();solve0();build();
	while(m--){
		int l=read(),r=read();
		dat d=ask(l,r);int c=d.c,u=d.u,v=d.v;
		dat x=ask(l,u-1),y=ask(u+1,r),z={0,0,c,0,0,N,0};
		int ans=max((x+z).b,(y+z).a);
		ans=max(ans,v-u+1);printf("%d\n",ans);
	}return 0;
}
