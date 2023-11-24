#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 5e5+5;
int n, k, a[N];
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

signed main() {
	freopen("elevator.in", "r", stdin);
	freopen("elevator.out", "w", stdout);
	read(n), read(k);
	int mx = 0;
	for(int i = 1; i <= n; ++i)
		read(a[i]), mx=max(mx, a[i]);
	for(int i = 1; i <= n; ++i)
		ans+=2*(mx-1);
	write(ans, '\n');
	return 0;
}
