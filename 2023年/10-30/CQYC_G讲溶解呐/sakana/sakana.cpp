#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 5e5+5;
int n, a[N], b[N], mx[N], mn[N], ans=2000000007;

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
void dfs(int x, int tot) {
	if(tot != 0 && mx[tot]-mn[tot] > ans)
		return ;
	if(x == n+1) {
		ans=min(ans, mx[tot]-mn[tot]); 
		return ;
	}
	if(x != n)
		b[tot+1]=a[x]+a[x+1], mn[tot+1]=min(mn[tot], b[tot+1]), mx[tot+1]=max(mx[tot], b[tot+1]), dfs(x+2, tot+1);
	b[tot+1]=a[x], mn[tot+1]=min(mn[tot], b[tot+1]), mx[tot+1]=max(mx[tot], b[tot+1]), dfs(x+1, tot+1);
}

signed main() {
	freopen("sakana.in", "r", stdin);
	freopen("sakana.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	mn[0]=2000000007;
	mx[0]=0;
	dfs(1, 0);
	write(ans, '\n');
	return 0;
}
