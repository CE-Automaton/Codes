#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e4+5;
int T, n, m, c[N], l[N], r[N], v[N], typ[N];
struct qwq {
	int w, r;
	bool operator <(const qwq& A) const {
		return A.r < r;
	}
};
priority_queue <qwq> q;
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
	File("factory");
	read(T);
	while(T--) {
		read(n), read(m);
		for(int i = 1; i <= n; ++i)
			read(c[i]);
		for(int i = 1; i <= m; ++i)
			read(l[i]), read(r[i]), read(v[i]), read(typ[i]);
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) 
				to[j].clear();
			for(int j = 1; j <= m; ++j)
				if(typ[j] == 0)
					to[l[j]].push_back(qwq {v[j], r[j]});
				else
					to[min(l[j], i)].push_back(qwq {v[j], max(r[j], i)});
			while(!q.empty())
				q.pop();
			LL ans = 0;
			for(int j = 1; j <= n; ++j) {
				for(int k = 0; k < to[j].size(); ++k)
					q.push(to[j][k]);
				int xx = c[j];
				while(xx && !q.empty()) {
					qwq it = q.top(); q.pop();
					if(it.r < j) continue;
					// debug(it.r, it.w, xx, "???\n");
					int yy = min(it.w, xx);
					xx-=yy, it.w-=yy;
					ans=ans+yy;
					if(it.w)
						q.push(it);
				}
			}
			write(ans, ' ');
		}
		putchar('\n');
	}
	return 0;
}