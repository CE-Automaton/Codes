#include <bits/stdc++.h>
#define mod 998244353
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e3+5;
int n, k, a[N], sum[N], dp[2][N], now, ans;
vector <int> to[N];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
void add(int l, int r) {
	for(int i = l; i <= r; ++i) {
		now^=1;
		for(int j = 0; j <= k+k; ++j)
			dp[now][j]=inf;
		for(int j = 0; j <= k+k; ++j) {
			if(j+a[i] <= k+k)
				dp[now][j+a[i]]=min(dp[now][j+a[i]], dp[now^1][j]+abs(j+a[i]-k));
			// if(j-a[i] >= 0)
			// 	dp[now][j-a[i]]=min(dp[now][j-a[i]], dp[now^1][j]+abs(j-a[i]-k));
			// if(j+k-a[i] <= k+k)
			// 	dp[now][j+k-a[i]]=min(dp[now][j+k-a[i]], dp[now^1][j]+abs(j-a[i]));
			if(j-k+a[i] >= 0)
				dp[now][j-k+a[i]]=min(dp[now][j-k+a[i]], dp[now^1][j]+abs(j-k-k+a[i]));
		}
	}
}

signed main() {
	File("substr");
	read(n), read(k);
	to[0].push_back(0);
	for(int i = 1; i <= n; ++i)
		read(a[i]), sum[i]=sum[i-1]+a[i], to[sum[i]%k].push_back(i);
	ans=upd(ans-1LL*n*(n+1)/2%mod+mod);
	for(int i = 0; i < k; ++i) {
		for(int l = 0; l < to[i].size(); ++l) {
			int r = l, st = to[i][l];
			now=0;
			for(int j = 0; j <= k+k; ++j)
				dp[0][j]=inf;
			dp[0][k]=0;
			while(r+1 < to[i].size())
				++r, add(st+1, to[i][r]), st=to[i][r], ans=upd(ans+upd(dp[now][k]+1));
		}
	}
	write(ans, '\n');
	return 0;
}