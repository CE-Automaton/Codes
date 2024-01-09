#include <bits/stdc++.h>
using namespace std;
int n, k, ans, zhan[25][25], tot[25];
struct qwq {
	int l, r;
}a[25];

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
qwq jiao(qwq A, qwq B) {
	if(A.l > B.l) swap(A, B);
	if(A.r < B.r)
		return {10000000, 9999999};
	else
		return {max(B.l, A.l), min(A.r, B.r)};
}
void dfs(int x) {
	if(x == n+1) {
		for(int i = 1; i <= k; ++i)
			if(tot[i] == 0) return ;
		int anss = 0;
		for(int o = 1; o <= k; ++o) {
			qwq sum = qwq{0, 10000000};
			for(int i = 1; i <= tot[o]; ++i)
				sum=jiao(sum, a[zhan[o][i]]);
			anss+=sum.r-sum.l+1;
		}
		ans=max(ans, anss);
		return ;
	}
	for(int o = 1; o <= k; ++o) {
		zhan[o][++tot[o]]=x;
		dfs(x+1);
		--tot[o];
	}
}

signed main() {
	freopen("interval.in", "r", stdin);
	freopen("interval.out", "w", stdout);
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		read(a[i].l), read(a[i].r), --a[i].r;
	dfs(1);
	write(ans, '\n');
	return 0;
}
