#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int t, n, k, tr[N], gs[N], mid[N];
long long ans;

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
void add(int x, int w) {
	while(x <= k) tr[x]+=w, x=x+(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x >= 1) ret+=tr[x], x=x-(x&(-x));
	return ret;
}
void sum(int l, int r, int c) {
	if(l > r) return ;
	if(r+c >= k)
		ans+=1LL*gs[l]*((l+c >= k ? -ask(l+c-k) : ask(k)-ask(l+c))+ask(r+c-k+1));
	else
		ans+=1LL*gs[l]*(ask(r+c+1)-ask(l+c));
}

signed main() {
	freopen("fang.in", "r", stdin);
	freopen("fang.out", "w", stdout);
	read(t);
	for(int op = 1; op <= t; ++op) {
		memset(mid, 0, sizeof mid);
		memset(gs, 0, sizeof gs);
		memset(tr, 0, sizeof tr);
		read(n), read(k);
		ans=0;
		for(int i = 1; i <= n; ++i) 
			++gs[(mid[i]=(i-1)%k+1)];
		for(int i = n; i >= 1; --i) {
			add(1LL*i*i%k*i%k+1, 1);
			int b = 1LL*i*i%k;
			sum(1, mid[i], b), sum(mid[i]+1, k, b);
			--gs[(i-1)%k+1];
		}
		putchar('C');
		putchar('a');
		putchar('s');
		putchar('e');
		putchar(' ');
		write(op, ':');
		putchar(' ');
		write(ans, '\n');
	}
	return 0;
}
