#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int typ, n, m, a[N], sum[N], zhan[N], tot, l, r, ans;

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
int check(int k) {
	tot=0;
	for(int i = 1; i <= n; ++i) 
		if(a[i] <= k/2)
			zhan[++tot]=i;
	int gs = tot;
	if(tot == 0) {
		for(int i = 1; i <= n; ++i) 
			if(a[i] <= k)
				gs=1;
	}
	else {
		for(int i = 1; i+1 <= tot; ++i)
			for(int j = zhan[i+1]-1; j >= zhan[i]+1; --j)
				if(a[j]+a[zhan[i]] <= k && a[j]+a[zhan[i+1]] <= k) {
					++gs;
					break;
				}
		for(int j = zhan[tot]+1; j <= n+zhan[1]-1; ++j) {
			int tt = (j-1)%n+1;
			if(a[tt]+a[zhan[tot]] <= k && a[tt]+a[zhan[1]] <= k) {
				++gs;
				break;
			}
		}
	}
	return (gs >= m);
}

signed main() {
	read(typ), read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	l=0, r=ans=2000000000;
	while(l <= r) {
		int mid = ((l>>1)+(r>>1)+((l&1)&(r&1)));
		if(check(mid))
			r=mid-1, ans=mid;
		else
			l=mid+1;
	}
	write(ans, '\n');
	return 0;
}
