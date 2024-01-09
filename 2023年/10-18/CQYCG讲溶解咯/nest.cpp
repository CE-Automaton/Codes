#include <bits/stdc++.h>
#define uLL unsigned long long
#define mod 1000000007
using namespace std;
const int N = 5e3+5;
const uLL base = 100007;
int n, a[N], f[N], sum, ans;
uLL hs;
unordered_map<uLL, int> qwq;

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("nest.in", "r", stdin);
	freopen("nest.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 0; i <= (1<<n)-1; ++i) {
		hs=0;
		for(int j = 1; j <= n; ++j)
			if((i>>(j-1))&1) 
				hs=hs*base+a[j];
		if(qwq.find(hs) != qwq.end())
			continue;
		qwq[hs]=1;
		sum=1;
		for(int j = 1; j <= n; ++j)
			f[j]=0;
		for(int j = 1; j <= n; ++j)
			if((i>>(j-1))&1) {
				int b = f[a[j]];
				f[a[j]]=sum, sum=sum+sum-b;
			}
		ans=upd(ans+sum);
	}
	write(ans, '\n');
	return 0;
}
