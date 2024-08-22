#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, m, u, v, in[N], out[N], a[N], pnt[N], vis[N], ds[N];
vector <int> to[N], so[N];
queue <int> q;
struct qwq {
	int d;
	bool operator <(const qwq& A) const {
		return pnt[A.d] < pnt[d];
	}
};
priority_queue <qwq> qq, pp;

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
	File("permutation");
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(a[i]), pnt[i]=(a[i] == 0 ? n : a[i]), vis[a[i]]=1;
	for(int i = 1; i <= m; ++i)
		read(u), read(v), to[u].push_back(v), so[v].push_back(u), ++in[v], ++ds[v], ++out[u];
	for(int i = 1; i <= n; ++i)
		if(!out[i]) 
			q.push(i);
	while(!q.empty()) {
		int it = q.front(); q.pop();
		for(int y : so[it]) {
			--out[y];
			pnt[y]=min(pnt[y], pnt[it]);//离正解只有一步之遥啊
			if(!out[y]) 
				q.push(y);
		}
	}
	for(int i = 1; i <= n; ++i)
		if(!in[i]) {
			if(a[i])
				pp.push(qwq {i});
			else
				qq.push(qwq {i});
		}
	for(int i = 1; i <= n; ++i)
		if(!vis[i]) {
			while(!pp.empty() && a[pp.top().d] < i) {
				int op = pp.top().d;
				pp.pop();
				for(int y : to[op]) {
					--in[y];
					if(!in[y]) {
						if(a[y])
							pp.push(qwq {y});
						else
							qq.push(qwq {y});
					}
				}
			}
			if(qq.empty()) {
				puts("-1");
				return 0;
			}
			int op = qq.top().d;
			qq.pop();
			a[op]=i;
			for(int y : to[op]) {
				--in[y];
				if(!in[y]) {
					if(a[y])
						pp.push(qwq {y});
					else
						qq.push(qwq {y});
				}
			}
		}
	// debug("???\n");
	for(int i = 1; i <= n; ++i)
		for(int j : to[i])
			if(a[j] < a[i]) {
				// debug(i, j, a[i], a[j], pnt[i], pnt[j], vis[a[i]], vis[a[j]], '\n');
				puts("-1");
				return 0;
			}
	for(int i = 1; i <= n; ++i)
		write(a[i], ' ');
	return 0;
}