#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, q, m, xx[N], rt[N], trr[N];
struct qwq {
	int l, r;
}a[N];
struct node {
	int ls, rs, w;
};
struct tree {
	int gs;
	node tr[N*23];
	void updt(int& k, int l, int r, int to) {
		tr[++gs]=tr[k];
		k=gs;
		if(l == r) {
			++tr[k].w;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(tr[k].ls, l, mid, to);
		else
			updt(tr[k].rs, mid+1, r, to);
		tr[k].w=tr[tr[k].ls].w+tr[tr[k].rs].w;
	}
	int ask(int k1, int k2, int l, int r, int lq, int rq) {
		if(tr[k2].w-tr[k1].w == 0)
			return 0; 
		if(lq <= l && r <= rq) 
			return tr[k2].w-tr[k1].w;
		int mid = ((l+r)>>1), ret = 0;
		if(lq <= mid)
			ret+=ask(tr[k1].ls, tr[k2].ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			ret+=ask(tr[k1].rs, tr[k2].rs, mid+1, r, lq, rq);
		return ret;
	}
}A;

namespace FastIO
{
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=obuf;
	char* flush(){fwrite(obuf,1,oT-oS,stdout);return oT=obuf;}
	struct Flusher{~Flusher(){flush();}}flusher;
	inline char gc(){return iS==iT && (iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT)?EOF:*iS++;}
	inline void pc(char c){if(oT==oS+SIZE) flush();*oT++=c;}
	#define getchar gc
	#define putchar pc
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
}
using FastIO::gc;
using FastIO::pc;
using FastIO::read;
using FastIO::write;
int comp(qwq AA, qwq BB) {
	return AA.r < BB.r;
}
void add(int x) {
	while(x <= n)
		trr[x]^=1, x+=(x&(-x));
}
int askk(int x, int ret = 0) {
	while(x >= 1)
		ret^=trr[x], x-=(x&(-x));
	return ret;
}

signed main() {
	freopen("badge.in", "r", stdin);
	freopen("badge.out", "w", stdout);
	read(n), read(q);
	int ww = (int) floor(sqrt(n));
//	write(ww, '\n');
	for(int i = 1; i <= n; ++i)
		read(a[i].l), read(a[i].r);
	sort(a+1, a+1+n, comp);
	A.tr[0].w=A.tr[0].ls=A.tr[0].rs=0;
	for(int i = 1, l = 1; i <= n; ++i) {
		rt[i]=rt[i-1];
		while(l <= n && a[l].r <= i)
			A.updt(rt[i], 1, n, a[l].l), ++l;
	}
	for(int i = 1; i <= q; ++i) {
		read(m);
		for(int j = 1; j <= m; ++j)
			read(xx[j]);
		xx[m+1]=n+1;
		int ans = 0;
		if(m <= ww) {//nlogn
			for(int j = 1; j <= m; j+=2)
				for(int ll = 1, rr = j; rr <= m; ++ll, ++rr)
					ans+=A.ask(rt[xx[rr]-1], rt[xx[rr+1]-1], 1, n, xx[ll-1]+1, xx[ll]);
		}
		else {//nlogn
			for(int j = 1; j <= m; ++j)
				add(xx[j]);
			for(int j = 1; j <= n; ++j) {
				int ll = askk(a[j].l-1), rr = askk(a[j].r);
				ans+=(ll^rr);
			}
			for(int j = 1; j <= m; ++j)
				add(xx[j]);
		}
		write(ans, '\n');
	}
	FastIO::flusher.~Flusher(); 
	return 0;
}
