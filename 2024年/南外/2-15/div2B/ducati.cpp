#include <bits/stdc++.h>
#define int long long
#pragma GCC optimize("Ofast")
using namespace std;
const int maxl=20000005,mod=998244353;

int read(){
	int s=0,w=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-')  w=-w;ch=getchar();}
	while (ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+(ch^'0');ch=getchar();}
	return s*w;
}
int n,m,k,ans1,ans2;
int jc[maxl],inv[maxl],f[maxl];

namespace Math{
	int quick_power(int x,int y){
		int res=1;
		for (;y;y=y>>1,x=(x*x)%mod){
			if (y&1)  res=(res*x)%mod;
		}
		return res;
	}
	int ny(int tmpx){return quick_power(tmpx,mod-2);}
	void init(int n){
		jc[0]=1;
		for (int i=1;i<=n;i++)  jc[i]=(jc[i-1]*i)%mod;
		
		inv[n]=ny(jc[n]);
		for (int i=n-1;i>=0;i--)  inv[i]=(inv[i+1]*(i+1))%mod;
	}
	int C(int x,int y){
		if (x<0||y<0||x<y)  return 0;
		else return ((jc[x]*inv[y])%mod*inv[x-y])%mod;
	}
	int F(int x,int y){
		if (x==0&&y==0)  return 1;
		return C(x+y-1,y-1);
	}
	int calc(int tot,int cnt,int maxv){
		int res=0;
		for (int i=0;i<=min(cnt,tot/maxv);i++){
			int val=C(cnt,i)*F(tot-i*maxv,cnt);
			if (i&1)  res=(res+mod-val)%mod;
			else res=(res+val)%mod;
		}
		return res;
	}
}
namespace ducati{
	void work1(){
		for (int x=k;x<=m;x++)  ans1=(ans1+Math::F(m-x,n-1))%mod;
	}
	void work2(){
		ans2=(Math::F(m,n)-Math::calc(m,n,k)+mod)%mod;
		ans2=(ans2*Math::ny(n))%mod;
	}
	void solve(){
		n=read(),m=read(),k=read();Math::init(maxl-5);
		if (k==0){
			cout<<Math::ny(n)<<endl;
			return;
		}
		work1(),work2();
		cout<<(ans2*Math::ny(ans1))%mod;
	}
}

signed main(){
	freopen("probability.in","r",stdin);
	freopen("probability.out","w",stdout);

	ducati::solve();
	return 0;
}
