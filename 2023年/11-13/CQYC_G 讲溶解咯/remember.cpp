#include <bits/stdc++.h>
#define mod 147744151
using namespace std;
const int N = 2e3+5;
int t, n, a, jzhan[N], jj, ozhan[N], oo, zf[N]/*每个数奇位减偶位的值*/, ou[N][15]/*偶串正选i,和为j的方案数*/,
ji[N][15]/*奇串正选i,和为j的方案数*/, d[N][15], sum[15], jc[N], c[N][N], ans;

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x, char ch) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(ch);
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("remember.in", "r", stdin);
	freopen("remember.out", "w", stdout);
	read(t);
	jc[0]=jc[1]=1;
	for(int i = 2; i <= 2000; ++i)
		jc[i]=1LL*i*jc[i-1]%mod;
	for(int i = 0; i <= 2000; ++i)
		c[i][0]=1;
	for(int i = 1; i <= 2000; ++i)
		for(int j = 1; j <= i; ++j)
			c[i][j]=upd(c[i-1][j-1]+c[i-1][j]);
	while(t--) {
		read(n);
		jj=oo=ans=0;
		memset(ou, 0, sizeof ou);
		memset(ji, 0, sizeof ji);
		for(int i = 1; i <= n; ++i) {
			zf[i]=0;
			read(a);
			int gs = 0, now = 1;
			do { zf[i]+=now*(a%10), gs^=1, now=-now, a/=10; } while(a);
			if(gs)
				jzhan[++jj]=i;
			else
				ozhan[++oo]=i;
			zf[i]%=11;
			zf[i]=(zf[i]+22)%11;
		}
		ji[0][0]=1;
		for(int i = 1; i <= jj; ++i) {
			int now = jzhan[i];
			for(int ls = 0; ls <= i-1; ++ls)
				for(int lt = 0; lt <= 10; ++lt)
					d[ls][lt]=ji[ls][lt], ji[ls][lt]=0;
			for(int ls = 0; ls <= i-1; ++ls)
				for(int lt = 0; lt <= 10; ++lt)
					ji[ls+1][(lt+zf[now])%11]=d[ls][lt];
			for(int ls = 0; ls <= i-1; ++ls)
				for(int lt = 0; lt <= 10; ++lt)
					ji[ls][(lt-zf[now]+22)%11]=upd(ji[ls][(lt-zf[now]+22)%11]+d[ls][lt]);
		}
		ou[0][0]=1;
		for(int i = 1; i <= oo; ++i) {
			int now = ozhan[i];
			for(int ls = 0; ls <= i-1; ++ls)
				for(int lt = 0; lt <= 10; ++lt)
					d[ls][lt]=ou[ls][lt], ou[ls][lt]=0;
			for(int ls = 0; ls <= i-1; ++ls)
				for(int lt = 0; lt <= 10; ++lt)
					ou[ls+1][(lt+zf[now])%11]=d[ls][lt];
			for(int ls = 0; ls <= i-1; ++ls)
				for(int lt = 0; lt <= 10; ++lt)
					ou[ls][(lt-zf[now]+22)%11]=upd(ou[ls][(lt-zf[now]+22)%11]+d[ls][lt]);
		}
		if(jj == 0) {//没有奇数特判一下 
			write(1LL*ou[oo][0]*jc[oo]%mod, '\n');
			continue;
		}
		for(int j = 0; j <= 10; ++j)
			sum[j]=0;
		for(int i = 0; i <= oo; ++i) 
			for(int j = 0; j <= 10; ++j) 
				sum[j]=upd(sum[j]+1LL*c[i+jj/2][jj/2]*jc[i]%mod*c[oo-i+(jj+1)/2-1][(jj+1)/2-1]%mod*jc[oo-i]%mod*ou[i][j]%mod);
		int zgs = (jj+1)/2;
		for(int j = 0; j <= 10; ++j) 
			ans=upd(ans+1LL*sum[(22-j)%11]*jc[zgs]%mod*jc[jj-zgs]%mod*ji[zgs][j]%mod);
		write(ans, '\n');
	}
	return 0;
}
