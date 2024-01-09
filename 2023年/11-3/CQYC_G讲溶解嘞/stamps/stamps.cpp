#include <bits/stdc++.h>
using namespace std;
const int N = 2e3+5;
int n, m, kk, l, r, dp[N][N], ans;
vector <int> to[N];
struct tree {
	int tr[N<<2], mn[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r, int p) {
		if(l == r) {
			tr[k]=dp[l][p], mn[k]=dp[l][p]-l;
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid, p);
		built(rs, mid+1, r, p);
		tr[k]=max(tr[ls], tr[rs]);
		mn[k]=max(mn[ls], mn[rs]);
	}
	int ask_tr(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret=max(ret, ask_tr(ls, l, mid, lq, rq));
		if(mid+1 <= rq)
			ret=max(ret, ask_tr(rs, mid+1, r, lq, rq));
		return ret;
	}
	int ask_mn(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return mn[k];
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret=max(ret, ask_mn(ls, l, mid, lq, rq));
		if(mid+1 <= rq)
			ret=max(ret, ask_mn(rs, mid+1, r, lq, rq));
		return ret;
	}
}A;

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
	freopen("stamps.in", "r", stdin);
	freopen("stamps.out", "w", stdout);
	read(n), read(m), read(kk);
	for(int i = 1; i <= m; ++i)
		read(l), read(r), to[r].push_back(l);
	for(int i = 1; i <= kk; ++i) {
		A.built(1, 1, n, i-1);
		for(int x = 1; x <= n; ++x)
			for(int y : to[x])
				dp[x][i]=max((y == 1 ? 0 : A.ask_tr(1, 1, n, 1, y-1))-y+1, (x == y ? 0 : A.ask_mn(1, 1, n, y, x)))+x;
	}
	for(int x = 1; x <= n; ++x)
		ans=max(ans, dp[x][kk]);
	write(ans, '\n');
	return 0;
}
