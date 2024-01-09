#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, h[N], ans[N];

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
	read(n);
	for(int i = 1; i <= n; ++i)
		read(h[i]);
	ans[1]=1;
	for(int i = 2; i <= n; ++i)
		ans[i]=min(ans[i-1]+1, h[i]);
	ans[n]=1;
	for(int i = n-1; i >= 1; --i)
		ans[i]=min(ans[i], ans[i+1]+1);
	int mx = 0;
	for(int i = 1; i <= n; ++i)
		mx=max(mx, ans[i]);
	write(mx, '\n');
	return 0;
}
