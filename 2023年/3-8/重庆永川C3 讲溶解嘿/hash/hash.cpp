#include <bits/stdc++.h>
#define TPLT template <typename T>
#define mod 998244353
#define uLL unsigned long long
using namespace std;
const uLL base = 29;
int T, n, m, ln[55], w[55], sum[55][55], ans; 
uLL bs[55], hs[55], ht[55];
char s[55], t[55];

TPLT void read(T& x) {
	x=0; char c=getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
}
int len; char put[105];
TPLT void write(T x) {
	if(x < 0) putchar('-'), x=-x;
	do { put[++len]=x%10, x/=10; }while(x);
	while(len) putchar(put[len--]^48);
}

int main() {
	freopen("hash.in", "r", stdin);
	freopen("hash.out", "w", stdout);
	read(T);
	while(T--) {
		scanf("%s", s+1);
		n=strlen(s+1);
		bs[0]=1;
		for(int i = 1; i <= n; ++i)
			bs[i]=bs[i-1]*base, hs[i]=hs[i-1]*base+s[i]-'a'+1;
		memset(sum, 0, sizeof sum);
		read(m);
		for(int i = 1; i <= m; ++i) {
			scanf("%s", t+1);
			read(w[i]);
			ln[i] = strlen(t+1);
			for(int o = 1; o <= ln[i]; ++o)
				ht[i]=ht[i]*base+t[o]-'a'+1;
			for(int r = ln[i]; r <= n; ++r)
				if(hs[r]-hs[r-ln[i]]*bs[ln[i]] == ht[i])
					sum[r-ln[i]+1][r]=(sum[r-ln[i]+1][r]+w[i])%mod;
		}
		for(int len = 1; len <= n; ++len)
			for(int r = len; r <= n; ++r)
				sum[r-len+1][r]=(((sum[r-len+1][r]+sum[r-len+2][r])%mod+sum[r-len+1][r-1])%mod-sum[r-len+2][r-1]+mod)%mod;
		for(int l = 1; l <= n; ++l)
			for(int r = l; r <= n; ++r)
				ans=(ans+1LL*sum[l][r]*sum[l][r]%mod*sum[l][r]%mod*sum[l][r]%mod*sum[l][r]%mod)%mod;
		write(ans); putchar('\n');
	}
	return 0;
}
