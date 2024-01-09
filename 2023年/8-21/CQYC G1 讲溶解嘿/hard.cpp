#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N = 1e6+5;
int p, k, vis[N], pd[N], zhan[N], tot;

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
	freopen("hard.in", "r", stdin);
	freopen("hard.out", "w", stdout);
	read(p), read(k);
	int ans = 1;
	if(k == 0) {
		for(int i = 1; i <= p-1; ++i)
			ans=1LL*ans*p%mod;
		write(ans, '\n');
		return 0;
	}
	for(int i = 1, pw = 1; i <= p-1; ++i) {
		pw=1LL*pw*k%p;
		if(pw == 1)
			vis[i]=1;
	} 
//	puts("?");
	for(int i = 0; i <= p-1; ++i) {
		if(pd[i]) continue;
		int now = i;
		tot=0;
		while(pd[now] == 0) {
			pd[now]=1;
			zhan[++tot]=now;
			now=1LL*now*k%p;
		}
		if(vis[tot] == 1)
			ans=1LL*ans*p%mod;
	}
	write(ans, '\n');
	return 0;
}
