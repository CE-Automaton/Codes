#include <bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
const int N = 1e5+5;
long long t, n, dp[N];

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
int sqrtt(int x) {
	int l = 1, r = 1000000000, ret = 0;
	while(l <= r) {
		int mid = (l+r)/2;
		if(mid*mid <= x)
			ret=mid, l=mid+1;
		else
			r=mid-1;
	}
	return ret;
}
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	freopen("quencese.in", "r", stdin);
	freopen("quencese.out", "w", stdout);
	read(t);
	while(t--) {
		read(n);
		int mx = sqrtt(n), az = sqrtt(mx), ans = 0;
		if(mx == 1) {
			puts("1");
			continue; 
		}
		if(mx == 2) {
			puts("2");
			continue; 
		}
//		write(mx, ' '), write(az, '\n');
		dp[1]=dp[2]=dp[3]=1;
		ans=3;
		for(int i = 2, sum = 2; i <= az; ++i) {
			int l = i*i, r = min((i+1)*(i+1)-1, mx);
			if(l <= az) 
				for(int j = l; j <= min(r, az); ++j)
					dp[j]=sum;
			ans=upd(ans+1LL*(r-l+1)*sum%mod);
			sum=upd(sum+dp[i+1]);
		}
		write(ans, '\n');
	}
	return 0;
}
