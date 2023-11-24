#include <bits/stdc++.h>
#define mod 1000003
using namespace std;
const int N = 1e6+5;
int n, k, a[N], pd[N], fa[N], jc[N], inv[N], inc[N];

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
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
int c(int x, int y) {
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}

signed main() {
	freopen("bit.in", "r", stdin);
	freopen("bit.out", "w", stdout);
	read(n), read(k);
	jc[0]=jc[1]=inc[0]=inc[1]=inv[0]=inv[1]=1;
	for(int i = 2; i <= n; ++i)
		jc[i]=1LL*jc[i-1]*i%mod, inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod, inc[i]=1LL*inc[i-1]*inv[i]%mod;
	for(int i = 1; i <= n-k+1; ++i)
		read(a[i]);
	for(int i = 1; i <= n; ++i)
		pd[i]=-1, fa[i]=i;
	for(int i = 1; i+k <= n; ++i) {
		int gs = a[i+1]-a[i], faa = find(i);
		if(gs == 0) 
			fa[i+k]=faa;
		else
			if(gs == 1) {
				if(pd[faa] == 1) {
					puts("0");
					return 0;
				}
				pd[faa]=0, pd[i+k]=1;
			}
			else
				if(gs == -1) { 
					if(pd[faa] == 0) {
						puts("0");
						return 0;
					}
					pd[faa]=1, pd[i+k]=0;
				}
				else {
					puts("0");
					return 0;
				}
	}
	int gs = 0, mm = a[1];
	for(int i = 1; i <= k; ++i) 
		gs+=(pd[i] == -1), mm-=(pd[i] == 1);
	write(c(gs, mm), '\n'); 
	return 0;
}
