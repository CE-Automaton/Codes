#include <bits/stdc++.h>
#define mod 1000000007
#define maxn 100005
#define N 2000000
using namespace std;
#define pc putchar
void put(int x,char suf=' ') {
		static char stk[40];int top=0;
		x<0?pc('-'),x=-x:0; while(x) stk[top++]=x%10,x/=10;
		!top?pc('0'),0:0; while(top--) pc(stk[top]+'0');
		pc(suf);
}
int Pow(int n,int x,int sp=1) { for(;x;n=1ll*n*n%mod,x>>=1) if(x&1) sp=1ll*sp*n%mod; return sp; }
int fac[2000005],finv[2000005];
int bin(int n,int m) { return (n<m||m<0) ? 0 : (1ll*fac[n]*finv[m]%mod*finv[n-m]%mod); }
int getv(int n,int m,int ty) { if(ty==0) return bin(n,m); else return bin(n+m-1,m); }
int n,m,a[maxn];
bool comp(int x,int y,int ty) {
	if(x==-1||y==-1) return 1;
	if(ty==0) return x<y; if(ty==1) return x>y; if(ty==2) return x<=y; return x>=y;
}
struct node {
	int le,lv,rv;
	int r[4];
	struct seg {
		int l,r,lv,rv; seg(){l=r=lv=rv=-1;}
		seg rev(int L) { if(l==-1) return *this; seg u=*this; swap(u.lv,u.rv),u.l=L-r+1,u.r=L-l+1; return u; }
		friend bool operator != (const seg &x,const seg &y) { return x.l!=y.l||x.r!=y.r; }
	} L,R;
	node(){le=r[0]=r[1]=r[2]=r[3]=0;L.l=L.r=L.lv=L.rv=R.l=R.r=R.lv=R.rv=lv=rv=-1;}
	node(int x) {
		le=1,lv=rv=x,r[0]=r[1]=r[2]=r[3]=1;
		if(x==-1) L.l=L.r=R.l=R.r=1; else L.l=L.r=R.l=R.r=-1;
		L.lv=L.rv=R.lv=R.rv=-1;
	}
	friend node operator + (node x,node y) {
		if(x.le==0) return y; if(y.le==0) return x;
		node u; u.le=x.le+y.le; if(y.L.l!=-1) y.L.l+=x.le,y.L.r+=x.le,y.R.l+=x.le,y.R.r+=x.le;
		u.lv=(x.lv==-1)?y.lv:x.lv,u.rv=(y.rv==-1)?x.rv:y.rv;
		for(int i=0;i<4;i++) u.r[i]=1ll*x.r[i]*y.r[i]%mod*comp(x.rv,y.lv,i);
		if(x.L.l!=-1&&x.L.rv==-1) x.L.rv=y.lv; if(x.R.l!=-1&&x.R.rv==-1) x.R.rv=y.lv;
		if(y.L.l!=-1&&y.L.lv==-1) y.L.lv=x.rv; if(y.R.l!=-1&&y.R.lv==-1) y.R.lv=x.rv;
		seg ml,mr; u.L=x.L,u.R=y.R; if(x.R!=x.L) ml=x.R; if(y.L!=y.R) mr=y.L;
		if(u.R.l==-1) u.R=x.R,ml=seg(); if(u.L.l==-1) u.L=y.L,mr=seg();
		if(ml.r+1==mr.l) ml.r=mr.r,ml.rv=mr.rv,mr=seg();
		if(u.L.r+1==u.R.l) u.L.r=u.R.r,u.L.rv=u.R.rv,u.R=u.L;
		if(u.L.r+1==mr.l) u.L.r=mr.r,u.L.rv=mr.rv,mr=seg();
		if(ml.r+1==u.R.l) u.R.l=ml.l,u.R.lv=ml.lv,ml=seg();
		if(ml.l!=-1) for(int i=0;i<4;i++) u.r[i]=1ll*u.r[i]*getv(abs(ml.rv-ml.lv)+((i>>1)?1:(-1)),ml.r-ml.l+1,i>>1)%mod;
		if(mr.l!=-1) for(int i=0;i<4;i++) u.r[i]=1ll*u.r[i]*getv(abs(mr.rv-mr.lv)+((i>>1)?1:(-1)),mr.r-mr.l+1,i>>1)%mod;
		return u;
	}
	node reverse() {
		if(le==0) return *this;
		node u=*this; swap(u.lv,u.rv); u.L=R.rev(u.le); u.R=L.rev(u.le);
		swap(u.r[0],u.r[1]),swap(u.r[2],u.r[3]);
		return u;
	}
}tr[maxn<<2];
vector<int>e[maxn];
int fa[maxn],sz[maxn],dp[maxn],sn[maxn],tp[maxn],dt[maxn],re[maxn],dft;
void dfs1(int u,int fat) {
	dp[u]=dp[fa[u]=fat]+1,sz[u]=1;
	for(int v:e[u]) if(v^fat) dfs1(v,u),sz[u]+=sz[v],sn[u]=(sz[sn[u]]<sz[v])?v:sn[u];
}
void dfs2(int u,int top) {
	tp[u]=top; re[dt[u]=++dft]=u; if(sn[u]) dfs2(sn[u],top);
	for(int v:e[u]) if(v^fa[u]&&v^sn[u]) dfs2(v,v);
}
void build(int k,int l,int r) {
	if(l==r) { tr[k]=node(a[re[l]]); return ; } int mid=l+r>>1;
	build(k<<1,l,mid),build(k<<1|1,mid+1,r); tr[k]=tr[k<<1]+tr[k<<1|1];
}
void mdf(int k,int l,int r,int p,int v) {
	if(l==r) { tr[k]=node(v); return ; } int mid=l+r>>1;
	if(p<=mid) mdf(k<<1,l,mid,p,v); else mdf(k<<1|1,mid+1,r,p,v); tr[k]=tr[k<<1]+tr[k<<1|1];
}
node qry(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return tr[k]; int mid=l+r>>1;
	if(y<=mid) return qry(k<<1,l,mid,x,y); if(x>mid) return qry(k<<1|1,mid+1,r,x,y);
	return qry(k<<1,l,mid,x,y)+qry(k<<1|1,mid+1,r,x,y);
}
node get(int u,int v) {
	node r[2]; bool f=0;
	for(;tp[u]^tp[v];r[0]=qry(1,1,n,dt[tp[u]],dt[u])+r[0],u=fa[tp[u]]) if(dp[tp[u]]<dp[tp[v]]) f^=1,swap(r[0],r[1]),swap(u,v);
	if(dp[u]<dp[v]) swap(u,v),f^=1,swap(r[0],r[1]); r[0]=qry(1,1,n,dt[v],dt[u])+r[0]; if(f) swap(r[0],r[1]);
	return r[0].reverse()+r[1];
}
int calc(node r,int ty,int A,int B) {
	int ans=r.r[ty],_l,_r,vl; if(ty<2) A--,B++;
	if(r.L.l!=-1) {
		auto _=r.L;
		if(ty&1) swap(_.lv,_.rv); if(_.lv==-1) _l=A; else _l=max(_.lv,A); if(_.rv==-1) _r=B; else _r=min(_.rv,B);
		ans=1ll*ans*getv(_r-_l+((ty>>1)?1:(-1)),_.r-_.l+1,ty>>1)%mod;
		if(r.L!=r.R) {
			_=r.R;
			if(ty&1) swap(_.lv,_.rv); if(_.lv==-1) _l=A; else _l=max(_.lv,A); if(_.rv==-1) _r=B; else _r=min(_.rv,B);
			ans=1ll*ans*getv(_r-_l+((ty>>1)?1:(-1)),_.r-_.l+1,ty>>1)%mod;
		}
	} return ans;
}
int main() {
	freopen("ynycoding.in","r",stdin);
	freopen("ynycoding.out","w",stdout);
	for(int i=fac[0]=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	finv[N]=Pow(fac[N],mod-2); for(int i=N;i;i--) finv[i-1]=1ll*finv[i]*i%mod;
	scanf("%d",&n),scanf("%d",&m); for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int u,v,i=1;i<n;i++,e[u].emplace_back(v),e[v].emplace_back(u)) scanf("%d",&u),scanf("%d",&v);
	dfs1(1,0),dfs2(1,1); build(1,1,n);
	char opt[20];
	for(int x,y,a,b;m--;) {
		scanf("%s %d %d",opt,&x,&y);
		if(opt[0]=='U') mdf(1,1,n,dt[x],y);
		else scanf("%d %d",&a,&b),put(calc(get(x,y),((opt[0]=='N')?(opt[4]=='D'?2:3):(opt[0]=='I'?0:1)),a,b),'\n');
	}
}
