#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 105;
int m, q, n, bs[35][N][N], ans[N], a[N];

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	File("chain");
	read(m), read(q);
	for(int i = 1; i <= m; ++i) 
		bs[0][i][i]=2*i, bs[0][i][i-1]=i-1, bs[0][i][i+1]=i+1;
	for(int i = 1; i <= 30; ++i) 
		for(int o = 1; o <= m; ++o)
			for(int op = 1; op <= m; ++op)
				for(int k = 1; k <= m; ++k)
					bs[i][o][k]=upd(bs[i][o][k]+1LL*bs[i-1][o][op]*bs[i-1][op][k]%mod);
	while(q--) {
		read(n), --n;
		for(int i = 1; i <= m; ++i)
			ans[i]=0;
		ans[1]=1;
		for(int i = 0; (1<<i) <= n; ++i) 
			if((n>>i)&1) {
				for(int o = 1; o <= m; ++o)	
					a[o]=ans[o], ans[o]=0;
				for(int o = 1; o <= m; ++o)	
					for(int k = 1; k <= m; ++k)
						ans[k]=upd(ans[k]+1LL*a[o]*bs[i][o][k]%mod);
			}
		write(ans[1], '\n');
	}
	// debug(clock(), '\n');
	return 0;
}