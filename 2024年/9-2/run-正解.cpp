#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 4e5+5;
int n, m, q, u[N], v[N], f[N], fa[N], cnt[N];

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
struct DSU {
	int tot, now, zhan[N][2];
	int find(int x) {
		return (fa[x] == x ? x : find(fa[x]));
	}
	int add(int x) {
		int xx = find(u[x]), yy = find(v[x]+n);
		++now;
		if(xx != yy) {
			if(cnt[xx] < cnt[yy]) swap(xx, yy);
			zhan[++tot][0]=yy, zhan[tot][1]=now;
			fa[yy]=xx, cnt[xx]+=cnt[yy];
		}
		xx = find(u[x]+n), yy = find(v[x]);
		if(xx != yy) {
			if(cnt[xx] < cnt[yy]) swap(xx, yy);
			zhan[++tot][0]=yy, zhan[tot][1]=now;
			fa[yy]=xx, cnt[xx]+=cnt[yy];
		}
		return (find(u[x]) == find(v[x]));
	}
	void pop() {
		while(tot && zhan[tot][1] == now)
			cnt[fa[zhan[tot][0]]]-=cnt[zhan[tot][0]], fa[zhan[tot][0]]=zhan[tot][0], --tot;
		--now;
	}
}A;
void dfs(int l, int r, int L, int R) {
	if(L > R || l > r) return ;
	if(l == r) {
		for(int i = L; i <= R; ++i)
			f[i]=l;
		return ;
	}
	int mid = ((L+R)>>1), to = R;
	// debug(l, r, L, R, mid, '\n');
	for(int i = mid; i <= r; ++i) {
		if(i >= R+1 && i < l) i=l;
		// debug(i), debug(' ');
		if(A.add(i)) {
			to=i;
			break;
		}
	}
	// debug('\n');
	f[mid]=to;
	// debug(mid, f[mid], "???\n");
	for(int i = to; i >= max(mid, l); --i) {
		if(i >= R+1 && i < l) i=R;
		A.pop();
	}
	dfs(l, to, L, mid-1);
	for(int i = mid; i <= min(R, l-1); ++i)
		A.pop();
	for(int i = max(R+1, l); i < to; ++i)
		A.add(i);
	dfs(to, r, mid+1, R);
	for(int i = max(R+1, l); i < to; ++i)
		A.pop();
}

signed main() {
	read(n), read(m), read(q);
	for(int i = 1; i <= n+n; ++i)
		fa[i]=i, cnt[i]=1;
	for(int i = 1; i <= m; ++i)
		read(u[i]), read(v[i]), u[i+m]=u[i], v[i+m]=v[i];
	u[m+m+1]=v[m+m+1]=1;
	dfs(1, m+m+1, 1, m+1);
	// for(int i = 1; i <= m; ++i)
	// 	debug(f[i]), debug(' ');
	for(int i = 1; i <= q; ++i) {
		int ll, rr;
		read(ll), read(rr);
		if(ll > rr) {
			puts("NO");
			continue;
		}
		// assert(l <= r);
		ll=ll-1+m;
		rr=rr+1;
		if(!f[rr] || ll < f[rr]) 
			puts("NO");
		else
			puts("YES");
	}
	return 0;
}