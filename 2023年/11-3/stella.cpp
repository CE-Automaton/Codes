#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m, op, ll, rr, L[N], R[N];
struct bit {
	int tr[N];
	void add(int x, int w) {
		while(x <= n) tr[x]+=w, x=x+(x&(-x));
	}
	int ask(int x, int ret = 0) {
		while(x) ret+=tr[x], x=x-(x&(-x));
		return ret;
	}
}A, sum; 
struct tree {
	vector <int> pnt[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void inst(int k, int l, int r, int x) {
		if(L[x] <= l && r <= R[x]) {
			pnt[k].push_back(x);
			return ;
		}
		int mid = ((l+r)>>1);
		if(L[x] <= mid)
			inst(ls, l, mid, x);
		if(mid+1 <= R[x])
			inst(rs, mid+1, r, x);
	}
	void cle(int k, int l, int r, int d) {
		for(int i = 0; i < pnt[k].size(); ++i) {
			int u = pnt[k][i], ad = 0;
			if(L[u] > l) continue;
			while(L[u] <= R[u]) {
				if(A.ask(R[u])-A.ask(L[u]-1) == 0) break;
				++ad;
				L[u]=min(L[u]+u, n+1), R[u]=min(R[u]+u, n);
			}
			if(L[u] != n+1)
				inst(1, 1, n, u);
			sum.add(u, ad);
		}
		pnt[k].clear();
		if(l == r) return ;
		int mid = ((l+r)>>1);
		if(d <= mid)
			cle(ls, l, mid, d);
		else
			cle(rs, mid+1, r, d);
	}
}B;

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

signed main() {
	freopen("stella.in", "r", stdin);
	freopen("stella.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		L[i]=1, R[i]=i, B.inst(1, 1, n, i), sum.add(i, 1);
	for(int i = 1; i <= m; ++i) {
		read(op), read(ll);
		if(op == 1) 
			A.add(ll, 1), B.cle(1, 1, n, ll);
		else
			read(rr), write(sum.ask(rr)-sum.ask(ll-1), '\n');
	}
	FastIO::flusher.~Flusher();
	return 0;
}
