#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 3e5+5;
int t, n, cntt[5], az[5], jc[N], inv[N], inc[N], pw[N];
struct qwq {
	int a, b;
}p[N];

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
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*x*ret%mod;
		y=(y>>1);
		x=1LL*x*x%mod;
	}
	return ret;
}
int c(int x, int y) {
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}

signed main() {
	freopen("fraud.in", "r", stdin);
	freopen("fraud.out", "w", stdout);
	read(t);
	jc[0]=jc[1]=inv[0]=inv[1]=inc[0]=inc[1]=pw[0]=1;
	pw[1]=2;
	for(int i = 2; i <= 300000; ++i)
		jc[i]=1LL*jc[i-1]*i%mod, inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod, 
		pw[i]=upd(pw[i-1]+pw[i-1]);
	while(t--) {
		read(n);
		int ans = 0, cnt = 0;
		cntt[0]=cntt[1]=cntt[2]=cntt[3]=az[1]=az[2]=az[3]=az[0]=0;
		for(int i = 1; i <= n; ++i) {
			read(p[i].a), read(p[i].b);
			cnt+=(p[i].a == 0);
			cnt+=(p[i].b == 0);
			if(p[i].a == 0 && p[i].b == 0)
				++cntt[3];
			else
				if((p[i].a == 0 && p[i].b == 1) || (p[i].a == 1 && p[i].b == 0))
					++cntt[1];//AA
				else
					if((p[i].a == 0 && p[i].b == 2) || (p[i].a == 2 && p[i].b == 0))
						++cntt[2];//BB
			if(p[i].a && p[i].b)
				++az[((p[i].b-1)<<1)+(p[i].a-1)];
		}
		if(az[3] == 0 && az[0] == 0) {
			if(az[1] && az[2])
				ans=0;
			else
				ans=1;
		}
		for(int i = max(az[3], max(az[0], 1)); i <= n; ++i) 
			for(int j = 0; j <= cntt[3] && j <= i; ++j) //枚举分给AA多少个 
				for(int k = 0; j+k <= cntt[3] && k <= i; ++k) {//枚举分给BB多少个 
					if(i-j > cntt[1] || i-k > cntt[2]) continue;
					int x = c(cntt[1], i-j), y = c(cntt[2], i-k);
					ans=upd(ans+1LL*x*y%mod*pw[cntt[3]-j-k]%mod);
				}
		write(1LL*ans*ksm(pw[cnt], mod-2)%mod, '\n');
	}
	return 0;
}
