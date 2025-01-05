#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int k, p, q, yy[N], tr[N], gs, rt[N], ll[N], lll[N], rr[N], rrr[N], jc[N], vis[N], fss;
LL xx[N], mn[N], mx[N], mmn[N], mmx[N], L;
vector <int> ad[N];
struct qwq {
	LL w;
	int d;
}b[N];

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
struct treee{
	int ww[N<<2], lzy[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		lzy[k]=0;
		if(l == r) {
			ww[k]=1;
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		ww[k]=(ww[ls]+ww[rs]);
	}
	void down(int k) {
		if(lzy[k]) {
			ww[ls]=ww[rs]=0, lzy[ls]=lzy[rs]=1;
			lzy[k]=0;
		}
	}
	void updt(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) {
			ww[k]=0, lzy[k]=1;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq);
		ww[k]=(ww[ls]+ww[rs]);
	}
	#undef ls
	#undef rs
}A;
struct node {
	int ls, rs, w;
}nd[N*20];
void upup(int k) {
	nd[k].w=nd[nd[k].ls].w+nd[nd[k].rs].w;
}
void updt(int &k, int l, int r, int to) {
	nd[++gs]=nd[k], k=gs;
	if(l == r) {
		nd[k].w=1;
		return ;
	}
	int mid = ((l+r)>>1);
	if(to <= mid)
		updt(nd[k].ls, l, mid, to);
	else
		updt(nd[k].rs, mid+1, r, to);
	upup(k);
}
int ask(int k, int l, int r, int lq, int rq) {
	if(!k) return 0;
	if(lq <= l && r <= rq)
		return nd[k].w;
	int mid = ((l+r)>>1), ret = 0;
	if(lq <= mid)
		ret=ask(nd[k].ls, l, mid, lq, rq);
	if(mid+1 <= rq)
		ret+=ask(nd[k].rs, mid+1, r, lq, rq);
	return ret;
}
int comp(qwq A, qwq B) {
	return A.w < B.w;
}
void add(int x, int w) {
	while(x >= 1)
		tr[x]+=w, x-=(x&(-x));
}
int askk(int x, int ret = 0) {
	while(x <= q)
		ret+=tr[x], x+=(x&(-x));
	return ret;
}
void cf(LL l, LL r, int pd) {
	if(l == r) return ;
	if(r-l >= L)
		l+=1LL*k*L, swap(l, r);
	if(r-l >= L)
		return ;
	// debug(l, r, pd, "???\n");
	LL gsf = (r-L)/L;
	r=(r-L)%L;
	l=l-1-gsf*L;
	if(r < 0)
		r+=L, l+=L;
	// debug(r, l, pd, "!!!\n");
	if(pd) {
		if(l < L) {
			if(r > 0)
				A.updt(1, 0, L-1, 0, r-1);
			if(l < L-1)
				A.updt(1, 0, L-1, l+1, L-1);
		}
		else {
			if(l-L+1 <= r-1)
				A.updt(1, 0, L-1, l-L+1, r-1);
		}
	}
	else {
		if(l < L) {
			A.updt(1, 0, L-1, r, l);
		}
		else {
			A.updt(1, 0, L-1, r, L-1);
			A.updt(1, 0, L-1, 0, l-L);
		}
	}
}

signed main() {
	File("cake");
	read(k), read(L), read(p), read(q);
	jc[0]=1;
	for(int i = 1; i <= k; ++i)
		mn[i]=inf, mx[i]=0, mmx[i]=inf, mmn[i]=0, jc[i]=1LL*jc[i-1]*i%p;
	for(int i = 1; i <= q; ++i)
		read(xx[i]), read(yy[i]), b[i]=qwq {xx[i], i}, ll[i]=lll[i]=rr[i]=rrr[i]=-1;
	sort(b+1, b+1+q, comp);
	for(int i = 1; i <= q; ++i) 
		xx[b[i].d]=i;
	nd[0]=node {0, 0, 0};
	for(int i = 1; i <= q; ++i)
		rt[i]=rt[i-1], updt(rt[i], 1, q, xx[i]), ad[yy[i]].push_back(i);
	for(int i = 1; i <= k; ++i) {
		for(int j = 0; j < ad[i].size(); ++j) {
			add(xx[ad[i][j]], 1);
			int l = 1, r = xx[ad[i][j]]-1, op = -1;
			while(l <= r) {
				int mid = ((l+r)>>1);
				if(ask(rt[ad[i][j]], 1, q, mid, xx[ad[i][j]])-(askk(mid)-askk(xx[ad[i][j]]+1)))
					op=mid, l=mid+1;
				else
					r=mid-1;
			}
			ll[ad[i][j]]=op;
			if(op == -1) {
				l = xx[ad[i][j]]+1, r = q, op = -1;
				while(l <= r) {
					int mid = ((l+r)>>1);
					if(ask(rt[ad[i][j]], 1, q, mid, q)-askk(mid))
						op=mid, l=mid+1;
					else
						r=mid-1;
				}
				lll[ad[i][j]]=op;
			}
			l = xx[ad[i][j]]+1, r = q, op = -1;
			while(l <= r) {
				int mid = ((l+r)>>1);
				if(ask(rt[ad[i][j]], 1, q, xx[ad[i][j]], mid)-(askk(xx[ad[i][j]])-askk(mid+1)))
					op=mid, r=mid-1;
				else
					l=mid+1;
			}
			rr[ad[i][j]]=op;
			if(op == -1) {
				l = 1, r = xx[ad[i][j]]-1, op = -1;
				while(l <= r) {
					int mid = ((l+r)>>1);
					if(ask(rt[ad[i][j]], 1, q, 1, mid)-(askk(1)-askk(mid+1)))
						op=mid, r=mid-1;
					else
						l=mid+1;
				}
				rrr[ad[i][j]]=op;
			}
		}
		for(int j = 0; j < ad[i].size(); ++j) 
			add(xx[ad[i][j]], -1);
	}
	// for(int i = 1; i <= q; ++i)
	// 	debug(ll[i], lll[i], rr[i], rrr[i], "???\n");
	A.built(1, 0, L-1);
	int pd = 0;
	fss=k;
	for(int i = 1; i <= q; ++i) {
		mn[yy[i]]=min(mn[yy[i]], xx[i]), mx[yy[i]]=max(mx[yy[i]], xx[i]);
		if(b[xx[i]].w <= L)
			mmn[yy[i]]=max(mmn[yy[i]], xx[i]);
		if(b[xx[i]].w >= 1LL*k*L-L)
			mmx[yy[i]]=min(mmx[yy[i]], xx[i]);
		if(b[mx[yy[i]]].w-b[mn[yy[i]]].w >= L && (mmx[yy[i]] != inf && mmn[yy[i]] && 1LL*k*L+b[mmn[yy[i]]].w-b[mmx[yy[i]]].w >= L))
			pd|=1;
		// debug(pd, "???\n");
		if(pd) {
			putchar('0');
			putchar('\n');
			continue;
		}
		if(!vis[yy[i]])
			--fss, vis[yy[i]]=1;
		if(b[mx[yy[i]]].w-b[mn[yy[i]]].w < L)
			cf(b[mn[yy[i]]].w, b[mx[yy[i]]].w, 1);
		if(mmx[yy[i]] != inf && mmn[yy[i]] && 1LL*k*L+b[mmn[yy[i]]].w-b[mmx[yy[i]]].w < L)
			cf(b[mmn[yy[i]]].w, b[mmx[yy[i]]].w, 1);
		if(ll[i] != -1)
			cf(b[ll[i]].w, b[xx[i]].w, 0);
		else
			if(lll[i] != -1)
				cf(b[xx[i]].w, b[lll[i]].w, 0);
		if(rr[i] != -1)
			cf(b[xx[i]].w, b[rr[i]].w, 0);
		else
			if(rrr[i] != -1)
				cf(b[rrr[i]].w, b[xx[i]].w, 0);
		write(1LL*jc[fss]*A.ww[1]%p, '\n');
	}
	FastIO::flusher.~Flusher();
	return 0;
}