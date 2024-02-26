#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int n, aa[18], lst[1<<16], dp[1<<16], zhan[18], tot, mx;

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
	File("count");
	read(n);
	for(int i = 0; i < n; ++i)
		read(aa[i]);
	for(int i = 0; i < (1<<n); ++i) {
		tot=0;
		for(int j = 0; j < n; ++j)
			if(!((i>>j)&1)) 
				zhan[++tot]=j;
		for(int a = 1; a <= tot; ++a)
			for(int b = a+1; b <= tot; ++b)
				for(int c = b+1; c <= tot; ++c) 
					if((aa[zhan[a]] == 1 && aa[zhan[b]] == 2 && aa[zhan[c]] == 3) || (aa[zhan[a]] == 3 && aa[zhan[b]] == 2 && aa[zhan[c]] == 1)) {
						int j = (i|(1<<zhan[a])|(1<<(zhan[b]))|(1<<zhan[c]));
						if(dp[i]+1 > dp[j])
							dp[j]=dp[i]+1, lst[j]=i;
					}
	}
	for(int i = 0; i < (1<<n); ++i) 
		if(dp[i] > dp[mx]) 
			mx=i;
	write(dp[mx], '\n');
	int now = mx;
	while(now) {
		int fr = lst[now], op = (fr^now);
		for(int i = 0; i < n; ++i)
			if((op>>i)&1) 
				write(i, ' ');
		putchar('\n');
		now=fr;
	}
	return 0;
}
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症
//我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症我有彝语症