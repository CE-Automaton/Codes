#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5, base = 31, mod = 1000000007;
int n, nxt[N], hs[N], bs[N], p, f[N], ans;
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
int pd(int l, int r, int ll, int rr) {
	return (upd(hs[r]-1LL*hs[l-1]*bs[r-l+1]%mod+mod) == upd(hs[rr]-1LL*hs[ll-1]*bs[rr-ll+1]%mod+mod));
}

signed main() {
	read(n);
	scanf("%s", s+1);
	for(int i = 2, j = 0; i <= n; ++i) {
		while(j && s[j+1] != s[i]) j=nxt[j];
		if(s[j+1] == s[i]) ++j;
		nxt[i]=j;
	}
	bs[0]=1;
	for(int i = 1; i <= n; ++i)
		hs[i]=upd(1LL*hs[i-1]*base%mod+s[i]-'a'+1), 
		bs[i]=1LL*bs[i-1]*base%mod;
	p=0;
	for(int i = n/2; i; --i) {
		p+=2;
		while(i+p-1 >= n-i-p+2 || !pd(i, i+p-1, n-i-p+2, n-i+1)) --p;
		f[i]=p;
		// cout<<i<<" "<<n-i+1<<" "<<p<<"!?\n";
	}
	p=nxt[n];
	while(p) {
		if(p+p <= n)
			ans=max(ans, p+f[p+1]);
		p=nxt[p];
	}
	write(ans, '\n');
	return 0;
}
