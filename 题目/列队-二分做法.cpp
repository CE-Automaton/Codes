#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5+5;
int n, m, q, rt[N], xx, yy, xixi; 
vector <int> v[N];
struct node {
	int ls, rs, w;
}tr[N*25];
struct tree {
	int gs = 0;
	int find(int k, int l, int r, int sz) {
		if(l == r) 
			return l;
		int mid = ((l+r)>>1), tmp = mid-l+1-tr[tr[k].ls].w;
		if(tmp < sz)
			return find(tr[k].rs, mid+1, r, sz-tmp);
		else
			return find(tr[k].ls, l, mid, sz);
	}
	void updt(int &k, int l, int r, int to) {
		if(!k) ++gs, k=gs;
		++tr[k].w;
		if(l == r) 
			return ;
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(tr[k].ls, l, mid, to);
		else
			updt(tr[k].rs, mid+1, r, to);
	}
}A;

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
int work1(int x, int y) {
	int pst = A.find(rt[n+1], 1, xixi, x), ret = 0;
	A.updt(rt[n+1], 1, xixi, pst);
	ret=(pst <= n ? pst*m : v[n+1][pst-n-1]);
	v[n+1].push_back((y ? y : ret));
	return ret;
}
int work2(int x, int y) {
	int pst = A.find(rt[x], 1, xixi, y), ret = 0;
	A.updt(rt[x], 1, xixi, pst);
	ret=(pst < m ? (x-1)*m+pst : v[x][pst-m]);
	v[x].push_back(work1(x, ret));
	return ret;
} 

signed main() {
	read(n), read(m), read(q);
	xixi=max(n, m)+q;
	while(q--)
		read(xx), read(yy), write((yy == m ? work1(xx, 0) : work2(xx, yy)), '\n');
	return 0;
}
