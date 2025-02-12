#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned int unt;
const int N = 2e5+5;
const unt fufu = -1;
int n, q, u, v, siz[N], msz[N], top[N], up[N], dfn[N], nfd[N], cntt, tot, len, cnt, zzz[N];
unt w, www[N], wws[N], tr[N<<2], ww[N<<2], lzy[N<<2], sum, ans[N];
struct qwq{ int lp, rp, dd; }x[N];
vector <qwq> to[1005];
struct qvq { int t; unt ww; };
vector <qvq> tt[N];

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
	if(zzz[A.lp] == zzz[B.lp])
		return A.rp < B.rp;
	return zzz[A.lp] < zzz[B.lp];
}
void dfs(int x, int fa) {
	siz[x]=1, up[x]=fa;
	for(qvq y : tt[x])
		if(y.t != fa) 
			www[y.t]=www[x]+y.ww, wws[y.t]=y.ww, dfs(y.t, x),
			siz[x]+=siz[y.t], msz[x]=(siz[msz[x]] > siz[y.t] ? msz[x] : y.t);
}
void ddfs(int x, int fa, int tp) {
	top[x]=tp, dfn[x]=++cntt, nfd[cntt]=x;
	if(msz[x])
		ddfs(msz[x], x, tp);
	for(qvq y : tt[x])
		if(y.t != fa && y.t != msz[x])
			ddfs(y.t, x, y.t);
}
#define ls (k<<1)
#define rs (ls|1)
void built(int k, int l, int r) {
	tr[k]=lzy[k]=0;
	if(l == r) {
		ww[k]=wws[nfd[l]];
		return ;
	}
	int mid = ((l+r)>>1);
	built(ls, l, mid);
	built(rs, mid+1, r);
	ww[k]=(ww[ls]+ww[rs]);
}
void down(int k) {
	if(lzy[k] != 0) {
		tr[ls]+=lzy[k]*ww[ls], tr[rs]+=lzy[k]*ww[rs];
		lzy[ls]+=lzy[k], lzy[rs]+=lzy[k];
		lzy[k]=0;
	}
}
void updt(int k, int l, int r, int lq, int rq, unt sw) {
	if(lq <= l && r <= rq) {
		tr[k]+=sw*ww[k];
		lzy[k]+=sw;
		return ;
	}
	down(k);
	int mid = ((l+r)>>1);
	if(lq <= mid)
		updt(ls, l, mid, lq, rq, sw);
	if(mid < rq)
		updt(rs, mid+1, r, lq, rq, sw);
	tr[k]=tr[ls]+tr[rs];
}
unt ask(int k, int l, int r, int lq, int rq) {
	if(lq <= l && r <= rq)
		return tr[k];
	down(k);
	int mid = ((l+r)>>1);
	unt ret = 0;
	if(lq <= mid)
		ret+=ask(ls, l, mid, lq, rq);
	if(mid < rq)
		ret+=ask(rs, mid+1, r, lq, rq);
	return ret;
}
#undef ls
#undef rs 
inline void add(int x) {
	// debug("+", x, "?\n");
	while(x) {
		sum+=ask(1, 1, n, dfn[top[x]], dfn[x]);
		updt(1, 1, n, dfn[top[x]], dfn[x], 1);
		x=up[top[x]];
	}
}
inline void dlt(int x) {
	// debug("-", x, "?\n");
	while(x) {
		updt(1, 1, n, dfn[top[x]], dfn[x], fufu);
		sum-=ask(1, 1, n, dfn[top[x]], dfn[x]);
		x=up[top[x]];
	}
}
void bl(qwq y) {
	for(int i = y.lp; i <= y.rp; ++i)
		add(i);
	ans[y.dd]-=sum*2;
	for(int i = y.lp; i <= y.rp; ++i)
		dlt(i);
}

signed main() {
	File("memory");
	read(n), read(q);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), read(w), tt[u].push_back(qvq {v, w}), tt[v].push_back(qvq {u, w});
	dfs(1, 0);
	ddfs(1, 0, 1);//重剖
	built(1, 1, n);
	for(int i = 1; i <= n; ++i)
		www[i]=www[i-1]+www[i];
	tot=sqrt(n);//分块
	len=(int) ceil(n*1.0/tot);
	for(int i = 1; i <= n; ++i)
		zzz[i]=i/len+(i%len != 0);
	LL ss = 0;
	for(int i = 1; i <= q; ++i) 
		read(x[i].lp), read(x[i].rp), x[i].dd=i, 
		ans[i]=(unt) (www[x[i].rp]-www[x[i].lp-1])*(x[i].rp-x[i].lp), 
		ss+=x[i].rp-x[i].lp+1;
	sort(x+1, x+1+q, comp);
	for(int i = 1; i <= q; ++i) 
		to[zzz[x[i].lp]].push_back(x[i]);
	for(int i = 1; i <= tot; ++i) {
		int rs=min(n, i*len), l = rs, r = rs+1;
		for(int j = 0; j < to[i].size(); ++j) {
			qwq v = to[i][j];
			if(zzz[v.rp] == i) {//可以直接处理的块
				bl(v);
				continue;
			}
			while(r <= v.rp) {//扩展右端点
				add(r);
				++r;
			}
			l = rs;
			while(l >= v.lp) {//移左端点
				add(l);
				--l;
			}
			ans[v.dd]-=sum*2;
			while(l < rs) {
				++l;
				dlt(l);
			}
		}
		while(r > rs+1)
			--r, dlt(r);
	}
	for(int i = 1; i <= q; ++i)
		write(ans[i], '\n');
	FastIO::flusher.~Flusher();
	return 0;
}