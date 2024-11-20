#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int t, n, s, u, v;
LL a[N], dsmx[25][25], dsmn[25][25], www[25][25];

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
	File("metro");
	read(t);
	while(t--) {
		read(n), read(s);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				dsmx[i][j]=inf, dsmn[i][j]=0;
		for(int i = 1; i <= n; ++i)
			read(a[i]), dsmx[i][i]=dsmn[i][i]=a[i];
		for(int i = 2; i <= n; ++i)
			read(u), read(v),
			dsmx[u][v]=dsmx[v][u]=max(a[u], a[v]), dsmn[u][v]=dsmn[v][u]=min(a[u], a[v]);
		for(int k = 1; k <= n; ++k)
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j)
					dsmx[i][j]=min(dsmx[i][j], max(dsmx[i][k], dsmx[k][j])), 
					dsmn[i][j]=max(dsmn[i][j], min(dsmn[i][k], dsmn[k][j]));
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				www[i][j]=1LL*dsmx[i][j]*dsmn[i][j]/*, debug(i, j, www[i][j], "???\n")*/;
		for(int k = 1; k <= n; ++k)
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j)
					www[i][j]=min(www[i][j], www[i][k]+www[k][j]);
		for(int i = 1; i <= n; ++i)
			write((s == i ? 0 : www[s][i]), ' ');
		putchar('\n');
	}
	// debug(clock(), '\n');
	return 0;
}