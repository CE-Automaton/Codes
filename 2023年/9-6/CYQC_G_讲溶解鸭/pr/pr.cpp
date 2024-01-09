#include <bits/stdc++.h>
using namespace std;
const int N = 4e6+5;
int p, t, n, m, sum[2][N], ans;

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
	return (x >= p ? x-p : x);
}
int ask(int now, int l, int r, int mid, int pd) {
	if(r > mid)
		return upd(upd(sum[now][mid]-(l < 0 ? 0 : sum[now][l])+p)+ask(now, mid-(r-mid)-pd, mid-pd, mid, pd));
	return upd(sum[now][r]-(l < 0 ? 0 : sum[now][l])+p);
}
int ksm(int x, int y, int ret = 1) {
	while(x) {
		if(x&1)
			ret=1LL*ret*y%p;
		y=1LL*y*y%p;
		x=(x>>1);
	}
	return ret;
}

signed main() {
	freopen("pr.in", "r", stdin);
	freopen("pr.out", "w", stdout);
	read(p);
	read(t);
	while(t--) {
		read(n), read(m);
		ans=0;
		int r = m;
		for(int i = 0; i <= m; ++i)
			sum[0][i]=1;
		int now = 0;
		for(int i = 2; i <= n; ++i) {
			now^=1;
			int mid = r/2, pd = (r+1)%2;
			for(int j = 0; j <= mid; ++j)
				sum[now^1][j]=upd(sum[now^1][j]+(j == 0 ? 0 : sum[now^1][j-1]));
			r+=m;
			for(int j = 0; j <= r/2; ++j)
				sum[now][j]=ask(now^1, j-m-1, j, mid, pd);
		}
		int l = (r-1)/2;
		for(int i = r/2+1; i <= r; ++i, --l)
			sum[now][i]=sum[now][l];
		int w = 0;
		for(int i = 0; i <= r; ++i) {
			ans=upd(ans+1LL*w*sum[now][i]%p);
			w = upd(w+sum[now][i]);
		}
		write(1LL*ans*ksm(2*n, ksm(p-2, m+1))%p, '\n');
	}
	return 0;
}
