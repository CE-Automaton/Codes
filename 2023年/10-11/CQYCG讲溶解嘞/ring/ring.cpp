#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1e5+5;
int n, m, b[N], a[N], t[N], vis[N], gs, ans;

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
	return (x >= m ? x-m : x);
}
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1)
			ret=1LL*ret*x%mod;
		x=1LL*x*x%mod;
		y=(y>>1);
	}
	return ret;
}
void dfs(int x) {
	if(x == n+1) {
		for(int i = 1; i <= n; ++i)
			a[i]=b[i], t[a[i]]=i;
		int pd = 1;
		for(int i = 1; i <= n; ++i) {
			int A = 0, B = 0;
			if(t[i] == 1)
				A = a[n], B = a[2], swap(a[n], a[2]), t[a[n]]=n, t[a[2]]=2;
			else
				if(t[i] == n)
					A = a[n-1], B = a[1], swap(a[n-1], a[1]), t[a[n-1]]=n-1, t[a[1]]=1;
				else
					A = a[t[i]-1], B = a[t[i]+1], swap(a[t[i]-1], a[t[i]+1]), t[a[t[i]-1]]=t[i]-1, t[a[t[i]+1]]=t[i]+1;
			if(A > B) swap(A, B);
			if(A < i && i < B)
				pd=0;
		}
		if(pd) 
			gs=upd(gs+1);
		return ;
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i]) {
			vis[i]=1;
			b[x]=i;
			dfs(x+1);
			vis[i]=0;
		}
}

signed main() {
	freopen("ring.in", "r", stdin);
	freopen("ring.out", "w", stdout);
	read(n), read(m);
	ans=1;
	for(int i = 1; i <= n; ++i)
		ans=1LL*ans*i%m;
	if(n%2 == 0)
		dfs(1);
	write(ans-gs, '\n');
	return 0;
}
