#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 5e5+5;
int n, a[N], q, xx[N], yy[N], cnt, trr[N<<1];
struct qwq {
	LL w;
	int d;
}b[N<<1];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
namespace FastIO {
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
int comp(qwq A, qwq B) {
	return A.w < B.w;
}
void add(int x, int w) {
	while(x <= cnt)
		trr[x]+=w, x+=(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x >= 1)
		ret+=trr[x], x-=(x&(-x));
	return ret;
}
struct tree {
	int tr[N<<4], lzy[N<<4];
	#define ls (k<<1)
	#define rs (ls|1)
	void down(int k) {
		if(lzy[k] == 0) return ;
		tr[ls]+=lzy[k], lzy[ls]+=lzy[k];
		tr[rs]+=lzy[k], lzy[rs]+=lzy[k];
		lzy[k]=0;
	}
	void built(int k, int l, int r) {
		tr[k]=inf, lzy[k]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int to, int w) {
		if(l == r) {
			tr[k]=w, lzy[k]=0;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls, l, mid, to, w);
		else
			updt(rs, mid+1, r, to, w);
		tr[k]=min(tr[ls], tr[rs]);
	}
	void updtt(int k, int l, int r, int lq, int rq, int w) {
		if(lq <= l && r <= rq) {
			tr[k]+=w, lzy[k]+=w;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updtt(ls, l, mid, lq, rq, w);
		if(mid+1 <= rq)
			updtt(rs, mid+1, r, lq, rq, w);
		tr[k]=min(tr[ls], tr[rs]);
	}
}A;

signed main() {
	File("sort");
	read(n), read(q);
	for(int i = 1; i <= n; ++i) 
		read(a[i]), b[i]=qwq {a[i]*1000000LL+i, i};
	for(int i = 1; i <= q; ++i)
		read(xx[i]), read(yy[i]), b[i+n]=qwq {yy[i]*1000000LL+xx[i], i+n};
	sort(b+1, b+1+n+q, comp);
	for(int i = 1; i <= n+q; ++i) {
		if(i == 1 || b[i].w != b[i-1].w)
			++cnt;
		if(b[i].d <= n) a[b[i].d]=cnt;
		else yy[b[i].d-n]=cnt;
	}
	for(int i = 1; i <= n; ++i) 
		add(a[i], 1);
	A.built(1, 1, cnt);
	for(int i = 1; i <= n; ++i)
		A.updt(1, 1, cnt, a[i], ask(a[i])-i);
	for(int i = 1; i <= q; ++i) {
		add(a[xx[i]], -1);
		A.updt(1, 1, cnt, a[xx[i]], inf);
		A.updtt(1, 1, cnt, a[xx[i]]+1, cnt, -1);
		add(yy[i], 1);
		a[xx[i]]=yy[i];
		A.updt(1, 1, cnt, yy[i], ask(yy[i])-xx[i]);
		A.updtt(1, 1, cnt, yy[i]+1, cnt, 1);
		write(-A.tr[1], '\n');
	}
	FastIO::flusher.~Flusher();
	return 0;
}