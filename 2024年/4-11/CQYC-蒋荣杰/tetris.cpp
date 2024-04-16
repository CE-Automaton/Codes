#include <bits/stdc++.h>
#define mod 998244353
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e3+5;
int n, m, R, C, to[N][N], pd[N][N], k, pw[N], fa[N][N], g, ans;
char s[N][N];

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void sol() {
	memset(pd, -1, sizeof pd);
	int pp = -1;
	for(int i = 1; i <= m; ++i) {
		pd[n][i]=(s[n][i] == '.' ? n+1 : n), 
		to[n][i]=n;
		if(s[n][i] == '#') 
			pp=(pp == -1 ? i : pp), fa[n][i]=pp;
		else
			pp=-1;
	}
	for(int i = n-1; i >= 1; --i) {
		int l = -1;
		for(int j = 1; j <= m; ++j) 
			if(s[i][j] == '#') {
				l=(l == -1 ? j : l);
				fa[i][j]=l;
				if(j == m || s[i][j+1] == '.') {
					int mn = n+1;
					for(int o = l; o <= j; ++o)
						mn=min(mn, pd[i+1][o]);
					for(int o = l; o <= j; ++o) {
						to[i][o]=mn-1, pd[i][o]=mn-1;
						for(int p = i+1, ggg = 1; p <= n; ++p, ++ggg)
							if(s[p][o] == '#')
								to[p][fa[p][o]]=to[i][o]+ggg;
							else
								break;
					}
				}
			}
			else l=-1, pd[i][j]=pd[i+1][j];
	}
	// for(int i = 1; i <= n; ++i, putchar('\n'))
	// 	for(int j = 1; j <= m; ++j)
	// 		if(s[i][j] == '.')
	// 			putchar('.'), putchar(' ');
	// 		else
	// 			write(to[i][fa[i][j]], ' ');
	// putchar('\n');
	ans=upd(ans+1LL*pw[k-g]*to[R][fa[R][C]]%mod);
}

signed main() {
	File("tetris");
	read(n), read(m), read(R), read(C);
	for(int i = 1; i <= n; ++i)
		scanf("%s", s[i]+1);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			k+=(s[i][j] == '.');
	pw[0]=1;
	for(int i = 1; i <= n*m; ++i)
		pw[i]=2021LL*pw[i-1]%mod;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(s[i][j] == '.') {
				++g;
				s[i][j]='#';
				sol();
				s[i][j]='.';
			}
	write(ans, '\n');
	return 0;
}