#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n, m, ans[N], vis[N], gs, dp[N], ddp[N];
struct qwq {
	int a, b;
}p[N];

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
	freopen("marketplace.in", "r", stdin); 
	freopen("marketplace.out", "w", stdout);
	read(n), read(m);
	gs=m;
	for(int i = 1; i <= n; ++i) 
		read(p[i].a), read(p[i].b), p[i+n]=p[i];
	p[1+n+n]=p[1];
	int ed = 0;
	for(int i = 1; i <= n+n+1; ++i) {
		if(vis[p[i].a]) {
			if(vis[p[i].b]) {
				ed=i;
//				cout<<i<<" "<<gs<<"!\n";
				ans[i]+=gs;//加上不影响选择的x 
				break;
			}
			else {
				vis[p[i].b]=1;
				--gs;
				++ans[i];//x=b的情况 
				ans[i]+=dp[p[i].b];
				dp[p[i].b]=0;
			}
		}
		else {
			vis[p[i].a]=1;
			--gs;
			if(vis[p[i].b]) //a不能选时,相当于多了个以后不能选择b的限制 
				++ans[i]/*x=b的情况*/, ans[i]+=dp[p[i].a], dp[p[i].a]=0;
			else
				++dp[p[i].b], dp[p[i].b]+=dp[p[i].a], dp[p[i].a]=0;
		}
	}
	for(int i = 1; i <= m; ++i)
		ans[ed]+=dp[i];//好像最后可以不用加? 
	for(int i = n+1; i <= n+n+1; ++i)
		ans[(i-1)%n+1]+=ans[i];
	for(int i = 1; i <= n; ++i)
		write(ans[i], '\n');
	return 0;
}
