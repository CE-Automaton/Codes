#include <bits/stdc++.h>
#define entr putchar('\n')
#define lowbit(x) (x&(-x))
#define inf 1000000000000000007LL
#define F(i,l,r) for(int i = l; i r; ++i)
#define R(i,r,l) for(int i = r; i l; --i)
#define RF(i,l,r,j) for(int i = l; i r; i = j)
using namespace std;
const int N = 21;
int n, m, q, abab, u, v, k, w[N+5][N+5], f[N+1][(1<<N)+5];
long long s[(1<<N)+5], ss[(1<<N)+5];

inline void read() {}
template <typename T, typename ...T_>
inline void read(T &x, T_ &...p) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x), read(p...);
}
int lne; char put[105];
inline void write() {}
template <typename T, typename ...T_>
inline void write(T x, T_...p) {
	if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(' '), write(p...);
}

signed main() {
	freopen("acquire.in", "r", stdin);
	freopen("acquire.out", "w", stdout);
	read(n, m);
	abab=(1<<n)-1;
	F(i, 1, <= n)
		F(j, i+1, <= n)
			w[i][j]=w[j][i]=2147483647LL;
	F(i, 1, <= m) 
		read(u, v, k), w[u][v]=w[v][u]=k;
	F(i, 1, <= n) {
		F(j, 0, <= abab)
			f[i][j]=2147483647LL;
		F(j, 1, <= n)
			f[i][1<<(j-1)]=w[i][j];
		F(j, 1, <= abab) 
			f[i][j]=min(f[i][j], min(f[i][j-lowbit(j)], f[i][lowbit(j)]));
		f[i][0]=0;
	}
	F(j, 1, <= abab)
		s[j]=inf;
	F(i, 1, <= abab)
		F(j, 1, <= n)
			if((i>>(j-1))&1)
				s[i]=min(s[i], s[i^(1<<(j-1))]+f[j][i^(1<<(j-1))]);
	F(j, 0, <= abab)
		ss[abab^j]=s[j];
	F(j, 0, < n)
		F(i, 1, <= abab)
			if((i>>j)&1)
				ss[i]=min(ss[i], ss[i^(1<<j)]);
	read(q);
	F(i, 1, <= q) {
		read(u);
		int now = abab;
		F(j, 1, <= u)
			read(v), now^=(1<<(v-1));
		write(ss[now]), entr;
	}
	return 0;
}
