#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5, M = 1e6+4;
int n, a[N];
long long ton[M];

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
		read(a[i]), ton[a[i]]+=1LL*a[i];
	for(int i = 1000000; i >= 0; --i)
		ton[i]+=ton[i+1];
	for(int i = 1; i <= n; ++i)
		write(ton[a[i]+1], ' ');
	return 0;
}
