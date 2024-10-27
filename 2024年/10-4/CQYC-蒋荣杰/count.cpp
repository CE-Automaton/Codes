#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 605;
int t, n, a[N], cnt, b[N], dp[2][N/*有i个需要填入数字的空隙*/], c[N][N], jc[N];

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
int comp(int x, int y) {
	return x > y;
}
void sol() {
	memset(dp, 0, sizeof dp);
	read(n);
	for(int i = 1; i <= n; ++i) {
		read(a[i]);
		int now = a[i];
		for(int j = 2; j <= now/j; ++j) {
			while(now%(j*j) == 0)
				a[i]/=j*j, now/=j*j;
			if(now%j == 0)
				now/=j;
		}
	}
	sort(a+1, a+1+n);
	cnt=0;
	for(int i = 1; i <= n; ++i) {
		int j = i;
		while(j+1 <= n && a[j+1] == a[i])
			++j;
		b[++cnt]=j-i+1;
		i=j;
	}
	// debug(cnt, '\n');
	// for(int i = 1; i <= cnt; ++i)
	// 	debug(b[i]), debug(' ');
	// debug("!\n");
	dp[0][b[1]-1]=jc[b[1]];
	int now = 0, sum = b[1];
	for(int i = 2; i <= cnt; ++i) {
		now^=1;
		for(int j = 0; j <= n; ++j)
			dp[now][j]=0;
		for(int j = 0; j <= sum; ++j)
			if(dp[now^1][j])
				for(int k = 1; k <= b[i]; ++k)
					for(int ll = max(0, k+j-1-sum); ll <= min(j, k); ++ll) {
						int to = j+b[i]-k-ll;
						dp[now][to]=upd(dp[now][to]+1LL*dp[now^1][j]*c[b[i]-1][k-1]%mod*c[j][ll]%mod*c[sum+1-j][k-ll]%mod*jc[b[i]]%mod);
					}
		sum+=b[i];
		// for(int j = 0; j <= sum; ++j)
		// 	debug(dp[now][j]), debug(' ');
		// debug('\n');
	}
	write(dp[now][0], '\n');
}

signed main() {
	File("count");
	for(int i = 0; i <= 600; ++i)
		c[i][0]=1;
	jc[0]=1;
	for(int i = 1; i <= 600; ++i) {
		jc[i]=1LL*jc[i-1]*i%mod;
		for(int j = 1; j <= i; ++j)
			c[i][j]=upd(c[i-1][j-1]+c[i-1][j]);
	}
	read(t);
	while(t--)
		sol();
	// debug(clock(), '\n');
	return 0;
}