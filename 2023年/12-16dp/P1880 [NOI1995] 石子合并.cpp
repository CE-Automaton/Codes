#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 1e2+5;
int n, a[N<<1], f[N<<1][N<<1], g[N<<1][N<<1], sum[N<<1], mn=inf, mx;

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

signed main() {
	read(n);
	for(int i = 1; i <= (n<<1); ++i)
		for(int j = 1; j <= (n<<1); ++j)
			f[i][j]=0, g[i][j]=inf;
	for(int i = 1; i <= n; ++i)
		read(a[i]), a[i+n]=a[i], 
		f[i][i]=f[i+n][i+n]=g[i][i]=g[i+n][i+n]=0;
	for(int i = 1; i <= (n<<1); ++i)
		sum[i]=sum[i-1]+a[i];
	for(int i = 2; i <= n; ++i)
		for(int l = 1, r = i; r <= (n<<1); ++l, ++r)
			for(int o = l; o < r; ++o)
				f[l][r]=max(f[l][r], f[l][o]+f[o+1][r]+sum[r]-sum[l-1]), 
				g[l][r]=min(g[l][r], g[l][o]+g[o+1][r]+sum[r]-sum[l-1]);
	for(int r = n; r <= (n<<1); ++r)
		mn=min(mn, g[r-n+1][r]), 
		mx=max(mx, f[r-n+1][r]);
	write(mn, '\n'), write(mx, '\n');
	return 0;
}
