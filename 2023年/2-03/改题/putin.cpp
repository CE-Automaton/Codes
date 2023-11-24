#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, a[29], id[29], b[29], sum[1<<26], smb[1<<26], ans;
void read(int& x) {
	x=0; char c = getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
}
int comp(int A, int B) {
	return a[A] < a[B];
}
signed main() {
	freopen("putin.in", "r", stdin);
	freopen("putin.out", "w", stdout);
	read(n), read(m);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) read(a[j]), id[j]=j;
		sort(id, id+m, comp);
		int haha = 0, lst = 0;
		for(int j = 0; j < m; ++j) {
			sum[haha]+=a[id[j]]-lst;
			lst = a[id[j]];
			haha |= (1<<id[j]);
		}
	}
	for(int j = 0; j < m; ++j)
		for(int i = 0; i <= (1<<m)-1; ++i)
			if(i&(1<<j))
				sum[i]+=sum[i^(1<<j)];
	for(int i = 0; i < m; ++i) 
		read(b[i]);
	for(int s = 0; s < (1<<m); ++s) {
		if(s) {
			int x = __builtin_ctz(s);
			smb[s]=smb[s^(1<<x)]+b[x];
		}
		sum[((1<<m)-1)^s]+=smb[s];
	}
	ans=sum[0];
	for(int i = 1; i < (1<<m)-1; ++i)
		ans=min(ans, sum[i]);
	printf("%lld\n", ans);
	return 0;
}
