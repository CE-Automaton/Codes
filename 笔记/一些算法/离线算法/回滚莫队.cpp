#include <bits/stdc++.h>
#define pii pair <int, int>
using namespace std;
const int N = 2e5+5, B = 455;
int n, q, a[N], to[N], cnt, ans[N];
pii b[N];
struct pro {
	int l, r, d;
}que[N];

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
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), b[i]=(pii) {a[i], i};
	sort(b+1, b+1+n);
	for(int i = 1; i <= n; ++i) {
		if(i == 1 || b[i].first != b[i-1].first)
			++cnt, to[cnt]=b[i].first;
		a[b[i].second]=cnt;
	}
	read(q);
	for(int i = 1; i <= q; ++i) 
		read(que[i].l), read(que[i].r), que[i].d=i;
	
	return 0;
}
