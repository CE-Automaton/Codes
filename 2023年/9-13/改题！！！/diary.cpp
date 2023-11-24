#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 2e6+5;
int n, m, jc[N], inv[N], inc[N], tot, zhan[N], ans;
char s[N], t[N];

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
int c(int x, int y) {
	if(x == 0 || y == 0)
		return 1;
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}

signed main() {
//	freopen("diary.in", "r", stdin);
//	freopen("diary.out", "w", stdout);
	scanf("%s %s", s+1, t+1);
	n=strlen(s+1);
	m=strlen(t+1);
	for(int i = 1; i <= m; ++i) 
		if(t[i] == '0') {
			puts("0");
			return 0;
		}
	jc[0]=jc[1]=inc[0]=inc[1]=inv[0]=inv[1]=1;
	for(int i = 2; i <= n; ++i)
		jc[i]=1LL*jc[i-1]*i%mod, inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	for(int i = 1; i <= n; ++i)
		if(s[i] == '1')
			zhan[++tot]=i;
	ans=(tot >= m);
	zhan[++tot]=n+1;
	for(int i = 1; i <= min(tot, m)-1; ++i) {
		int x = n-zhan[i+1], y = m-i;
		if(x < 0 || x < y) continue;
		ans=upd(ans+c(x, y));
	}
	for(int i = 2; i+m-1 <= n; ++i)
		ans=upd(ans+c(n-i, m-1));
	write(ans, '\n');
	return 0;
}
