#include <bits/stdc++.h>
#define mod 10007
int upd(int x) { return (x >= mod ? x-mod : x); }
using namespace std;
const int N = 5e4+5, K = 155;
int n, k, s[N][K], u, v, jc[N];
vector <int> to[N];
struct dp{
	int f[K];
	int& operator[](int x) { return f[x]; }
	void operator +=(dp A) {
		for(int i = 1; i <= k; ++i)
			f[i]=upd(f[i]+upd(A[i]+A[i-1]));
		f[0]=upd(f[0]+A[0]);
	}
	void operator -=(dp A) {
		f[0]=upd(f[0]-A[0]+mod);
		for(int i = k; i >= 1; --i)
			f[i]=upd(f[i]-upd(A[i]+A[i-1])+mod);
	}
}ds[N];

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
void dfs(int x, int fa) {
	ds[x][0]=1;
	for(int y : to[x])
		if(y != fa) 
			dfs(y, x), ds[x]+=ds[y];
}
void sol(int x, int fa) {
	for(int y : to[x])
		if(y != fa) {
			dp t = ds[x];
			t-=ds[y];
			ds[y]+=t;
			sol(y, x);
		}
}

signed main() {
    read(n), read(k);
	s[0][1]=s[1][1]=jc[1]=1;
	for(int i = 2; i <= n; ++i) {
		jc[i]=jc[i-1]*i%mod;
		for(int j = 1; j <= k; ++j)
			s[i][j]=upd(s[i-1][j-1]+s[i-1][j]*j%mod);
	}
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	dfs(1, 0);
	sol(1, 0);
	for(int x = 1, ans = 0; x <= n; ++x) {
		ans=0;
		for(int i = 0; i <= k; ++i)
			ans=upd(ans+s[k][i]*jc[i]%mod*ds[x][i]%mod);
		write(ans, '\n');
	}
	return 0;
}