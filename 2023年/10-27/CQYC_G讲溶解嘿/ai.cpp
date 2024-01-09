#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, v, kk, cnt;
long long m, to[N], nd[N], ans=-1;
struct thngs {
	long long v, w;
}a[N], b[N];
struct tree {
	int tr[N<<2];
	long long sum[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		tr[k]=0;
		sum[k]=0;
		if(l == r) 
			return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int tt) {
		if(l == r) {
			++tr[k];
			sum[k]+=to[l];
			return ;
		}
		int mid = ((l+r)>>1);
		if(tt <= mid) updt(ls, l, mid, tt);
		else updt(rs, mid+1, r, tt);
		tr[k]=tr[ls]+tr[rs];
		sum[k]=sum[ls]+sum[rs];
	}
	long long ask(int k, int l, int r, int ak) {
		if(ak == 0) return 0;
		assert(!(l == r && tr[k] < ak));
		if(l == r) return 1LL*to[l]*ak;
		int mid = ((l+r)>>1);
		if(tr[ls] <= ak)
			return sum[ls]+ask(rs, mid+1, r, ak-tr[ls]);
		else
			return ask(ls, l, mid, ak);
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
int comp(thngs AA, thngs BB) {
	if(AA.w == BB.w)
		return AA.v < BB.v;
	return AA.w < BB.w;
}

signed main() {
	freopen("ai.in", "r", stdin);
	freopen("ai.out", "w", stdout);
	read(n), read(m), read(kk);
	kk/=2;
	for(int i = 1; i <= n; ++i)
		read(a[i].v), read(a[i].w);
	if(kk == 0) {
		for(int i = 1; i <= n; ++i)
			if(a[i].v <= m)
				ans=max(ans, a[i].w);
		write(ans, '\n');
		return 0;
	}
	sort(a+1, a+1+n, comp);
	for(int i = 1; i <= n; ++i)
		b[i]=thngs {i, a[i].v}, nd[i]=a[i].v;
	sort(b+1, b+1+n, comp);
	for(int i = 1; i <= n; ++i) {
		if(i == 1 || b[i].w != b[i-1].w)
			to[++cnt]=b[i].w;
		a[b[i].v].v=cnt;
	}
	A.built(1, 1, cnt);
	for(int i = 1; i <= n-kk; ++i) {
		if(i >= kk+1) 
			nd[i]+=A.ask(1, 1, cnt, kk);
		A.updt(1, 1, cnt, a[i].v);
	}
	A.built(1, 1, cnt);
	for(int i = n; i >= kk+1; --i) {
		if(i <= n-kk) 
			nd[i]+=A.ask(1, 1, cnt, kk);
		A.updt(1, 1, cnt, a[i].v);
	}
	for(int i = kk+1; i <= n-kk; ++i)
		if(nd[i] <= m)
			ans=max(ans, a[i].w);
	write(ans, '\n');
	return 0;
}
