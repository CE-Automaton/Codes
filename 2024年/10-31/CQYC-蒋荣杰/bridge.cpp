#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e2+5;
int t, n, dis[N][N], tot, u[N*N], v[N*N];
char a[N][N];

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
	File("bridge");
	read(t);
	while(t--) {
		read(n);
		for(int i = 1; i <= n; ++i)
			scanf("%s", a[i]+1);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				dis[i][j]=(a[i][j] == '1' ? 1 : inf);
		for(int k = 1; k <= n; ++k)
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j)
					dis[i][j]=min(dis[i][k]+dis[k][j], dis[i][j]);
		int pd = 1;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				if(dis[i][j]%2 != a[i][j]-'0' || (i != j && dis[i][j] == inf))
					pd=0;
		if(pd) {
			puts("Pure Memory");
			for(int i = 1; i <= n; ++i)
				for(int j = i+1; j <= n; ++j)
					if(a[i][j] == '1')
						++tot, u[tot]=i, v[tot]=j;
			write(tot, '\n');
			for(int i = 1; i <= tot; ++i)
				write(u[i], ' '), write(v[i], '\n');
			tot=0;
		}
		else
			puts("Track Lost");
	}
	return 0;
}