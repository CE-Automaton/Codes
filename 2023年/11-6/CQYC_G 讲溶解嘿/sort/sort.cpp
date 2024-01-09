#include <bits/stdc++.h>
using namespace std;
const int N = 7e5+5;
int n, a[N], to[N], rt[N], gs;
long long ans;
struct node {
	int ls, rs, w;
}tr[N*25];
struct tree {
	void inst(int& k, int l, int r, int to) {
		tr[++gs]=tr[k], k=gs;
		if(l == r) {
			tr[k].w=1;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			inst(tr[k].ls, l, mid, to);
		else
			inst(tr[k].rs, mid+1, r, to);
		tr[k].w=tr[tr[k].ls].w+tr[tr[k].rs].w;
	}
	int ask(int k1, int k0, int l, int r, int to) {
		if(l == r)
			return l;
		int mid = ((l+r)>>1), aa = tr[tr[k1].ls].w-tr[tr[k0].ls].w;
		if(to <= aa)
			return ask(tr[k1].ls, tr[k0].ls, l, mid, to);
		else
			return ask(tr[k1].rs, tr[k0].rs, mid+1, r, to-aa);
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
void sol(int L, int R) {
//	cerr<<L<<" "<<R<<"\n";
	if(R <= L) return ;
	int gs = tr[rt[R]].w-tr[rt[L-1]].w;
	ans+=gs;
	gs=(gs>>1)+(gs&1);
	gs=a[A.ask(rt[R], rt[L-1], 1, n, gs)];
	sol(L, gs-1);
	sol(gs+1, R);
}

signed main() {
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), to[a[i]]=i;
	for(int i = 1; i <= n; ++i)
		rt[i]=rt[i-1], A.inst(rt[i], 1, n, to[i]);
	sol(1, n);
	write(ans, '\n');
	return 0;
}
