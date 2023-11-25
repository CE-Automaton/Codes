#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 45;
int n, m, f[N][N][N][N], sum[N][N][N][N], d[N][N][N], dd[N][N][N], ans[N];

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
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	read(n), read(m);
	for(int i = 0; i < m; ++i)
		f[0][i][i][i]=1;
	for(int l = 0; l < m; ++l) 
		for(int r = l; r < m; ++r)
			for(int o = 0; o < m; ++o)
				sum[0][l][r][o]=upd(sum[0][l][r-1][o]+f[0][l][r][o]);
	for(int i = 1; (1<<i) <= n; ++i) 
		for(int l = 0; l < m; ++l) {
			for(int r = l; r < m; ++r)
				for(int mid = l; mid <= r; ++mid)
					for(int p = 0; p < m; ++p) 
						if(f[i-1][mid][r][p])
							for(int o = 0; o < m; ++o)
								f[i][l][r][o*p%m]=upd(f[i][l][r][o*p%m]+1LL*sum[i-1][l][mid][o]*f[i-1][mid][r][p]%mod);
			for(int r = l; r < m; ++r)
				for(int o = 0; o < m; ++o)
					sum[i][l][r][o]=upd(sum[i][l][r-1][o]+f[i][l][r][o]);
		}
	int pd = 0;
	for(int i = 0; i <= 30; ++i) 
		if((n>>i)&1) {
			if(!pd) {
				for(int l = 0; l < m; ++l)
					for(int r = l; r < m; ++r) 
						for(int o = 0; o < m; ++o) 
							d[l][r][o]=f[i][l][r][o];
				pd=1;
				continue; 
			}
			for(int l = 0; l < m; ++l)
				for(int r = l; r < m; ++r) 
					for(int o = 0; o < m; ++o) 
						dd[l][r][o]=d[l][r][o], d[l][r][o]=0;
			for(int l = 0; l < m; ++l)
				for(int r = l; r < m; ++r) 
					for(int mid = l; mid <= r; ++mid)
						for(int o = 0; o < m; ++o) 
							if(dd[mid][r][o])
								for(int p = 0; p < m; ++p) 
									d[l][r][o*p%m]=upd(d[l][r][o*p%m]+1LL*sum[i][l][mid][p]*dd[mid][r][o]%mod); 
		}
	for(int l = 0; l < m; ++l)
		for(int r = l; r < m; ++r) 
			for(int o = 0; o < m; ++o) 
				ans[o]=upd(ans[o]+d[l][r][o]);
	for(int o = 0; o < m; ++o) 
		write(ans[o], '\n');
	return 0;
}
