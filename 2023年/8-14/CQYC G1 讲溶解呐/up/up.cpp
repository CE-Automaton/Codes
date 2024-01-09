#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
int n, a[N], sum, ans;

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
	freopen("up.in", "r", stdin);
	freopen("up.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= a[1]-1; ++i) {
		sum=i;
		int j = i;
		for(int o = 2; o <= n; ++o)
			j%=a[o], sum+=j;
		ans=max(ans, sum);
	}
	write(ans, '\n');
	return 0;
}
