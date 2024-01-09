#include <bits/stdc++.h>
#define uLL unsigned long long
#define TPLT template <typename T>
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
const uLL base = 1e5+3;
const int N = 1e5+5;
int n, q, col[N], sz[N], pro, a, b, c, d;
uLL bs[N];
vector <int> son[N];
TPLT inline void read(T& r){
	r=0; int f=1; char c=getchar(); while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
	while(isdigit(c)) r=(r<<1)+(r<<3)+(c^48), c=getchar(); r*=f;
}
int len; char put[78];
TPLT inline void write(T x) {
	if(x < 0) putchar('-'), x=-x;
	do {put[++len]=x%10, x/=10;}while(x);
	while(len) putchar(put[len--]^48); putchar(' ');
}
struct tree {
	uLL s[N<<2], t[N<<2];
	int len[N<<2];
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void upup(int k) {
		s[k]=s[ls]*bs[len[rs]]+s[rs];
		t[k]=t[ls]+t[rs]*bs[len[ls]];
	}
	void built(int k, int l, int r) {
		len[k]=r-l+1;
		if(l == r) { t[k]=s[k]=col[l]; return ; } 
		int mid = ((l+r)>>1);
		built(ls, l, mid), built(rs, mid+1, r);
		upup(k);
	}
	void updt(int k, int l, int r, int to) {
		if(l == r) { t[k]=s[k]=col[to]; return ; } 
		int mid = ((l+r)>>1);
		if(mid >= to) updt(ls, l, mid, to);
		else updt(rs, mid+1, r, to);
		upup(k);
	}
	uLL asks(int k, int l, int r, int L, int R) {
		if(L <= l && r <= R) return s[k];
		int mid = ((l+r)>>1);
		if(mid >= L && mid+1 <= R) return asks(ls, l, mid, L, mid)*bs[R-mid]+asks(rs, mid+1, r, mid+1, R);
		else if(mid >= L) return asks(ls, l, mid, L, R);
		else return asks(rs, mid+1, r, L, R);
	}
	uLL askt(int k, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[k];
		int mid = ((l+r)>>1);
		if(mid >= L && mid+1 <= R) return askt(ls, l, mid, L, mid)+askt(rs, mid+1, r, mid+1, R)*bs[mid-L+1];
		else if(mid >= L) return askt(ls, l, mid, L, R);
		else return askt(rs, mid+1, r, L, R);
	}
	#undef ls
	#undef rs
}A;
int change(int x, int y) {
	x=col[x], y=col[y];
	if(sz[y] > sz[x]) swap(x, y);
	for(auto i : son[y])
		col[i]=x, A.updt(1, 1, n, i), son[x].push_back(i);
	sz[x]+=sz[y];
	return 1;
}
signed main() {
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	read(n), read(q);
	bs[0]=1;
	for(int i = 1; i <= n; ++i) bs[i]=bs[i-1]*base;
	for(int i = 1; i <= n; ++i) col[i]=i;
	for(int i = 1; i <= n; ++i) son[i].push_back(i);
	for(int i = 1; i <= n; ++i) sz[i]=1;
	A.built(1, 1, n);
	while(q--) {
		read(pro);
		if(pro == 1) {
			read(a), read(b); int toto = -1;
			do {
				toto = -1;
				int l = 1, r = (b-a+1)/2;
				while(l <= r) {
					int mid = (l+r)/2;
					uLL ss = A.asks(1, 1, n, a, a+mid-1), tt = A.askt(1, 1, n, b-mid+1, b);
					if(ss != tt) 
						toto = mid, r=mid-1;
					else
						l=mid+1;
				}
			} while(toto != -1 && change(a+toto-1, b-toto+1));
		}
		else {
			read(a), read(b), read(c), read(d);
			if(b-a != d-c) {
				putchar('N');
				putchar('o');
				putchar('t');
				putchar(' ');
				putchar('e');
				putchar('q');
				putchar('u');
				putchar('a');
				putchar('l');
				putchar('\n');
				continue;
			}
			uLL ss = A.asks(1, 1, n, a, b), tt = A.asks(1, 1, n, c, d);
			if(ss != tt) {
				putchar('U');
				putchar('n');
				putchar('k');
				putchar('n');
				putchar('o');
				putchar('w');
				putchar('n');
				putchar('\n');
			}
			else {
				putchar('E');
				putchar('q');
				putchar('u');
				putchar('a');
				putchar('l');
				putchar('\n');
			}
		}
	}
	return 0;
}
