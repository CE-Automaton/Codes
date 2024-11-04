#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5, Q = 5e5+5;
int t, n, ppp, q, u, v, w, cnt, dfn[N], tt[N], siz[N], ola[N<<1], in[N], dep[N], st[N<<1][21];
LL w1[N], w2[N], ans[Q];
struct qwq { int t, d; };
vector <qwq> t1[N], t2[N], que[N];

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
void dfs(int x, int fa) {
	dfn[++cnt]=x, tt[x]=cnt, siz[x]=1;
	for(int t = 0; t < t1[x].size(); ++t) {
		qwq y = t1[x][t];
		if(y.t != fa)
			w1[y.t]=w1[x]+y.d, dfs(y.t, x), siz[x]+=siz[y.t];
	}
}
void dfs2(int x, int fa) {
	ola[++cnt]=x, in[x]=cnt, dep[x]=dep[fa]+1;
	for(int t = 0; t < t2[x].size(); ++t) {
		qwq y = t2[x][t];
		if(y.t != fa)
			w2[y.t]=w2[x]+y.d, dfs2(y.t, x), ola[++cnt]=x;
	}
}
int mmn(int x, int y) {
	return (dep[x] < dep[y] ? x : y);
}
int lca(int x, int y) {
	if(x > y) swap(x, y);
	int lg = __lg(y-x+1);
	return mmn(st[x][lg], st[y-(1<<lg)+1][lg]);
}
LL diss(int x, int y) {;
	return w2[x]+w2[y]-w2[lca(in[x], in[y])]*2;
}
struct qvq { int a, b; LL wa, wb, lzy; };
struct tree {//维护直径
	qvq tr[N<<2];
	qvq upup(qvq A, qvq B) {
		qvq ret;
		LL ab = diss(A.a, A.b)+A.wa+A.wb, ac = diss(A.a, B.a)+A.wa+B.wa, ad = diss(A.a, B.b)+A.wa+B.wb,
		bc = diss(A.b, B.a)+A.wb+B.wa, bd = diss(A.b, B.b)+A.wb+B.wb, cd = diss(B.a, B.b)+B.wa+B.wb, 
		mx=max({ab, ac, ad, bc, bd, cd});
		if(mx == ab) ret=A;
		else if(mx == ac) ret=qvq {A.a, B.a, A.wa, B.wa, 0};
		else if(mx == ad) ret=qvq {A.a, B.b, A.wa, B.wb, 0};
		else if(mx == bc) ret=qvq {A.b, B.a, A.wb, B.wa, 0};
		else if(mx == bd) ret=qvq {A.b, B.b, A.wb, B.wb, 0};
		else ret=B;
		ret.lzy=0;
		return ret;
	}
	#define ls (k<<1)
	#define rs (ls|1)
	void down(int k) {
		if(tr[k].lzy == 0) return ;
		tr[ls].wa+=tr[k].lzy;
		tr[ls].wb+=tr[k].lzy;
		tr[ls].lzy+=tr[k].lzy;
		tr[rs].wa+=tr[k].lzy;
		tr[rs].wb+=tr[k].lzy;
		tr[rs].lzy+=tr[k].lzy;
		tr[k].lzy=0;
	}
	void built(int k, int l, int r) {
		tr[k].lzy=0;
		if(l == r) {
			tr[k]=qvq {dfn[l], dfn[l], w1[dfn[l]], w1[dfn[l]], 0};
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		tr[k]=upup(tr[ls], tr[rs]);
	}
	void updt(int k, int l, int r, int lq, int rq, LL www) {
		// debug(l, r, lq, rq, www, "?\n");
		if(lq <= l && r <= rq) {
			tr[k].wa+=www, tr[k].wb+=www, tr[k].lzy+=www;
			// debug(tr[k].a, tr[k].wa, "!!!\n");
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq, www);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq, www);
		tr[k]=upup(tr[ls], tr[rs]);
	}
}A;
void getans(int x, int fa) {
	// debug(x, tt[x], "???\n");
	for(int t = 0; t < que[x].size(); ++t) {
		qwq y = que[x][t];
		ans[y.d]=max(diss(A.tr[1].a, y.t)+A.tr[1].wa, diss(A.tr[1].b, y.t)+A.tr[1].wb);
		// debug(A.tr[1].wa, A.tr[1].wb, "!!!\n");
	}
	for(int t = 0; t < t1[x].size(); ++t) {
		qwq y = t1[x][t];
		if(y.t != fa) {
			A.updt(1, 1, n, 1, n, y.d), A.updt(1, 1, n, tt[y.t], tt[y.t]+siz[y.t]-1, -2*y.d);
			getans(y.t, x);
			A.updt(1, 1, n, tt[y.t], tt[y.t]+siz[y.t]-1, 2*y.d), A.updt(1, 1, n, 1, n, -y.d);
		}
	}
}

signed main() {
	File("move");
	read(t);
	while(t--) {
		read(n);
		for(int i = 1; i <= n; ++i)
			t1[i].clear(), t2[i].clear(), que[i].clear(), w1[i]=w2[i]=0;
		for(int i = 2; i <= n; ++i)
			read(u), read(v), read(w), 
			t1[u].push_back(qwq {v, w}),
			t1[v].push_back(qwq {u, w});
		cnt=0, dfs(1, 0);
		for(int i = 2; i <= n; ++i)
			read(u), read(v), read(w), 
			t2[u].push_back(qwq {v, w}),
			t2[v].push_back(qwq {u, w});
		cnt=0, dfs2(1, 0);
		for(int i = 1; i <= cnt; ++i)
			st[i][0]=ola[i];
		ppp=__lg(cnt);
		for(int i = 1; i <= ppp; ++i)
			for(int j = 1; j+(1<<(i-1)) <= cnt; ++j)
				st[j][i]=mmn(st[j][i-1], st[j+(1<<(i-1))][i-1]);
		A.built(1, 1, n);
		read(q);
		for(int i = 1; i <= q; ++i)
			read(u), read(v), que[u].push_back(qwq {v, i});
		getans(1, 0);
		for(int i = 1; i <= q; ++i)
			write(ans[i], '\n');
	}
	FastIO::flusher.~Flusher();
	return 0;
}