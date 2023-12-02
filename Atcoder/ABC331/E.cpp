//可以直接枚举的样子,有点内个了 
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m, l, b[N], d[N], rk[N], cnt, u, v, tr[N], ans;
vector <int> to[N];
struct qwq {
	int a, b;
}bb[N];

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
	return A.a > B.a;
}
void add(int x, int w) {
	while(x <= m)
		tr[x]+=w, x=x+(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x >= 1)
		ret+=tr[x], x=x-(x&(-x));
	return ret;
}

signed main() {
	read(n), read(m), read(l);
	for(int i = 1; i <= n; ++i)
		read(b[i]);
	for(int i = 1; i <= m; ++i)
		read(d[i]), 
		bb[i]=qwq {d[i], i};
	for(int i = 1; i <= l; ++i)
		read(u), read(v), to[u].push_back(v);
	sort(bb+1, bb+1+m, comp);
	for(int i = 1; i <= m; ++i) 
		rk[bb[i].b]=i;
	for(int i = 1; i <= n; ++i) {
		for(int y : to[i])
			add(rk[y], 1);
		int l = 1, r = m, op = 0;
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(ask(mid) != mid)
				op=mid, r=mid-1;
			else
				l=mid+1;
		}
		if(op)
			ans=max(ans, b[i]+d[bb[op].b]);
		for(int y : to[i])
			add(rk[y], -1);
	}
	write(ans, '\n');
	return 0;
}
