#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int N = 1e6+6;
int n, a[N], b[N], tt[N], rr[N], pa[N<<1], pb[N<<1], tr[N<<2], gs[N<<2], ww[N<<2], fa[N], cnt[N], p, vis[N], lll[N], rrr[N];
vector <int> to[N];
set<int> lx, rx;

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
int find(int x) { return (x == fa[x] ? x : fa[x]=find(fa[x])); }
void merge(int x, int y) {
	// debug(x, y, "???\n");
	x=find(x), y=find(y);
	if(x == y) return ;
	if(cnt[x] > cnt[y]) swap(x, y);
	fa[x]=y, cnt[y]+=cnt[x];
}
#define ls (k<<1)
#define rs (ls|1)
void upup(int k, int l, int r) {
	gs[k]=gs[ls]+gs[rs];
	if(gs[k] == r-l+1)
		tr[k]=1, ww[k]=0;
}
void built(int k, int l, int r) {
	if(l == r) {
		tr[k]=2, ww[k]=tt[l];
		return ;
	}
	int mid = ((l+r)>>1);
	built(ls, l, mid);
	built(rs, mid+1, r);
}
void updt(int k, int l, int r, int lq, int rq, int rt) {
	if(tr[k] == 1) return ;
	if(tr[k] == 2) {
		// debug(l, r, "?\n");
		merge(rt, ww[k]);
		return ;
	}
	int mid = ((l+r)>>1);
	updt(ls, l, mid, lq, rq, rt);
	updt(rs, mid+1, r, lq, rq, rt);
	tr[k]=2, ww[k]=find(rt);
	upup(k, l, r);
}
void dlt(int k, int l, int r, int to) {
	if(l == r) {
		tr[k]=1;
		ww[k]=0;
		gs[k]=1;
		return ;
	}
	int mid = ((l+r)>>1);
	if(to <= mid)
		dlt(ls, l, mid, to);
	else
		dlt(rs, mid+1, r, to);
	upup(k, l, r);
}
void mrge(int k, int l, int r, int lq, int rq, int rt) {
	if(tr[k] == 1) return ;
	if(tr[k] == 2) {
		// debug(l, r, "?\n");
		merge(rt, ww[k]);
		return ;
	}
	if(lq <= l && r <= rq) {
		updt(k, l, r, lq, rq, rt);
		return ;
	}
	int mid = ((l+r)>>1);
	if(lq <= mid)
		mrge(ls, l, mid, lq, rq, rt);
	if(mid < rq)
		mrge(rs, mid+1, r, lq, rq, rt);
	upup(k, l, r);
}
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*x*ret%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}

signed main() {
	File("v");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), read(b[i]), 
		pa[a[i]]=i, pb[b[i]]=i, fa[i]=i, cnt[i]=1;
	lx.insert(10000000);
	for(int i = 1; i <= n+n; ++i) 
		if(pa[i]) {
			auto itl = lx.upper_bound(b[pa[i]]);
			if(itl != lx.begin()) {
				--itl;
				if(*itl >= i)
					lll[pa[i]]=(*itl);
			}
			lx.insert(b[pa[i]]);
		}
	for(int i = n+n; i >= 1; --i) 
		if(pb[i]) {
			auto itr = rx.lower_bound(a[pb[i]]);
			if(itr != rx.end())
				if(*itr <= i)
					rrr[pb[i]]=(*itr);
			rx.insert(a[pb[i]]);
		}
	for(int i = 1; i <= n; ++i)
		if(lll[i] && rrr[i] && lll[i] >= rrr[i]) {
			write(0, '\n');
			FastIO::flusher.~Flusher();
			return 0;
		}
	for(int i = 1, j = 0; i <= n+n; ++i)
		if(pb[i])
			++j, b[pb[i]]=j, tt[j]=pb[i];
	int lst = -1;
	for(int i = n+n; i >= 1; --i) 
		if(pb[i])
			lst=b[pb[i]];
		else
			rr[pa[i]]=lst;
	built(1, 1, n);
	for(int i = n+n; i >= 1; --i) 
		if(pa[i]) {
			dlt(1, 1, n, b[pa[i]]);
			if(rr[pa[i]] < b[pa[i]])
				mrge(1, 1, n, rr[pa[i]], b[pa[i]]-1, pa[i]);
			// debug(pa[i], rr[pa[i]], b[pa[i]], "!???\n");
		}
	for(int i = 1; i <= n; ++i)
		if(find(i) == i)
			++p;
	write(ksm(2, p), '\n');
	FastIO::flusher.~Flusher();
	return 0;
}