#include <bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
int m, n, k, o, l[N], r[N], ans[N], aa[N], cc[N], dd[N], now;
long long p[N], a[N];
vector <int> to[N];

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
struct BIT {
	long long tr[N];
	void add(int x, long long w) {
		if(!x) return ;
		while(x <= m)
			tr[x]=tr[x]+w, x=x+(x&(-x));
	}
	long long ask(int x, long long ret=0) {
		while(x >= 1)
			ret=ret+tr[x], x=x-(x&(-x));
		return ret;
	}
}A;
void sol(int lq, int rq, int ll, int rr) {
	if(lq > rq || ll > rr) return ;
	int mid = ((ll+rr)>>1);
	while(now+1 <= mid) {
		++now;
		if(l[now] <= r[now])
			A.add(l[now], a[now]), A.add(r[now]+1, -a[now]);
		else
			A.add(1, a[now]), A.add(r[now]+1, -a[now]), A.add(l[now], a[now]);
	}
	while(now > mid) {
		if(l[now] <= r[now])
			A.add(l[now], -a[now]), A.add(r[now]+1, a[now]);
		else
			A.add(1, -a[now]), A.add(r[now]+1, a[now]), A.add(l[now], -a[now]);
		--now;
	}
	int MID = 0, els = 0;
	for(int k = lq; k <= rq; ++k) {
		int i = aa[k];
		long long w = 0;
		for(int j : to[i]) {
			w+=A.ask(j);
			if(w >= p[i]) break; 
		}
		if(w >= p[i])
			ans[i]=mid, cc[++MID]=i;
		else
			dd[++els]=i;
	}
	for(int k = 1; k <= MID; ++k)
		aa[k+lq-1]=cc[k];
	MID=MID+lq-1;
	for(int k = 1; k <= els; ++k)
		aa[k+MID]=dd[k];
	sol(lq, MID, ll, mid-1);
	sol(MID+1, rq, mid+1, rr);
}

signed main() {
	read(n), read(m);
	for(int i = 1; i <= m; ++i)
		read(o), to[o].push_back(i);
	for(int i = 1; i <= n; ++i)
		read(p[i]), aa[i]=i;
	read(k);
	for(int i = 1; i <= k; ++i)
		read(l[i]), read(r[i]), read(a[i]);
	sol(1, n, 1, k);
	for(int i = 1; i <= n; ++i)
		if(ans[i] == 0)
			puts("NIE");
		else
			write(ans[i], '\n');
	return 0;
}
