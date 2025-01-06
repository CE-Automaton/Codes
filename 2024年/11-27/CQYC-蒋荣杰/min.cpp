#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, a[N], b[N], qu[N], hd, tl, quu[N], hdd, tll, ww[N], fa[N], cnt[N], vis[N];
struct qwq {
	int w, d;
}ab[N];

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
struct tree {
	int tr[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		tr[k]=0;
		if(l == r)
			return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int lq, int rq, int ok) {
		if(lq <= l && r <= rq) {
			tr[k]=max(tr[k], ok);
			return ;
		}
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq, ok);
		if(mid < rq)
			updt(rs, mid+1, r, lq, rq, ok);
	}
	int ask(int k, int l, int r, int to) {
		if(l == r) 
			return tr[k];
		int mid = ((l+r)>>1);
		if(to <= mid)
			return max(tr[k], ask(ls, l, mid, to));
		else
			return max(tr[k], ask(rs, mid+1, r, to));
	}
}AAA;
int find(int x) {
	return (fa[x] == x ? x : fa[x]=find(fa[x]));
}
int comp(qwq A, qwq B) {
	return A.w > B.w;
}
void merge(int x, int y) {
	if(!x || y > n || !vis[x] || !vis[y])
		return ;
	x=find(x), y=find(y);
	if(cnt[x] > cnt[y]) swap(x, y);
	fa[x]=y, cnt[y]+=cnt[x];
}

signed main() {
	File("min");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	int pd1 = 1, pd2 = 1;
	for(int i = 1; i <= n; ++i)
		read(b[i]), pd1&=(b[i] == 1), pd2&=(b[i] == 1000000000);
	if(pd1) {
		// debug("sub A!\n");
		ww[1]=inf;
		for(int i = 1; i <= n; ++i)
			--a[i], ww[1]=min(ww[1], a[i]);
		for(int i = 1; i <= n; ++i)
			write(ww[1], '\n');
		return 0;
	}
	if(pd2) {
		// debug("sub B!\n");
		for(int i = 1; i <= n; ++i)
			fa[i]=i, cnt[i]=1, ab[i]=qwq {a[i], i};
		sort(ab+1, ab+1+n, comp);
		AAA.built(1, 1, n);
		for(int i = 1; i <= n; ++i) {
			vis[ab[i].d]=1;
			merge(ab[i].d-1, ab[i].d);
			merge(ab[i].d, ab[i].d+1);
			AAA.updt(1, 1, n, 1, cnt[find(ab[i].d)], ab[i].w);
		}
		for(int i = 1; i <= n; ++i)
			write(1000000000-AAA.ask(1, 1, n, i), '\n');
		return 0;
	}
	if(n <= 1000) {
		for(int k = 1; k <= n; ++k) {
			hd=hdd=1, tl=tll=0;
			ww[k]=inf;
			for(int o = 1; o < k; ++o) {
				while(hd <= tl && a[qu[tl]] > a[o])
					--tl;
				qu[++tl]=o;
				while(hdd <= tll && b[quu[tll]] > b[o])
					--tll;
				quu[++tll]=o;
			}
			for(int i = k; i <= n; ++i) {
				while(hd <= tl && a[qu[tl]] > a[i])
					--tl;
				qu[++tl]=i;
				while(hdd <= tll && b[quu[tll]] > b[i])
					--tll;
				quu[++tll]=i;
				while(hd <= tl && qu[hd] <= i-k)
					++hd;
				while(hdd <= tll && quu[hdd] <= i-k)
					++hdd;
				ww[k]=min(ww[k], abs(a[qu[hd]]-b[quu[hdd]]));
			}
			write(ww[k], '\n');
		}
	}
	return 0;
}