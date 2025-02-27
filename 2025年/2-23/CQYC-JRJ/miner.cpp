#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, l, k, d, xx[N], dp[(1<<13)][14], z, u, p, aa, pd[N], cnt[(1<<13)], nr[N];

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
void sol(int st) {
	int ans = inf;
	for(int i = 0; i < (1<<l); ++i)
		for(int j = 1; j <= n; ++j)
			dp[i][j]=inf;
	for(int j = 1; j <= n; ++j)
		if(!pd[j])
			dp[((1<<l)-1)][j]=abs(st-xx[j]);
	for(int i = (1<<l)-1; i > 0; --i) 
		for(int j = 1; j <= n; ++j) 
			if(dp[i][j] != inf) {
				for(int kk = 0; kk <= l; ++kk)
					if(kk != xx[j]) {
						int x = xx[j], y = kk, zz = 0;
						if(x > y) swap(x, y);
						zz=(((1<<y)-(1<<x))&i);
						if(cnt[zz] > k) continue;
						if(i == zz)
							ans=min(ans, dp[i][j]+abs(xx[j]-kk));
						else
							for(int o = 1; o <= n; ++o)
								if(!pd[o])
									dp[i^zz][o]=min(dp[i^zz][o], dp[i][j]+abs(xx[j]-kk)+abs(xx[o]-kk));
					}
			}
	// for(int i = (1<<l)-1; i > 0; --i) 
	// 	for(int j = 1; j <= n; ++j) {
	// 		for(int o = 0; o < l; ++o)
	// 			debug((i>>o)&1);
	// 		debug("", j, dp[i][j], "!?\n");
	// 	}
	write(ans, '\n');
}
void soll(int st) {
	xx[0]=inf;
	for(int i = 0; i <= l; ++i)
		nr[i]=0;
	for(int j = 1; j <= n; ++j)
		if(!pd[j]) 
			for(int i = 0; i <= l; ++i)
				if(abs(xx[nr[i]]-i) > abs(xx[j]-i))
					nr[i]=j;
	int ans = inf;
	for(int j = 1; j <= n; ++j)
		if(!pd[j]) {
			int all = abs(st-xx[j]), ls = xx[j];
			for(int i = xx[j]-1; i >= 0; --i) {
				if(ls > i)
					all+=ls-i+abs(i-xx[nr[i]]), ls=xx[nr[i]];
				else
					all+=i+1-ls+abs(i+1-xx[nr[i]]), ls=xx[nr[i]];
			}
			for(int i = xx[j]; i < l; ++i) {
				if(ls > i)
					all+=ls-i+abs(i-xx[nr[i]]), ls=xx[nr[i]];
				else
					all+=i+1-ls+abs(i+1-xx[nr[i]]), ls=xx[nr[i]];
			}
			ans=min(ans, all);
		}
	write(ans, '\n');
}

signed main() {
	File("miner");
	read(n), read(l), read(k), read(d);
	for(int i = 1; i <= n; ++i)
		read(xx[i]);
	if(l <= 12 && d <= 50) {
		cnt[0]=0;
		for(int i = 0; (i<<1) < (1<<l); ++i)
			cnt[i<<1]=cnt[i], cnt[(i<<1)|1]=cnt[i]+1;
		for(int i = 1; i <= d; ++i) {
			read(z), read(u), read(p);
			for(int j = 1; j <= z; ++j)
				read(aa), pd[aa]=0;
			for(int j = 1; j <= u; ++j)
				read(aa), pd[aa]=1;
			sol(p);
		}
		return 0;
	}
	if(l <= 500 && d <= 50 && k == 1) {
		for(int i = 1; i <= d; ++i) {
			read(z), read(u), read(p);
			for(int j = 1; j <= z; ++j)
				read(aa), pd[aa]=0;
			for(int j = 1; j <= u; ++j)
				read(aa), pd[aa]=1;
			soll(p);
		}
		return 0;
	}
	return 0;
}
