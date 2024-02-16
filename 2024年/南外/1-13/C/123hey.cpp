#include<bits/stdc++.h>
#define For(a,b,c) for(int a=b;a<=c;++a)
#define Dor(a,b,c) for(int a=b;a>=c;--a)
using namespace std;
bool m1;
const int N=1000007;
int n,m,X[N],Y[N];
void rd(int &x) {
	x=0; char c=getchar(); int f=0;
	while(!isdigit(c)) {if(c=='-') f=1; c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;
}
namespace P1 {
	int a,b,c,d,e,hd[N],nt[N<<1],to[N<<1],D[N],V[N];
	void fly(int u) {
		if(V[u]) return;
		V[u]=1;
		if(D[u]==0) ++d;
		if(D[u]==1) ++a;
		if(D[u]==2) ++b;
		if(D[u]>=3) ++c;
		for(int i=hd[u];i;i=nt[i]) fly(to[i]);
	}
	int UFO(int x) {
		For(i,1,n) V[i]=0; V[x]=1;
		For(i,1,n)
		if(!V[i]) {
			a=b=c=d=0;
			fly(i);
			if(c) return 0;
			if(d) continue;
			if(a!=2) return 0;
		}
		return 1;
	}
	int cool(int x) {
		for(int i=hd[x];i;i=nt[i]) --D[to[i]];
		int r=UFO(x);
		for(int i=hd[x];i;i=nt[i]) ++D[to[i]];
		return r;
	}
	int qry() {
		For(i,1,n)
		if(D[i]>=4) return cool(i);
		For(i,1,n)
		if(D[i]==3) {
			int r=cool(i);
			for(int e=hd[i];e;e=nt[e])
				r+=cool(to[e]);
			return r;
		}
		For(i,1,n) V[i]=0;
		int r=n,f=0;
		For(i,1,n)
		if(!V[i]) {
			a=b=c=d=0;
			fly(i);
			if(d||a==2) continue;
			if(f) return 0;
			f=1,r=b;
		}
		return r;
	}
	void sol() {
		For(i,1,m) {
			int x=X[i],y;
			if(x==-1) printf("%d\n",qry());
			else {
				y=Y[i],++x,++y,++D[x],++D[y];
				nt[++e]=hd[x],hd[x]=e,to[e]=y;
				nt[++e]=hd[y],hd[y]=e,to[e]=x;
			}
		}
	}
}
namespace P2 {
	int t,e,D[N],C[N],sz[N],hd[N],nt[N<<1],to[N<<1];
	int fi(int u) {
		return u==C[u]?u:C[u]=fi(C[u]);
	}
	struct sky {
		int king,gg,C[N],D[N];
		int fi(int u) {
			return u==C[u]?u:C[u]=fi(C[u]);
		}
		void eat(int x,int y) {
			if(gg) return;
			if(x==king||y==king) return;
			++D[x],++D[y];
			if(D[x]>2||D[y]>2) gg=1;
			x=fi(x),y=fi(y);
			if(x==y) gg=1;
			else C[x]=y;
		}
		void mk(int u,int s) {
			king=u,gg=0;
			For(i,1,n) C[i]=i,D[i]=0;
			For(i,1,s-1) {
				if(X[i]==-1) continue;
				eat(X[i]+1,Y[i]+1);
			}
		}
		int qry() {
			return !gg;
		}
	}G[4];
	void upd(int u,int s) {
		if(D[u]>=4) {
			if(t==1&&G[0].king!=u) {
				For(i,s,m)
				if(X[i]==-1) puts("0");
				exit(0);
			}
			if(t==1) return;
			t=1;
			G[0].mk(u,s);
		}
		if(D[u]>=3) {
			if(t) return;
			G[0].mk(u,s);
			t=1;
			for(int i=hd[u];i;i=nt[i]) {
				G[t].mk(to[i],s);
				++t;
			}
		}
	}
	void sol() {
		int fish=0;
		For(i,1,n) C[i]=i,sz[i]=1;
		For(i,1,m) {
			if(X[i]==-1) {
				if(t) {
					int r=0;
					For(i,0,t-1) r+=G[i].qry();
					printf("%d\n",r);
				}
				else {
					if(!fish) printf("%d\n",n);
					else printf("%d\n",sz[fish]);
				}
			}
			else {
				int x=X[i]+1,y=Y[i]+1;
				++D[x],++D[y];
				nt[++e]=hd[x],hd[x]=e,to[e]=y;
				nt[++e]=hd[y],hd[y]=e,to[e]=x;
				upd(x,i),upd(y,i);
				For(j,0,t-1) G[j].eat(x,y);
				x=fi(x),y=fi(y);
				if(x!=y) C[x]=y,sz[y]+=sz[x];
				else {
					if(fish&&fi(fish)!=fi(x)) {
						For(j,i,m)
						if(X[j]==-1) puts("0");
						return;
					}
					fish=x;
				}
			}
		}
	}
}
bool m2;
int main() {
//	cerr<<(&m2-&m1)/1048576.<<"MB"<<endl;
	freopen("rings.in","r",stdin);
	freopen("rings.out","w",stdout);
	scanf("%d%d",&n,&m);
	int F1=0;
	For(i,1,m) {
		rd(X[i]);
		if(X[i]==-1) ++F1;
		else rd(Y[i]);
	}
	if(1LL*F1*n<=2000000) P1::sol();
	else P2::sol();
	return 0;
}
