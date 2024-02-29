#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, h[N], vis[N], ans, out[N][2], dp[(1<<17)], fr[(1<<17)];
struct qwq {
	int tr[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k]=h[l];
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		tr[k]=max(tr[ls], tr[rs]);
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[k];
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret=max(ret, ask(ls, l, mid, lq, rq));
		if(mid+1 <= rq)
			ret=max(ret, ask(rs, mid+1, r, lq, rq));
		return ret;
	}
	void updt(int k, int l, int r, int to) {
		if(l == r) {
			tr[k]=0;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls, l, mid, to);
		else
			updt(rs, mid+1, r, to);
		tr[k]=max(tr[ls], tr[rs]);
	}
}A;

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
	File("shoot");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(h[i]);
	A.built(1, 1, n);
	for(int i = 1; i <= n; ++i) {
		if(vis[i]) continue;
		int l = i+1, r = n, ok = 0;
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(A.ask(1, 1, n, i+1, mid) >= h[i])
				ok=mid, r=mid-1;
			else
				l=mid+1;
		}
		++ans;
		out[ans][0]=i;
		out[ans][1]=ok;
		vis[ok]=1;
		A.updt(1, 1, n, ok);
	}
	write(ans, '\n');
	for(int i = 1; i <= ans; ++i) {
		if(out[i][1])
			write(h[out[i][0]], ' '), write(h[out[i][1]], '\n');
		else
			write(h[out[i][0]], '\n');
	}
	return 0;
}