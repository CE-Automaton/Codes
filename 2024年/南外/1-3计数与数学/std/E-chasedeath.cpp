#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair <int,int> Pii;
#define reg register
#define mp make_pair
#define pb push_back
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
template <class T> inline void cmin(T &a,T b){ ((a>b)&&(a=b)); }
template <class T> inline void cmax(T &a,T b){ ((a<b)&&(a=b)); }

char IO;
template <class T=int> T rd(){
	T s=0; int f=0;
	while(!isdigit(IO=getchar())) f|=IO=='-';
	do s=(s<<1)+(s<<3)+(IO^'0');
	while(isdigit(IO=getchar()));
	return f?-s:s;
}

const int N=510,INF=1e9+10;
const int P=1e9+7;
bool Mbe;

int n,m;
int C[N][N],W[N][N],IW[N][N],D[N][N],J[N],I[N];
ll qpow(ll x,ll k=P-2) {
	ll res=1;
	for(;k;k>>=1,x=x*x%P) if(k&1) res=res*x%P;
	return res;
}

int G[N],H[N],T[N][N],R[N][N],S[N][N],U[N][N],V[N][N];
int Div(int a,int b){
	if(!b) return !a;
	return C[a+b-1][b-1];
}

ull Q[N],F[N];
int c=0;
const int E=17;

void Double(int T[N][N],int R[N][N]){
	rep(i,1,n/2) {
		rep(j,1,n/2) Q[j]=0;
		rep(j,1,n/2) {
			rep(k,1,n/2) Q[k]+=(ull)T[i][j]*T[j][k];
			if(j%E==0) rep(k,1,n/2) Q[k]%=P;
		}
		rep(j,1,n/2) R[i][j]=Q[j]%P;
	}
}

void Mul(int U[N][N]){
	rep(i,0,n/2) Q[i]=0;
	rep(i,1,n/2) {
		rep(j,1,n/2) Q[j]+=U[i][j]*F[i];
		if(i%E==0) rep(j,1,n/2) Q[j]%=P;
	}
	rep(i,1,n/2) F[i]=Q[i]%P;
}

void Solve() {
	rep(i,0,n) rep(j,*C[i]=1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
	rep(i,*J=1,n) J[i]=1ll*J[i-1]*i%P;
	I[n]=qpow(J[n]);
	drep(i,n,1) I[i-1]=1ll*I[i]*i%P;
	rep(i,**D=1,n) {
		rep(j,1,i) D[i][j]=1ll*J[i]*C[i-1][i-j]%P*I[j]%P;
		D[i][0]=J[i-1];
	}
	rep(i,**W=1,n) {
		rep(j,0,i/2) {
			W[i][j]=1ll*C[i][j*2]*J[j*2]%P*I[j]%P;
		}
	}

	rep(i,0,n/2) rep(j,0,n/2) T[i][j]=0;
	rep(i,0,n/2) F[i]=G[i]=H[i]=0;
	rep(i,1,n/2) F[i]=1ll*W[n][i]*Div(n-i*2,i)%P*J[n-i*2]%P;
	rep(i,1,n/2) {
		int cc=n-i*2;
		rep(j,0,n/2) Q[j]=0;
		for(int d=0;d<=cc;d+=E){
			for(int c=d;c<d+E && c<=cc;c++) {
				int t=cc-c;
				ull w=C[cc][c];
				if(t&1) w=P-w;
				rep(j,t+1,n/2) Q[j]+=D[i+c][j-t]*w;
				//if(t&1) rep(j,t+1,n/2) T[i][j]=(T[i][j]-1ll*D[i+c][j-t]*C[cc][c])%P;
				//else rep(j,t+1,n/2) T[i][j]=(T[i][j]+1ll*D[i+c][j-t]*C[cc][c])%P;
			}
			rep(j,0,n/2) Q[j]%=P;
		}
		rep(j,1,n/2) T[i][j]=Q[j]%P;
	}
	Double(T,R),Double(R,S),Double(S,U),Double(U,V);
	m-=2;
	rep(i,1,m/16) m-=16,Mul(V);
	rep(i,1,m/8) m-=8,Mul(U);
	rep(i,1,m/4) m-=4,Mul(S);
	rep(i,1,m/2) m-=2,Mul(R);
	rep(i,1,m) m--,Mul(T);
	int ans=0;
	rep(i,1,n/2) ans=(ans+J[n-i-1]*F[i])%P;
	printf("%d\n",ans);
}

bool Med;
int main(){
	fprintf(stderr,"%.2lf\n",(&Med-&Mbe)/1024./1024.0);
	freopen("graph.in","r",stdin),freopen("graph.out","w",stdout);
	rep(_,1,rd()) n=rd(),m=rd(),Solve();
}

