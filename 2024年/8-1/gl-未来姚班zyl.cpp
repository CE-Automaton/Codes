#include<bits/stdc++.h>
#define ll long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define Pi pair<int,int>
#define pb push_back
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N=1e5+6,inf=(1LL<<31)-1,mod=11417603;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1ll*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,m,fac[N],iv[N];
string opt;
inline int C(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return mul(fac[x],mul(iv[y],iv[x-y]));
}
inline int A(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return mul(fac[x],iv[x-y]);
}
int mxa[N],mxc[N],F[N<<3],T[N<<3],*f=F+200000,*t=T+200000,sm,Sm,t0=1,v0,Time=1,ex,fm1;
inline void Sol(int x){
	if(t[x]<t0)t[x]=t0,f[x]=v0;
}
inline void insert(int x,int k){
	Sol(x);
	t[x]=++Time,add(f[x],k),add(sm,k),add(Sm,mul(Red(x,1),k));
}
inline int Get(int x){
	Sol(x);
	return Add(ex,f[x]);
}
inline void Ins(int k){
	Time++,add(ex,k),add(sm,mul(m+1,k)),add(Sm,mul(1LL*(m+1)*(m-2)/2%mod,k));
}
inline void shift(){
	red(sm,Get(m)),red(Sm,mul(m-1,Get(m))),add(fm1,Get(m)),f--,t--;
	add(Sm,sm);
	t[0]=++Time,f[0]=Red(mod,ex);
}
inline void clear(){
	t0=++Time,v0=Red(mod,ex),sm=Sm=0;
} 
inline void prep(){
	fac[0]=1;
	rep(i,1,N-5)fac[i]=mul(fac[i-1],i);
	iv[N-5]=INV(fac[N-5]);
	per(i,N-6,0)iv[i]=mul(iv[i+1],i+1);
	rep(i,2,8)if(fac[i]<=m){
		mxa[i]=i;
		ll w=fac[i];
		while(1){
			ll nx=w*(mxa[i]+1)/(mxa[i]-i+1);
			if(nx>m)break;
			w=nx,mxa[i]++;
		}
	}
	rep(i,2,m){
		mxc[i]=i;
		ll w=1;
		while(1){
			ll nx=w*(mxc[i]+1)/(mxc[i]-i+1);
			if(nx>m)break;
			w=nx,mxc[i]++;
		}
	}
	repm(i)mxa[i]=min(mxa[i],m),mxc[i]=min(mxc[i],m);
}
inline int Sum(){
	return Add(Sm,Get(0));
}
vector<Pi>p;
signed main(){
	n=read(),m=read(),prep(),cin>>opt,opt='#'+opt;
	bool nw=0;
	repm(i)insert(i,1);
	rep(o,1,n-2){
		int k=Get(1);
		if(opt[o]=='A'){
			p.pb({0,Add(Sum(),mul(fm1,m))}),p.pb({1,mul(m,Get(0))});
			rep(i,2,min(8,m)){
				int w=Get(i);
				rep(j,i,mxa[i])p.pb({A(j,i),w});
			}
			clear();
		}else {
			p.pb({0,Add(Sum(),mul(fm1,m))}),p.pb({1,Add(sm,Red(mul(Red(m,2),Get(0)),Get(1)))}),p.pb({2,Red(mod,Get(1))});
			for(int i=2;mxc[i]>i+1;i++){
				int w=Get(i);
				rep(j,i+2,mxc[i])p.pb({C(j,i),w});
			}
			shift();
		}
		Ins(k),insert(0,Red(mod,k));
		for(auto x:p)insert(x.first,x.second);p.clear();
		fm1=Red(qp(m,o+1),sm);
	}
	int ans=mul(Get(0),m);
	add(ans,mul(Get(1),C(m+1,2)));
	if(opt[n-1]=='A')rep(i,2,m)add(ans,mul(Get(i),mul(fac[i],C(m+1,i+1))));
	else rep(i,2,m)add(ans,mul(Get(i),C(m+1,i+1)));
	cout <<ans;
	return 0;
}