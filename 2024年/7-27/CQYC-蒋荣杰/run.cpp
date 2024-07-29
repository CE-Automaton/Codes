#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e3+5;
int n, m, b[N][N], f[N][N][2];

template <typename T> inline void debug(T x) { cerr<<x<<'\n'; }
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
	File("run");
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			read(b[i][j]), f[i][j][0]=f[i][j][1]=inf;
	f[1][1][b[1][1]]=b[1][1];
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			if(i < n) {
				if(b[i+1][j] == 0)
					f[i+1][j][0]=min(f[i+1][j][0], min(f[i][j][0], f[i][j][1]));
				else
					f[i+1][j][1]=min(f[i+1][j][1], min(f[i][j][0]+1, f[i][j][1]));
			}
			if(j < m) {
				if(b[i][j+1] == 0)
					f[i][j+1][0]=min(f[i][j+1][0], min(f[i][j][0], f[i][j][1]));
				else
					f[i][j+1][1]=min(f[i][j+1][1], min(f[i][j][0]+1, f[i][j][1]));
			}
		}
	write(min(f[n][m][0], f[n][m][1]), '\n');
	return 0;
}