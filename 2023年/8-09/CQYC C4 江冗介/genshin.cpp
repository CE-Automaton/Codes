#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, p, w, d;
long long sum[N], ssum[N], summ[N], ssumm[N], anss = 1000000000000000000LL;
struct qwq {
	int l, r, w;
}perl[N], perr[N];

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
int comp(qwq A, qwq B) {
	return A.l < B.l;
}
int comp2(qwq A, qwq B) {
	return A.r < B.r;
}

signed main() {
	freopen("genshin.in", "r", stdin);
	freopen("genshin.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(p), read(w), read(d), perl[i]=perr[i]=qwq{p-d, p+d, w};
	sort(perl+1, perl+1+n, comp);
	sort(perr+1, perr+1+n, comp2);
	for(int i = n; i >= 1; --i)
		sum[i]=sum[i+1]+perl[i].w, ssum[i]=ssum[i+1]+1LL*perl[i].l*perl[i].w; 
	for(int i = 1; i <= n; ++i)
		summ[i]=summ[i-1]+perr[i].w, ssumm[i]=ssumm[i-1]+1LL*perr[i].r*perr[i].w; 
	for(int i = 0; i <= 3000000; ++i) {
		int l = 1, r = n, ret = 0;
		long long ans = 0;
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(perr[mid].r < i)
				ret=mid, l=mid+1;
			else
				r=mid-1;
		}
		ans+=summ[ret]*i-ssumm[ret];
		l = 1, r = n, ret = n+1;
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(perl[mid].l > i)
				ret=mid, r=mid-1;
			else
				l=mid+1;
		}
		ans+=ssum[ret]-sum[ret]*i;
		anss=min(anss, ans);
	}
	write(anss, '\n');
	return 0;
}
