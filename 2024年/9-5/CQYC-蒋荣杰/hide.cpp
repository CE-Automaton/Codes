#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 55;
int n, m, k, r, u[N], v[N], s[N], t[N], dis[N][N], ans, sum;

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
	File("hide");
	read(n), read(m), read(k), read(r);
	for(int i = 1; i <= m; ++i)
		read(u[i]), read(v[i]);
	for(int i = 1; i <= k; ++i)
		read(s[i]), read(t[i]);
	if(r == 2) {
		ans=0;
		for(int i = 1; i <= m; ++i)
			for(int j = i+1; j <= m; ++j) {
				for(int o = 1; o <= n; ++o)
					for(int p = 1; p <= n; ++p)
						dis[o][p]=inf;
				sum=0;
				for(int op = 1; op <= m; ++op)
					if(op == i || op == j)
						dis[u[op]][v[op]]=1,
						dis[v[op]][u[op]]=1;
					else
						dis[u[op]][v[op]]=0,
						dis[v[op]][u[op]]=0;
				for(int kk = 1; kk <= n; ++kk)
					for(int o = 1; o <= n; ++o)
						for(int p = 1; p <= n; ++p)
							dis[o][p]=min(dis[o][p], dis[o][kk]+dis[kk][p]);
				for(int kk = 1; kk <= k; ++kk)
					sum+=dis[s[kk]][t[kk]];
				ans=max(ans, sum);
			}
		write(ans, '\n');
	}
	return 0;
}