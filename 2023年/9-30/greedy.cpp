#include <bits/stdc++.h>
#define mod 147744151
#define int long long
using namespace std;
const int N = 1e6+5;
int n, m, dp[2][N];

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
//	freopen("greedy.in", "r", stdin);
//	freopen("greedy.out", "w", stdout);
	read(n), read(m);
	if(m == 1) {
		write((n-1)%mod, '\n');
		return 0;
	}
	if(m == 2) {
		int az = (long long) sqrt(2LL*n);
		if(az*(az+1)/2 >= n)
			write(min(az, n-1)%mod, '\n');
		else
			write(min(az+1, n-1)%mod, '\n');
		return 0;
	} 
	int qwq = (long long) ceil(log2(n));
	if(m >= qwq) {
		write(qwq, '\n');
		return 0;
	}
	int r = 960625, now = 0;
	for(int i = 1; i <= r; ++i)
		dp[now][i]=i;
	for(int i = 3; i <= m; ++i) {
		now^=1;
		dp[now][1]=1;
		int sum = 1; 
		for(int j = 2; j <= r; ++j) {
			dp[now][j]=dp[now][j-1]+dp[now^1][j-1];
			sum+=dp[now][j];
			if(sum >= n) {
				r=j;
				break;
			}
		}
	}
	int sum = 0;
	for(int i = 1; i <= r; ++i)
		if(sum+dp[now][i] >= n) {
			write(i, '\n');
			break;
		}
		else
			sum+=dp[now][i];
	return 0;
}
