#include <bits/stdc++.h>
#define inf 1000000000000000000LL
#define LL long long
using namespace std;
const int N = 1e5+5, X = 1e6+4;
int n, h[N];
LL w[N], dp[N]; 
struct qwq {
	LL k, b;
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
LL ask(int nmb, int x) {
	return (LL) xd[nmb].k*x+xd[nmb].b;
}
int pd(int nmb, int tr, int x) {
	if(ask(nmb, x) < ask(tr, x)/* || (ask(nmb, x) == ask(tr, x) && nmb < tr)*/)
		return 1;
	return 0;
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
	xd[0]=qwq {0, inf};
	A.built(1, 1, 1000000); 
	for(int i = 1; i <= n; ++i) 
		read(h[i]);
	for(int i = 1; i <= n; ++i) 
		read(w[i]), w[i]+=w[i-1];
	xd[1]=qwq {-2*h[1], (LL) h[1]*h[1]-w[1]};
	A.updt(1, 1, 1000000, 1);
	for(int i = 2; i <= n; ++i) {
		dp[i]=ask(A.find(1, 1, 1000000, h[i]), h[i])+((LL) h[i]*h[i]+w[i-1]);
		xd[i]=qwq {-2*h[i], (LL) h[i]*h[i]-w[i]+dp[i]};
		A.updt(1, 1, 1000000, i);
	}
	write(dp[n], '\n');
	return 0;
}
