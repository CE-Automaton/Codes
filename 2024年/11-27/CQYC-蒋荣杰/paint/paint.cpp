#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, m, mm, q, c[N], a[N][8], opt;
LL lstans, ll, rr;

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
struct node {
	LL a[10][10], b[5];
}ans, tr[N<<2];
#define ls (k<<1)
#define rs (ls|1)
node upup(node A, node B) {
	node ret;
	for(int i = 0; i < mm; ++i)
		for(int j = 0; j < mm; ++j) {
			LL mx = -inf;
			for(int k = 0; k < m; ++k) 
				mx=max(mx, max(max(A.a[i][k]+B.a[k+m][j], A.a[i][k+m]+B.a[k][j]), A.a[i][k]+B.a[k][j]));
			ret.a[i][j]=mx;
		}
	for(int i = 0; i < mm; ++i)
		for(int p = m; p < mm; ++p)
			if(A.a[i][p] >= 0)//卡常,满足这个的p好像最多1个
				for(int k = m; k < mm; ++k)
					for(int j = 0; j < mm; ++j)
						ret.a[i][j]=max(ret.a[i][j], A.a[i][p]+B.a[k][j]);
	for(int i = 0; i < m; ++i) {
		ret.b[i]=A.b[i]+B.b[i];
		for(int j = 0; j < mm; ++j)
			ret.a[i][j]=max(ret.a[i][j], A.b[i]+max(B.a[i][j], B.a[i+m][j])), 
			ret.a[j][i]=max(ret.a[j][i], max(A.a[j][i], A.a[j][i+m])+B.b[i]);
	}
	return ret;
}
void built(int k, int l, int r) {
	if(l == r) {
		for(int i = 0; i < mm; ++i)
			for(int j = 0; j < mm; ++j)
				tr[k].a[i][j]=-inf;
		tr[k].a[c[l]+m][c[l]+m]=a[l][c[l]];
		for(int i = 0; i < m; ++i) 
			tr[k].b[i]=a[l][i];
		return ;
	};
	int mid = ((l+r)>>1);
	built(ls, l, mid);
	built(rs, mid+1, r);
	tr[k]=upup(tr[ls], tr[rs]);
}
void updt(int k, int l, int r, int to) {
	if(l == r) {
		for(int i = m; i < mm; ++i)
			tr[k].a[i][i]=-inf;
		tr[k].a[c[l]+m][c[l]+m]=a[l][c[l]];
		return ;
	}
	int mid = ((l+r)>>1);
	if(to <= mid)
		updt(ls, l, mid, to);
	else
		updt(rs, mid+1, r, to);
	tr[k]=upup(tr[ls], tr[rs]);
}
node ask(int k, int l, int r, int lq, int rq) {
	if(lq <= l && r <= rq)
		return tr[k];
	int mid = ((l+r)>>1);
	if(lq <= mid && mid < rq)
		return upup(ask(ls, l, mid, lq, rq), ask(rs, mid+1, r, lq, rq));
	if(lq <= mid)
		return ask(ls, l, mid, lq, rq);
	else
		return ask(rs, mid+1, r, lq, rq);
}

signed main() {
	File("paint");
	read(n), read(m), read(q);
	mm=m+m;
	for(int i = 1; i <= n; ++i)
		read(c[i]), --c[i];
	for(int i = 1; i <= n; ++i) 
		for(int j = 0; j < m; ++j)
			read(a[i][j]);
	built(1, 1, n);
	ans=tr[1];
	lstans=0;
	for(int i = m; i < mm; ++i)
		for(int j = m; j < mm; ++j)
			lstans=max(lstans, ans.a[i][j]);
	write(lstans, '\n');
	for(int i = 1; i <= q; ++i) {
		read(opt), read(ll), read(rr);
		ll^=lstans, rr^=lstans;
		if(opt == 1)
			c[ll]=rr-1, updt(1, 1, n, ll);
		else {
			ans=ask(1, 1, n, ll, rr);
			lstans=0;
			for(int i = m; i < mm; ++i)
				for(int j = m; j < mm; ++j)
					lstans=max(lstans, ans.a[i][j]);
			write(lstans, '\n');
		}
	}
	FastIO::flusher.~Flusher();
	return 0;
}
/*
3 2 4
2 1 2
4 4
2 4
3 1
2 8 10
1 11 8
2 10 10
1 0 0*/