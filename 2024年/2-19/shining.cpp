#include <bits/stdc++.h>
#define inf 1000000000000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, tl, hd;
LL sum[N], h[N], c;
struct qwq {
	LL a, b;
}zhan[N];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
int check(LL mid) {
	LL l = -inf, ll = -inf, r = inf, rr = inf, mxb = -inf, mxa = -inf;
	hd=1, tl=0;
	for(int i = 1; i <= n; ++i) {
		LL a = sum[i]+h[i], b = h[i]-sum[i];
		if(a+mxb > mid) {
			while(hd <= tl && a+zhan[hd].b > mid)
				mxa=max(mxa, zhan[hd].a), ++hd;
			l=max(l, mxa+a-mid+c);
			ll=max(ll, mxb+a-mid+c);
			r=min(r, mid-c-mxb-b);
			rr=min(rr, mid-c-mxa-b);
		}
		mxb=max(mxb, b);
		while(hd <= tl && zhan[tl].b <= b) --tl;
		zhan[++tl]=qwq {a, b};
	}
	if(l > r || ll > rr) return 0;
	int l1 = n+1, r1 = n, l2 = 1, r2 = 0;
	for(int i = 1; i <= n; ++i) {
		while(l1 > 1 && sum[l1-1]+sum[i] >= l) --l1;
		while(r1 >= l1 && sum[r1]+sum[i] > r) --r1;
		while(r2 < n && sum[r2+1]-sum[i] <= rr) ++r2;
		while(l2 <= r2 && sum[l2]-sum[i] < ll) ++l2;
		if(max(l1, l2) <= min(r1, r2))
			return 1;
	}
	return 0;
}

signed main() {
	read(n), read(c);
	for(int i = 2; i <= n; ++i)
		read(sum[i]), sum[i]+=sum[i-1];
	for(int i = 1; i <= n; ++i)
		read(h[i]);
	LL l = 1, r = 1000000000000000000LL, ans = -1;
	while(l <= r) {
		LL mid = ((l+r)>>1);
		if(check(mid)) ans=mid, r=mid-1;
		else l=mid+1;
	}
	write(ans, '\n');
	return 0;
}