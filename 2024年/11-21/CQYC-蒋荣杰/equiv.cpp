#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int n, dp[65][65], inv[105], lst[2][15];
LL res, m, gg[65], ans;

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1) 
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	read(n), read(res), read(m);
	if(n <= 5 && m <= 10) {//sub1
		// debug("sub1!\n");
		int now = 0;
		lst[0][1]=1;
		for(int i = 1; i <= n; ++i) {
			now^=1;
			for(int j = 0; j < m; ++j)
				lst[now][j]=0;
			for(int j = 0; j < m; ++j)
				if(lst[now^1][j])
					for(int k = 0; k < m; ++k)
						lst[now][j*k%m]=upd(lst[now][j*k%m]+lst[now^1][j]);
		}
		write(lst[now][res], '\n');
		return 0;
	}
	int p = -1, gs = 0;
	LL mm = m;
	for(int i = 2; 1LL*i*i <= mm; ++i)
		if(mm%i == 0) {
			while(mm%i == 0) mm/=i;
			p=i, ++gs;
		}
	if(gs == 0 && res == 0) {//sub2
		// debug("sub2!\n");
		write(upd(ksm(m%mod, n)-ksm((m-1)%mod, n)+mod), '\n');
		return 0;
	}
	if(gs == 1 && res == 0) {//sub3
		// debug("sub3!\n");
		int now = 0;
		LL pp = 1, ss = 0;
		while(m != pp)
			pp=1LL*pp*p, ++now, gg[now]=m/pp;
		for(int i = now; i >= 1; --i)
			gg[i]-=ss, ss+=gg[i];
		// for(int i = 1; i <= now; ++i)
		// 	debug(gg[i]), debug(' ');
		// debug('\n', m-ss, "???\n");
		dp[0][0]=1;
		for(int i = 0; i < now; ++i)
			for(int j = 0; j < now; ++j)
				for(int op = 1; op < now; ++op)
					if(i+op < now)
						dp[i+op][j+1]=upd(dp[i+op][j+1]+1LL*dp[i][j]*gg[op]%mod);
		ans=ksm(m%mod, n);
		inv[0]=inv[1]=1;
		for(int i = 2; i <= now; ++i)
			inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod;
		for(int j = 0, sss = 1; j < now; ++j) {
			for(int i = 0; i < now; ++i)
				ans=upd(ans-1LL*dp[i][j]*ksm((m-ss)%mod, n-j)%mod*sss%mod+mod);
			sss=1LL*sss*(n-j)%mod*inv[j+1]%mod;
		}
		write(ans, '\n');
		return 0;
	}
	return 0;
}