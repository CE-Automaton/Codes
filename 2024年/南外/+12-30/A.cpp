#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 5e5+5;
int n, m, a[N], vis[N], ans;

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
	freopen("per.in", "r", stdin);
	freopen("per.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= m; ++i)
		read(a[i]), vis[a[i]]=1;
	ans=1;
	int r = m;
	for(int i = 1; i+1 <= m; ++i)
		if(a[i] > a[i+1]) {
			r=i;
			break;
		}
	for(int i = 1, j = 1, k = 0; i <= n; ++i) 
		if(!vis[i]) {
			if(i < a[1]) {
				puts("0");
				return 0;
			}
			while(j+1 <= r && a[j+1] <= i) ++j;
			if(j == r) ++j;
			ans=1LL*ans*(j+(k++))%mod;
		}
	write(ans, '\n');
	return 0;
}