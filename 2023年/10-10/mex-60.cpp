#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 5e3+5;
int n, b[N], gs[N], sum[N][N], jc[N<<1], inv[N<<1], inc[N<<1], ans;

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
int c(int x, int y) {
	return 1LL*jc[x]*inc[x-y]%mod*inc[y]%mod;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
//	freopen("mex.in", "r", stdin);
//	freopen("mex.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) {
		read(b[i]);
		if(b[i] <= n+1)
			++gs[b[i]];
	}
	sort(b+1, b+1+n);
	inv[0]=inv[1]=jc[0]=jc[1]=inc[0]=inc[1]=1;
	for(int i = 2; i <= n*2; ++i)
		inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod, 
		inc[i]=1LL*inc[i-1]*inv[i]%mod, jc[i]=1LL*jc[i-1]*i%mod;
	for(int i = n+1; i >= 1; --i) {
		int l = 1, r = n, ll = n+1;
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(b[mid] >= i)
				ll=mid, r=mid-1;
			else
				l=mid+1;
		}
		
		sum[i][0]=i;
		for(int j = ll; j <= n; ++j)
			for(int o = j-ll; o >= 0; --o)
				sum[i][o+1]=upd(sum[i][o+1]+sum[i][o]), 
				sum[i][o]=1LL*sum[i][o]*upd(b[j]+mod-i)%mod;
		
		for(int j = 0; j-1+gs[i] <= n+1; ++j)
			if(sum[i+1][j])
				for(int p = 1; j+gs[i]-p >= 0; ++p)
					sum[i][j-p+gs[i]]=upd(sum[i][j-p+gs[i]]+1LL*sum[i+1][j]*c(j+gs[i], p)%mod);
	}
	for(int j = 1; j <= n+1; ++j)
		ans=upd(ans+sum[1][j]);
	ans=(gs[0] == 0 ? ans : upd(ans+sum[1][0]));
	write(ans, '\n');
	return 0;
}
