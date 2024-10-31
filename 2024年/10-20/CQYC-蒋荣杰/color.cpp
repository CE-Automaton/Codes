#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned int ui;
const int N = 2e5+5;
int t, n, m, c[N], to[N], ans, dp[2][N], pw[N];

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
	File("color");
	for(int i = 1; i <= 200000; ++i)
		pw[i]=pw[i-1]+__lg(i&(-i));
	read(t);
	while(t--) {
		read(n), read(m);
		ans=0;
		int pd = 1;
		for(int i = 1; i <= n; ++i) 
			read(c[i]), dp[0][i]=0, pd&=(c[i] == i);
		if(n > 10000 && pd) {
			ans=0;
			for(int i = 1; i <= n; ++i)
				ans^=(pw[n]-pw[n-i]-pw[i]+pw[n-1]-pw[n-i]-pw[i-1] == 0);
			int opp = ans+'0';
			putchar(opp);
			continue;
		}
		for(int i = 1; i <= m; ++i) 
			to[i]=0;
		for(int i = 1; i <= n; ++i)
			if(to[c[i]] == 0)
				dp[0][i]=1, to[c[i]]=1;
		int now = 0;
		for(int i = 2; i <= n; ++i) {
			int sum = 0;
			now^=1;
			for(int j = 1; j <= m; ++j)
				to[j]=0;
			for(int j = 1; j <= n; ++j) {
				sum^=dp[now^1][j];
				dp[now][j]=(sum^to[c[j]]);
				to[c[j]]=sum;
			}
		}
		for(int j = 1; j <= n; ++j)
			ans^=dp[now][j];
		int opp = ans+'0';
		putchar(opp);
	}
	return 0;
}