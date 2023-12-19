#include <bits/stdc++.h>
#define mod 23333333
using namespace std;
const int N = 1e5+5;
int n, B, f[N], sm[N], g[2][N], zhan[N], nmb[N], ll, rr, ans;

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
void get_ans(int now) {
	// for(int i = 0; i <= n; ++i)
	// 	cout<<g[now][i]<<" ";
	// puts("");
	for(int i = 0; i <= n; ++i)
		ans=upd(ans+1LL*f[i]*g[now][n-i]%mod);
}

signed main() {
	read(n);
	B=(int) floor(sqrt(n));
	f[0]=1;
	for(int i = 1; i <= B; ++i) {
		for(int j = 0; j <= i-1; ++j)
			sm[j]=f[j];
		for(int j = i; j <= n; ++j)
			sm[j]=upd(sm[j-i]+f[j]);
		for(int j = 1; j <= n; ++j)
			f[j]=upd(sm[j]-(j >= i*(i+1) ? sm[j-(i+1)*i] : 0)+mod);
	}
	ans=f[n];
	++B;
	int now = 0;
	for(int i = B; i <= n; ++i)
		g[0][i]=1;
	get_ans(now);
	for(int i = 2; i <= B; ++i) {
		now^=1;
		for(int j = 0; j <= n; ++j)
			g[now][j]=0;
		for(int j = 0; j <= n; ++j)
			g[now][j]=upd((j >= B ? g[now^1][j-B] : 0)+(j >= i ? g[now][j-i] : 0));
		get_ans(now);
	}
	write(ans, '\n');
	return 0;
}
