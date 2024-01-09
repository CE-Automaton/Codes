#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1e5+5;
int n, f[N], inv[N], ans;
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
	read(n);
	scanf("%s", s+1);
    s[0]=s[n+1]='.';
	f[0]=f[1]=inv[0]=inv[1]=1;
	for(int i = 2; i <= n; ++i)
		inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod;
    int cnt = 0;
    for(int i = 1; i <= n; ++i)
        f[i]=1LL*f[i-1]*upd(1-1LL*inv[i]*inv[2]%mod+mod)%mod, cnt+=(s[i] == '.');
	for(int i = 1, lst = 0, ls = 0, gs = 0; i <= n+1; ++i) 
		if(s[i] == '.') {
			ans=upd(ans+1LL*f[lst]*f[cnt-lst]%mod*(gs+ls)%mod);
			++lst, ls=i, gs=0;
		}
        else
            gs+=(s[i] == '<');
	write(ans, '\n');
	return 0;
}
