#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, ll[N], rr[N], lans[N], rans[N], to[N<<1], pd[N<<1];
long long sum1, sum2, sum3, gs;
struct tree {
	long long tr[N<<3];
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void built(int k, int l, int r) {
		tr[k]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	} 
	void updt(int k, int l, int r, int to, long long ww) {
		if(l == r) {
			tr[k]+=ww;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid) updt(ls, l, mid, to, ww);
		else updt(rs, mid+1, r, to, ww);
		tr[k]=tr[ls]+tr[rs];
	}
	long long ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		int mid = ((l+r)>>1);
		long long ret = 0;
		if(lq <= mid)
			ret+=ask(ls, l, mid, lq, rq);
		if(mid+1 <= rq)
			ret+=ask(rs, mid+1, r, lq, rq);
		return ret;
	}
}A, B;

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

signed main() {
	freopen("explorer.in", "r", stdin);
	freopen("explorer.out", "w", stdout);
	read(n);
	int pdd = 1;
	for(int i = 1; i <= n; ++i) {
		read(ll[i]), read(rr[i]);
		if(ll[i] > rr[i]) swap(ll[i], rr[i]);
		pdd&=(ll[i] == 2*i-1);
		pdd&=(rr[i] == 2*i);
		to[ll[i]]=i, pd[ll[i]]=0;
		to[rr[i]]=i, pd[rr[i]]=1;
	}
	if(pdd) {
		write(1LL*n*(n-1)*(n-2)/2/3, '\n');
		return 0;
	}
	A.built(1, 1, n*2);
	B.built(1, 1, n*2);
	for(int i = 1; i <= n*2; ++i) 
		if(pd[i] == 1) {
			sum1+=B.ask(1, 1, n*2, 1, ll[to[i]]);
			B.updt(1, 1, n*2, i, A.ask(1, 1, n*2, 1, ll[to[i]]));
			A.updt(1, 1, n*2, i, 1LL);
		}
	A.built(1, 1, n*2);
	for(int o = 1; o <= n; ++o) {
		for(int i = ll[o]+1; i+1 <= rr[o]; ++i)
			if(pd[i] == 1 && ll[to[i]] >= ll[o]) {
				sum2+=A.ask(1, 1, n*2, 1, ll[to[i]]);
				A.updt(1, 1, n*2, i, 1LL);
			}
		for(int i = rr[o]-1; i-1 >= ll[o]; --i)
			if(pd[i] == 1 && ll[to[i]] >= ll[o]) 
				A.updt(1, 1, n*2, i, -1LL);
	}
	A.built(1, 1, n*2);
	for(int i = 1; i <= n*2; ++i) 
		if(pd[i] == 0) {
			for(int k = rr[to[i]]+1; k <= n*2; ++k)
				if(pd[k] == 1 && ll[to[k]] >= i)
					sum3+=A.ask(1, 1, n*2, ll[to[k]], rr[to[i]]);
			A.updt(1, 1, n*2, rr[to[i]], 1LL);
		}
//	cout<<sum1<<' '<<sum2<<" "<<sum3<<"\n";
	write(sum1+sum2+sum3, '\n');
	return 0;
}
