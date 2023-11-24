#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 2e5+7e4+5;
int n, m, sum[N], pow2[N], pow11[N], inf2[N], inf11[N], l, r, x, f, gs;
char s[N];

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
	freopen("idol.in", "r", stdin);
	freopen("idol.out", "w", stdout);
	read(n);
	scanf("%s", s);
	n=(1<<n);
	inf2[0]=inf11[0]=pow2[0]=pow11[0]=1;
	inf2[1]=499122177, pow2[1]=2;
	inf11[1]=272248460, pow11[1]=11;
	for(int i = 2; i <= n; ++i)
		inf2[i]=1LL*inf2[i-1]*inf2[1]%mod, 
		pow2[i]=upd(pow2[i-1]+pow2[i-1]), 
		inf11[i]=1LL*inf11[i-1]*inf11[1]%mod, 
		pow11[i]=11LL*pow11[i-1]%mod;
	for(int i = 1; i <= n+1; ++i)
		sum[i]=upd(sum[i-1]+1LL*pow2[i-1]*pow11[n-i+1]%mod*(s[i-1]-'0')%mod);
	read(m);
	while(m--) {
		read(l), read(r), read(x);
		if(x == 0) {
			f=upd(sum[r+1]-sum[l]+mod);
			f=1LL*f*inf2[l]%mod*inf11[n-r]%mod;
		}
		else {
			f=0, gs=1;
			for(int i = l; i <= r; ++i)
				f=upd(11LL*f%mod+1LL*gs*(s[i^x]-'0')%mod), gs=upd(gs+gs);
		}
		write(f, '\n');
	}
	return 0;
}
