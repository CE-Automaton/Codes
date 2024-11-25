#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 55;
int n, m, l, r, fa[N], cnt[N], zhan[N], tot, cntt;
LL ans;
struct qwq {
	int u, v, w;
}b[N*N];

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
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
int comp(qwq A, qwq B) {
	return A.w < B.w;
}

signed main() {
	File("city");
	read(n), read(m);
	for(int i = 1; i <= m; ++i) {
		read(l), read(r);
		tot=0;
		for(int now = l; now <= n; now+=(now&(-now))) {
			int nxt = min(now+(now&(-now))-1, r);
			// debug(now, nxt, "\n");
			zhan[++tot]=now;
			if(nxt == r) break;
		}
		ans=0;
		for(int j = 1; j < tot; ++j)
			ans+=1LL*(zhan[j]+zhan[j+1])*(zhan[j+1]-1-zhan[j])/2;
		if(tot != 1) {
			for(int k = 1; k <= tot; ++k)
				fa[k]=k, cnt[k]=1;
			cntt=0;
			for(int o = 1; o <= tot; ++o)
				for(int k = o+1; k <= tot; ++k)
					b[++cntt]=qwq {o, k, (zhan[o]|zhan[k])};
			sort(b+1, b+1+cntt, comp);
			for(int i = 1; i <= cntt; ++i) {
				int x = b[i].u, y = b[i].v;
				x=find(x), y=find(y);
				if(x != y) {
					ans+=b[i].w;
					if(cnt[x] < cnt[y]) swap(x, y);
					fa[y]=x, cnt[x]+=cnt[y];
				}
			}
		}
		ans+=1LL*(zhan[tot]+1+r)*(r-zhan[tot])/2;
		write(ans, '\n');
	}
	// debug(clock(), "\n");
	return 0;
}