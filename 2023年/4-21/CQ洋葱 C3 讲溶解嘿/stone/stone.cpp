#include <bits/stdc++.h>
#define mod 1000000007
#define int long long
using namespace std;
const int N = 1e7+5;
int n, a[N], ans;

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
int check() {
	for(int i = 1; i < n; ++i)
		if(a[i] > a[i+1])
			return 1;
	return 0;
}

signed main() {
	freopen("stone.in", "r", stdin);
	freopen("stone.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) 
		read(a[i]);
	for(int i = n-1; i >= 1; --i) 
		while(a[i] > a[i+1]) {
			int haha = (a[i]-a[i+1]+1)/2;
			(ans+=haha)%=mod;
			a[i]-=haha;
			a[i+1]+=haha;
			for(int j = i+1; j < n; ++j)
				if(a[j] > a[j+1]) {
					int haha = (a[j]-a[j+1]+1)/2;
					(ans+=haha)%=mod;
					a[j]-=haha;
					a[j+1]+=haha;
				}
				else 
					break;
		} 
	while(check()) {
		for(int i = 1; i < n; ++i)
			if(a[i] > a[i+1]) {
				int haha = (a[i]-a[i+1]+1)/2;
				(ans+=haha)%=mod;
				a[i]-=haha;
				a[i+1]+=haha;
			}
	}
	write(ans, '\n');
	return 0;
}
