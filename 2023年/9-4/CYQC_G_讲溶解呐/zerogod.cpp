#include <bits/stdc++.h>
using namespace std;
long long n;
int p, ans,
pri[65]={0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281};

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
int ksm(int x, int y, int ret = 1) {
	while(x) {
		if(x&1)
			ret=1LL*ret*y%p;
		y=1LL*y*y%p;
		x=(x>>1);
	}
	return ret;
}

signed main() {
	freopen("zerogod.in", "r", stdin);
	freopen("zerogod.out", "w", stdout);
	read(n), read(p);
	ans=1LL*n%p;
	for(long long i = 1; i <= 60; ++i)
		if((n>>(i-1))&1LL)
			ans=ksm(pri[i], ans);
	write(ans, '\n');
	return 0;
}
