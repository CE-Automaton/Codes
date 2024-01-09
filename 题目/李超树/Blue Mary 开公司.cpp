#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5, X = 1e5+4;
const long double eps=1e-12;
int n, k, tot; 
char s[15];
struct qwq {
	long double k, b;
}xd[N];

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
long double ask(int nmb, int x) {
	return (long double) xd[nmb].k*x+xd[nmb].b;
}
int pd(int nmb, int tr, int x) {
	long double ww = ask(nmb, x) - ask(tr, x);
	if(ww > eps)
		return 1;
	if(-ww > eps)
		return 0;
	return (nmb < tr);
}
struct tree {//Àî³¬Ïß¶ÎÊ÷ 
	int tr[X<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	void built(int k, int l, int r) {
		tr[k]=0;
		if(l == r) 
			return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt(int k, int l, int r, int nmb) {
		if(tr[k] == 0) {
			tr[k]=nmb;
			return ;
		}
		int mid = ((l+r)>>1);
		if(pd(nmb, tr[k], mid)) 
			swap(nmb, tr[k]);
		if(l == r) return ;
		if(pd(nmb, tr[k], l))
			updt(ls, l, mid, nmb); 
		if(pd(nmb, tr[k], r))
			updt(rs, mid+1, r, nmb); 
	}
	int find(int k, int l, int r, int to) {
		if(l == r) 
			return tr[k];
		int mid = ((l+r)>>1), ret = 0;
		if(to <= mid)
			ret=find(ls, l, mid, to);
		else
			ret=find(rs, mid+1, r, to); 
		if(pd(tr[k], ret, to))
			ret=tr[k];
		return ret;
	}
}A;

signed main() {
	read(n);
	xd[0]=qwq {0, 0};
	A.built(1, 1, 100000); 
	for(int i = 1; i <= n; ++i) {
		scanf("%s", s+1);
		if(s[1] == 'P') {
			++tot;
			scanf("%Lf %Lf", &xd[tot].b, &xd[tot].k);
			xd[tot].b-=xd[tot].k;
			A.updt(1, 1, 100000, tot);
		}
		else {
			read(k);
			write((int) floor((long double) ask(A.find(1, 1, 100000, k), k)/100), '\n');
		}
	}
	return 0;
}
