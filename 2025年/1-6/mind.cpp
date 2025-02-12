#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, k, a[N], ss[N];
LL ans;
char s[N];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
	// File("mind5");
	read(n), read(k);
	scanf("%s", s+1);
	for(int i = 1; i <= n; ++i)
		a[i]=(s[i] == 'L' ? -1 : 1), ss[i]=ss[i-1]+a[i];
	if(ss[n] == 0) {
		for(int i = 1; i <= n; ++i)
			ans+=(a[i] == 1 ? (ss[i] > 0) : (ss[i] >= 0));
		write(ans*k, '\n');
		return 0;
	}
	if(ss[n] < 0) {
		for(int i = 1; i*2 <= n; ++i)
			swap(a[i], a[n-i+1]);
		for(int i = 1; i <= n; ++i)
			a[i]=-a[i], ss[i]=ss[i-1]+a[i];
	}
	// for(int i = 1; i <= n; ++i)
	// 	debug(ss[i], "?\n");
	for(int i = 1, xx = 1; i <= n; ++i) {
		if(ss[i] > 0) xx = 0;
		if(a[i] == -1)
			ans+=k-xx;
		else
			ans+=2*max(0LL, (LL) k-max(0LL, 1LL*(1LL*k*ss[n]-ss[i]+ss[n])/ss[n]));
	}
	write(ans, '\n');
	return 0;
}