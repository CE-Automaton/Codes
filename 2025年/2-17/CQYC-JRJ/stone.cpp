#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e3+5;
int n, m, k, u, v, col[N], pd[N][N], vis[N], dep[N];
vector <int> to[N];
queue <int> q;

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
void sol(int nn) {
	for(int i = 1; i <= nn; ++i)
		to[i].clear();
	for(int i = 1; i <= nn; ++i)
		for(int j = 1; j <= nn; ++j)
			if(pd[i][j])
				to[i].push_back(j);
	int ans = 0;
	for(int i = 1; i <= nn; ++i) {
		for(int j = 1; j <= nn; ++j)
			dep[j]=0;
		dep[i]=1;
		q.push(i);
		while(!q.empty()) {
			int it = q.front(); q.pop();
			// debug(it, "???\n");
			for(int i = 0; i < to[it].size(); ++i)
				if(!dep[to[it][i]]) {
					dep[to[it][i]]=dep[it]+1;
					q.push(to[it][i]);
				}
		}
		for(int j = 1; j <= nn; ++j)
			ans=max(ans, dep[j]-1);
	}
	write(ans, '\n');
}

signed main() {
	File("stone");
	read(n), read(m), read(k);
	int ppd = 1;
	for(int i = 1; i <= n; ++i)
		read(col[i]), ppd&=(col[i] == 1);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), pd[u][v]=pd[v][u]=1;
	if(k == 0 || ppd || m == n-1) {
		// debug("????\n");
		sol(n);
		return 0;
	}
	return 0;
}
