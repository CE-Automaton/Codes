#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
int n, m, k, a[15], ans, gs;
char fx[15];

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
int ksm(int xx, int nn, int ret = 1) {
	while(nn) {
		if(nn&1)
			ret=1LL*ret*xx%mod;
		nn>>=1;
		xx=1LL*xx*xx%mod;
	}
	return ret;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void dfs(int x) {
	if(x == m+1) {
		++gs;
		for(int i = 1; i <= n; ++i)
			for(int j = i+1; j <= n; ++j)
				ans=upd(ans+ksm(abs(a[j]-a[i]), k));
		return ;
	}
	int b[15];
	for(int i = 0; i <= (1<<n)-1; ++i) {
		for(int j = 1; j <= n; ++j)
			b[j]=a[j];
		for(int j = 0; j <= n-1; ++j)
			if((i>>j)&1)
				a[j+1]+=(fx[j+1] == 'R')-(fx[j+1] == 'L');
		dfs(x+1);
		for(int j = 1; j <= n; ++j)
			a[j]=b[j];
	}
} 

signed main() {
	freopen("stone.in", "r", stdin);
	freopen("stone.out", "w", stdout);
	read(n), read(m), read(k);
	for(int i = 1; i <= n; ++i) 
		read(a[i]), scanf(" %c", &fx[i]);
	dfs(1);
	write(1LL*ans*ksm(gs, mod-2)%mod, '\n');
	return 0;
}
