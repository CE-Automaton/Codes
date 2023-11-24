#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 5e3+5;
int n, m, mx[5000005], ans;
char s[25][200005];

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
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		scanf("%s", s[i]+1);
	for(int j = 0; j <= (1<<n)-1; ++j)
		for(int i = 1; i <= m; ++i) {
			int gs = 0;
			for(int o = 1; o <= n; ++o)
				gs+=((s[o][i]-'0')^((j>>(o-1))&1));
			mx[j]+=min(gs, n-gs);
		}
	ans=mx[0];
	for(int j = 1; j <= (1<<n)-1; ++j) 
		ans=min(ans, mx[j]);
	write(ans, '\n');
	return 0;
}
