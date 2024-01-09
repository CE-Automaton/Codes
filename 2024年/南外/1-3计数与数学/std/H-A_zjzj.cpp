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
const int N=121,mod=1e9+9;
int n,m;
ll k;
ll qpow(ll x,ll y=mod-2,ll ans=1){
	for(;y;(x*=x)%=mod,y>>=1)if(y&1)(ans*=x)%=mod;
	return ans;
}
const int w3=qpow(13,(mod-1)/3);
using matrix=array<array<int,N>,N>;
#ifdef DEBUG
ostream& operator << (ostream &out,array<int,N> a){
	out<<'[';
	for(int i=0;i<=n;i++)out<<a[i]<<',';
	return out<<']';
}
ostream& operator << (ostream &out,matrix a){
	out<<'[';
	for(int i=0;i<=n;i++)out<<a[i]<<',';
	return out<<']';
}
#endif
matrix a,b,C;
void DFT(const matrix &a,int op,matrix &b){
	for(int i=0;i<=n;i++)b[i].fill(0);
	static matrix f;
	auto mul=[&](int A,int B,int C){
		for(int i=n;i>=0;i--){
			for(int j=n-i;j>=0;j--){
				f[i][j]=(1ll*f[i][j]*C+(i?1ll*f[i-1][j]*A:0)+(j?1ll*f[i][j-1]*B:0))%mod;
			}
		}
	};
	auto div=[&](int A,int B,int C){
		int iC=qpow(C);
		for(int i=0;i<=n;i++){
			for(int j=0;i+j<=n;j++){
				f[i][j]=(f[i][j]+(i?1ll*f[i-1][j]*(mod-A):0)+(j?1ll*f[i][j-1]*(mod-B):0))%mod*iC%mod;
			}
		}
	};
	for(int i=0;i<=n;i++)f[i].fill(0);
	f[0][0]=1;
	int p1=0,p2=0,p3=0;
	auto jump=[&](int x,int y,int z){
		for(;p1>x;p1--)div(w3,1ll*w3*w3%mod,1);
		for(;p2>y;p2--)div(1ll*w3*w3%mod,w3,1);
		for(;p3>z;p3--)div(1,1,1);
		for(;p1<x;p1++)mul(w3,1ll*w3*w3%mod,1);
		for(;p2<y;p2++)mul(1ll*w3*w3%mod,w3,1);
		for(;p3<z;p3++)mul(1,1,1);
	};
	for(int i=0;i<=n;i++){
		if(i&1){
			for(int j=n-i;j>=0;j--){
				jump(i,j,n-i-j);
				// debug("f",p1,p2,p3,f);
				for(int x=0;x<=n;x++){
					for(int y=0;x+y<=n;y++){
						// if(a[x][y])debug(i,j,x,y,"f",f[x][y],"a",a[x][y]);
						b[i][j]=(b[i][j]+1ll*a[x][y]*f[x][y])%mod;
					}
				}
			}
		}else{
			for(int j=0;i+j<=n;j++){
				jump(i,j,n-i-j);
				// debug("f",p1,p2,p3,f);
				for(int x=0;x<=n;x++){
					for(int y=0;x+y<=n;y++){
						// if(a[x][y])debug(i,j,x,y,"f",f[x][y],"a",a[x][y]);
						b[i][j]=(b[i][j]+1ll*a[x][y]*f[x][y])%mod;
					}
				}
			}
		}
	}
	// debug("before",b);
	if(op<0){
		ll x=qpow(qpow(3,n));
		for(int i=0;i<=n;i++){
			for(int j=0;i+j<=n;j++){
				b[i][j]=b[i][j]*x%mod;
			}
		}
		for(int i=0;i<=n;i++){
			for(int j=i+1;i+j<=n;j++){
				swap(b[i][j],b[j][i]);
			}
		}
	}
	// debug("DFT",op);
	// debug(a);
	// debug(b);
}
int main(){
	freopen("machine.in","r",stdin);
	freopen("machine.out","w",stdout);
	// debug(w3,1ll*w3*w3%mod,1ll*w3*w3%mod*w3%mod);
	scanf("%d%d%lld",&n,&m,&k);
	for(int i=0;i<=n;i++){
		for(int j=C[i][0]=1;j<=i;j++){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
		}
	}
	for(int x,y;m--;){
		scanf("%d%d",&x,&y);
		a[x][y]++;
	}
	DFT(a,1,b);
	for(int i=0;i<=n;i++){
		for(int j=0;i+j<=n;j++){
			b[i][j]=qpow(b[i][j],k);
		}
	}
	DFT(b,-1,a);
	for(int i=0;i<=n;i++){
		for(int j=0;i+j<=n;j++){
			int res=1ll*a[i][j]*C[n][i]%mod*C[n-i][j]%mod;
			printf("%d%c",res,"\n "[i+j<n]);
		}
	}
	debug(1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}
