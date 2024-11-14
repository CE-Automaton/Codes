#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, q, l, r, a[N], b[N][2], tot, zhan[N], sum[N][35];

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
	int op, pdd, tr[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k]=b[l][op];
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		tr[k]=(pdd ? (tr[ls]|tr[rs]) : (tr[ls]&tr[rs]));
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		int mid = ((l+r)>>1);
		if(lq <= mid && mid+1 <= rq)
			return (pdd ? (ask(ls, l, mid, lq, rq)|ask(rs, mid+1, r, lq, rq)) : (ask(ls, l, mid, lq, rq)&ask(rs, mid+1, r, lq, rq)));
		if(lq <= mid)
			return ask(ls, l, mid, lq, rq);
		else
			return ask(rs, mid+1, r, lq, rq);
	}
}A[4];

signed main() {
	File("bit");
	read(n), read(q);
	int pd1 = 1, pd2 = 1;
	for(int i = 1; i <= n; ++i)
		read(a[i]), pd1&=((a[i]&(-a[i])) == a[i]), pd2&=(((a[i]+1)&(-(a[i]+1))) == a[i]+1);
	if(pd1) {
		// debug("sub2\n");
		for(int i = 1; i <= n; ++i) {
			a[i]=__lg(a[i]);
			for(int j = 0; j <= 30; ++j)
				sum[i][j]=sum[i-1][j];
			++sum[i][a[i]];
		}
		for(int i = 1; i <= q; ++i) {
			read(l), read(r);
			if(l == r) {
				puts("NO");
				continue;
			}
			int gs = 0;
			for(int j = 0; j <= 30; ++j)
				if(sum[r][j]-sum[l-1][j])
					++gs;
			if(gs == 1) 
				puts("YES");
			else
				puts("NO");
		}
		return 0;
	}
	if(pd2) {
		// debug("sub3\n");
		for(int i = 1; i <= n; ++i) {
			++a[i];
			a[i]=__lg(a[i]);
			for(int j = 0; j <= 30; ++j)
				sum[i][j]=sum[i-1][j];
			++sum[i][a[i]];
		}
		for(int i = 1; i <= q; ++i) {
			read(l), read(r);
			if(l == r) {
				puts("NO");
				continue;
			}
			int gs = 0;
			for(int j = 0; j <= 30; ++j)
				if(sum[r][j]-sum[l-1][j] >= 2)
					++gs;
			if(gs >= 1) 
				puts("YES");
			else
				puts("NO");
		}
		return 0;
	}
	if(n <= 20 && q <= 5) {
		for(int i = 1; i <= q; ++i) {
			read(l), read(r);
			if(l == r) {
				puts("NO");
				continue;
			}
			tot=0;
			int pd = 0;
			for(int j = l; j <= r; ++j)
				zhan[++tot]=j;
			for(int j = 1; j < (1<<tot)-1; ++j) {
				int x = 0, y = (1<<30)-1;
				for(int k = 0; k < tot; ++k)
					if((j>>k)&1)
						x|=a[zhan[k+1]];
					else
						y&=a[zhan[k+1]];
				pd|=(x == y);
			}
			if(pd)
				puts("YES");
			else
				puts("NO");
		}
		return 0;
	}
	for(int i = 1; i <= n; ++i)
		b[i][0]=a[i], b[i][1]=(((1<<30)-1)^a[i]);
	A[0].op=0, A[1].op=0, A[2].op=1, A[3].op=1;
	A[0].pdd=0, A[1].pdd=1, A[2].pdd=0, A[3].pdd=1;
	A[0].built(1, 1, n);
	A[1].built(1, 1, n);
	A[2].built(1, 1, n);
	A[3].built(1, 1, n);
	for(int i = 1; i <= 10; ++i) {
		read(l), read(r);
		if(l == r) {
			puts("NO");
			continue;
		}
		int aa = A[0].ask(1, 1, n, l, r), bb = A[1].ask(1, 1, n, l, r), cc = A[2].ask(1, 1, n, l, r), dd = A[3].ask(1, 1, n, l, r);
		if((aa+cc) == (aa|cc) && (bb+dd) == (bb|dd))
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}