#include <bits/stdc++.h>
using namespace std;
const int N = 1e3+5, base = 31, mod1=1e9+7, mod2=998244353;
int n, m, a[N][N], b[N<<1];
char s[N][N];
long long ans;
unordered_map <long long, int> mp;

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
int upd1(int x) {
	return (x >= mod1 ? x-mod1 : x);
}
int upd2(int x) {
	return (x >= mod2 ? x-mod2 : x);
}

signed main() {
	freopen("algebra.in", "r", stdin);
	freopen("algebra.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= m; ++i) {
		for(int j = 1; j <= n; ++j)
			scanf("%s", s[j]+1);
		for(int j = 1; j <= n; ++j)
			for(int k = 1; k <= n; ++k)
				a[j][k]=s[j][k]-'0';
		for(int j = 1; j < n; ++j)
			for(int k = 1; k < n; ++k)
				if(a[j][k])
					a[j][k]^=1, a[j+1][k]^=1, a[j][k+1]^=1, a[j+1][k+1]^=1;
		// for(int j = 1; j <= n; ++j, putchar('\n'))
		// 	for(int k = 1; k <= n; ++k)
		// 		write(a[j][k], ' ');
		for(int j = 1; j <= n; ++j)
			b[j]=a[j][n];
		for(int k = n; k >= 1; --k)
			b[n+n-k+1]=a[n][k];
		int hs1 = 0, hs2 = 0;
		for(int o = 1; o <= (n<<1); ++o)
			hs1=upd1(1LL*hs1*base%mod1+b[o]+1), 
			hs2=upd2(1LL*hs2*base%mod2+b[o]+1);
		long long now = hs1*1000000000LL+hs2;
		if(mp.find(now) == mp.end())
			mp[now]=0;
		ans+=mp[now];
		++mp[now];
	}
	write(ans, '\n');
	return 0;
}
