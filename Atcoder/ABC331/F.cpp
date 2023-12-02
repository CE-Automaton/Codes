#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 1e6+5, base = 31;
int n, q, bs[N], ll, rr, opt;
char tt[N], ttt;

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
struct tree {
	char s[N];
	int tr[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void upup(int k, int l, int r) {
		int mid = ((l+r)>>1);
		tr[k]=upd(1LL*tr[ls]*bs[r-mid]%mod+tr[rs]);
	}
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k]=s[l]-'a'+1;
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		upup(k, l, r);
	}
	void updt(int k, int l, int r, int to, char t) {
		if(l == r) {
			s[l]=t;
			tr[k]=s[l]-'a'+1;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(ls, l, mid, to, t);
		else
			updt(rs, mid+1, r, to, t);
		upup(k, l, r);
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		int mid = ((l+r)>>1);
		if(lq <= mid && mid+1 <= rq)
			return upd(1LL*ask(ls, l, mid, lq, mid)*bs[rq-mid]%mod+ask(rs, mid+1, r, mid+1, rq));
		if(lq <= mid)
			return ask(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			return ask(rs, mid+1, r, lq, rq);
	}
}A, B;

signed main() {
	read(n), read(q);
	scanf("%s", tt+1);
	for(int i = 1; i <= n; ++i)
		A.s[i]=tt[i], B.s[n-i+1]=tt[i];
	bs[0]=1;
	for(int i = 1; i <= n; ++i)
		bs[i]=1LL*bs[i-1]*base%mod;
	A.built(1, 1, n);
	B.built(1, 1, n);
	for(int i = 1; i <= q; ++i) {
		read(opt);
		if(opt == 2) {
			read(ll), read(rr);
			if(A.ask(1, 1, n, ll, rr) == B.ask(1, 1, n, n-rr+1, n-ll+1))
				puts("Yes");
			else
				puts("No");
		}
		else {
			read(ll), scanf(" %c", &ttt);
			A.updt(1, 1, n, ll, ttt);
			B.updt(1, 1, n, n-ll+1, ttt);
		}
	}
	return 0;
}
