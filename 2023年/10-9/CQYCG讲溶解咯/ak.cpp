#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, k, a[N], b[N], cnt;
long long sum;

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
	freopen("ak.in", "r", stdin);
	freopen("ak.out", "w", stdout);
	read(n), read(k);
	for(int i = 1; i <= n; ++i) {
		read(a[i]);
		sum+=1LL*a[i];
		if((i-1)%k == 0)
			b[++cnt]=a[i];
	}
	if(n == 1) {
		write(a[1], '\n');
		return 0;
	}
	sort(b+1, b+1+cnt);
	write(sum-1LL*b[cnt/2+1], '\n');
	return 0;
}
