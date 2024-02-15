#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int k, n, q, a[N], b[N], c[N], d[N], tc[N], td[N], w[N], t, xx, yy, rt[N], ppd, zhan[N], tot;
struct qwq {
	int w, t;
}aa[N], ans;
struct tree {
	int pd[N<<2], tr[N<<2][2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		pd[k]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void add(int k, int l, int r, int lq, int rq, int ll, int rr) {
		if(lq <= l && r <= rq) {
			if(pd[k])
				tr[k][0]=min(tr[k][0], ll), 
				tr[k][1]=max(tr[k][1], rr);
			else
				tr[k][0]=ll, 
				tr[k][1]=rr;
			pd[k]=1;
			return ;
		}
		int mid = ((l+r)>>1);
		if(lq <= mid)
			add(ls, l, mid, lq, rq, ll, rr);
		if(mid+1 <=rq)
			add(rs, mid+1, r, lq, rq, ll, rr);
	}
	void ask(int k, int l, int r, int to) {
		if(pd[k]) {
			if(ppd)
				ans.w=min(tr[k][0], ans.w), 
				ans.t=max(tr[k][1], ans.t);
			else
				ans.w=tr[k][0], 
				ans.t=tr[k][1];
			ppd=1;
		}
		if(l == r) return ;
		int mid = ((l+r)>>1);
		if(to <= mid)
			ask(ls, l, mid, to);
		else
			ask(rs, mid+1, r, to);
	}
}AA;

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
int comp(qwq A, qwq B) {
	return A.w < B.w;
}
int findcd(int x, int pd, int azz) {
	int l = 1, r = n, ret = 1;
	while(l <= r) {
		int mid = ((l+r)>>1);
		if(azz) {
			if((pd ? tc[mid] : td[mid]) <= x)
				ret=mid, l=mid+1;
			else
				r=mid-1;
		}
		else {
			if(x <= (pd ? tc[mid] : td[mid]))
				ret=mid, r=mid-1;
			else
				l=mid+1;
		} 
	}
	return ret;
}

signed main() {
	File("spy");
	read(k), read(n), read(q);
	for(int i = 1; i <= k; ++i)
		read(a[i]), read(b[i]);
	for(int i = 1; i <= n; ++i)
		read(c[i]), read(d[i]), read(w[i]), 
		aa[i]=qwq {c[i], i};
	sort(aa+1, aa+1+n, comp);
	for(int i = 1; i <= n; ++i)
		tc[i]=aa[i].w, c[aa[i].t]=i, 
		aa[i]=qwq {d[i], i};
	sort(aa+1, aa+1+n, comp);
	for(int i = 1; i <= n; ++i)
		td[i]=aa[i].w, d[aa[i].t]=i;
//	for(int i = 1; i <= n; ++i)
//		debug(c[i], d[i], '\n');
	for(int i = 1; i <= q; ++i) {
		read(xx), read(yy), read(t);
		AA.built(1, 1, n), ppd=0;
		LL anss = 0; 
		for(int j = 1; j <= (1<<k)-1; ++j) {
			tot=0;
			for(int p = 0; p < k; ++p) 
				if((j>>p)&1)
					zhan[++tot]=p+1;
			for(int jj = 0; jj <= (1<<tot)-1; ++jj) {
				int as = 0, bs = 0;
				for(int op = 0; op < k; ++op)
					if((jj>>op)&1) as+=a[zhan[op+1]], bs+=b[zhan[op+1]];
					else as-=a[zhan[op+1]], bs-=b[zhan[op+1]];
				int lc = xx+as*t, rc = xx, 
				ld = yy+bs*t, rd = yy;
				if(lc > rc) swap(lc, rc);
				if(ld > rd) swap(ld, rd);
//				debug(lc, rc, ld, rd, '\n');
				lc=findcd(lc, 1, 0), rc=findcd(rc, 1, 1);
				ld=findcd(ld, 0, 0), rd=findcd(rd, 0, 1);
//				debug(lc, rc, ld, rd, "?????\n");
				if(lc <= rc && ld <= rd)
					AA.add(1, 1, n, lc, rc, ld, rd); 
			}
		}
		for(int j = 1; j <= n; ++j) {
			ppd=0;
			AA.ask(1, 1, n, c[j]);
			if(ans.w <= d[j] && d[j] <= ans.t)
				anss+=w[j]/*, debug(j), debug(' ')*/;
		}
//		debug("???\n");
		write(anss, '\n');
	}
	return 0;
}
