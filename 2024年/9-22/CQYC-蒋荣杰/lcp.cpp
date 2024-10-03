#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e3+5;
int n, m, a[N], nxt[N];
LL dp[2][N], ans;
struct qwq { int t, w; };
vector <qwq> to[N];

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
	File("lcp");
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 2, j = 0; i <= n; ++i) {
		while(j && a[j+1] != a[i]) j=nxt[j];
		if(a[j+1] == a[i]) ++j;
		nxt[i]=j;
	}
	for(int i = 1; i <= n; ++i) {
		if(nxt[i] == 0) {
			if(a[i+1] == a[1])
				to[i].push_back(qwq {i+1, 2});
			else
				to[i].push_back(qwq {1, 1}), 
				to[i].push_back(qwq {i+1, 1});
		}
		else {
			int pd = 0;
			for(qwq j : to[nxt[i]])
				if(a[j.t] == a[i+1]) {
					to[i].push_back(qwq {i+1, j.w+1});
					pd=1;
				}
				else 
					to[i].push_back(qwq {j.t, j.w});
			if(!pd) 
				to[i].push_back(qwq {i+1, 1});
		}
	}
	dp[0][1]=1;
	int now = 0;
	for(int j = 2; j <= m; ++j) {
		now^=1;
		for(int i = 1; i <= n; ++i)
			dp[now][i]=0;
		for(int i = 1; i <= n; ++i)
			if(dp[now^1][i]) {
				for(qwq p : to[i])
					dp[now][p.t]=max(dp[now][p.t], dp[now^1][i]+p.w);
			}
	}
	for(int i = 1; i <= n; ++i)
		ans=max(ans, dp[now][i]);
	write(ans, '\n');
	// debug(clock());
	return 0;
}