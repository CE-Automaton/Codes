#include <bits/stdc++.h>
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#define S cerr << "SYT AK IOI" <<endl;
#define M cerr << "MKF AK IOI" <<endl;
#define CONNECT_BASE(x,y) x##y
#define CONNECT(x,y) CONNECT_BASE(x,y)
#define DEBUG_BASE(x) cerr<<#x<<'='<<x<<' '
#define DEB_1(x) DEBUG_BASE(x)
#define DEB_2(x,y) DEB_1(x),DEB_1(y)
#define DEB_3(x,y,z) DEB_1(x),DEB_2(y,z)
#define DEB_4(x,y,z,w) DEB_1(x),DEB_3(y,z,w)
#define DEB_5(a,b,c,d,e) DEB_1(a),DEB_4(b,c,d,e)
#define DEB_6(a,b,c,d,e,f) DEB_1(a),DEB_5(b,c,d,e,f)
#define COUNT_BASE(_1,_2,_3,_4,_5,_6,x,...) x
#define COUNT(...) COUNT_BASE(__VA_ARGS__,6,5,4,3,2,1,0)
#define D(...) std::cerr << "[In Line " << __LINE__ << "]: ",CONNECT(DEB_,COUNT(__VA_ARGS__))(__VA_ARGS__) , cerr << '\n'

using namespace std;
int n,q,k;
const int N=1e5+5;
const int mod=1e9+7;
struct Martix{
	int a[9][9];
	int *operator [](int x){
		return a[x];
	}
	Martix(){
		memset(a,0,sizeof(a));
	}
	void reset(){
		memset(a,0,sizeof(a));
	}
	Martix operator *(Martix &b){
		Martix c;
		for(int i=0;i<=k;i++){
			for(int j=0;j<=k;j++){
				if(!a[i][j])continue;
				for(int K=0;K<=k;K++){
					if(b[j][K])
					c[i][K]=(c[i][K]+1ll*a[i][j]*b[j][K])%mod;
				}
			}
		}
		return c;
	}
}ans;
int A[N];Martix a[N<<2];
namespace SGT{

	inline void build(int p,int l,int r){
		if(l==r){
			for(int i=0;i<=k;i++){
				if(i)a[p][0][i]=A[l];
				else a[p][0][0]=1;
				for(int j=1;j<=i;j++)a[p][j][i]=1;
			}
			return;
		}
		int mid=(l+r)>>1;
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
		a[p]=a[p<<1]*a[p<<1|1];
	}
	inline void up(int p,int pos,int kkk,int L,int R){
		
		if(L==R){
			for(int i=1;i<=k;i++)(a[p][0][i]+=kkk)%=mod;
			return;
		}
		int mid=(L+R)>>1;
		if(mid>=pos)up(p<<1,pos,kkk,L,mid);
		else up(p<<1|1,pos,kkk,mid+1,R);
		a[p]=a[p<<1]*a[p<<1|1];
	}
	inline void query(int p,int l,int r,int L,int R){
		if(L>=l and R<=r){
			Martix c;
			for(int j=0;j<=k;j++)
				for(int K=0;K<=k;K++)
					c[0][K]=(c[0][K]+1ll*ans[0][j]*a[p][j][K])%mod;
			swap(ans,c);
			return;
		}
		int mid=(L+R)>>1;
		if(mid>=l)query(p<<1,l,r,L,mid);
		if(mid<r)query(p<<1|1,l,r,mid+1,R);
		return;
	}
}
using namespace SGT;
int main(){
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>q>>k;
	for(int i=1;i<=n;i++)cin>>A[i];
	build(1,1,n);
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int pos,k;
			cin>>pos>>k;
			//			D(pos,k);
			up(1,pos,k,1,n);
		}
		else {
			for(int i=1;i<=k;i++)ans[0][i]=0;
			ans[0][0]=1;
			int l,r;
			cin>>l>>r;
			query(1,l,r,1,n);
			cout<<ans[0][k]<<'\n';
		}
	}
	return 0;
}
