#include <bits/stdc++.h>
#define int long long
using namespace std;
long long t, n, ans, dp[55];

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
	int l = 1, r = 1000000, ret = 0;
	while(l <= r) {
		int mid = (l+r)/2;
		if(mid*mid*mid <= x)
			ret=mid, l=mid+1;
		else
			r=mid-1;
	}
	return ret;
}

signed main() {
	freopen("math.in", "r", stdin);
	freopen("math.out", "w", stdout);
	read(t);
	while(t--) {
		read(n);
		ans=sqrtt(n);
//		write(ans, '\n');
		for(int i = 2; i <= 1000000 && (n+i)/(i*i*i) >= i*i; ++i) {
//			write(i, ' ');
			int tot = 2;
			dp[1]=i, dp[2]=1LL*i*i*i;
			while((n+dp[tot-1])/dp[tot] >= 1LL*i*i) {
				++tot;
				dp[tot]=1LL*i*i*dp[tot-1]-dp[tot-2];
			}
//			write(i, ' '), write(dp[tot], ' '), write(tot, '\n');
			if(tot == 5) {
				int l = i, r = 100, ret = i, ll = i;
				while(l <= r) {
					int mid = (l+r)/2;
					if(mid*mid*mid*mid*mid*mid*mid*mid*mid-3LL*mid*mid*mid*mid*mid+mid <= n)
						ret=mid, l=mid+1;
					else
						r=mid-1;
				}
				ans+=3*(ret-ll+1);
				ll=l=ret+1, r=372;
				while(l <= r) {
					int mid = (l+r)/2;
					if(mid*mid*mid*mid*mid*mid*mid-2LL*mid*mid*mid <= n)
						ret=mid, l=mid+1;
					else
						r=mid-1;
				}
				ans+=2*(ret-ll+1);
				ll=l=ret+1, r=3981;
				while(l <= r) {
					int mid = (l+r)/2;
					if(mid*mid*mid*mid*mid-mid <= n)
						ret=mid, l=mid+1;
					else
						r=mid-1;
				}
				ans+=(ret-ll+1);
				break;
			}
			ans+=tot-2;
		}
		write(ans, '\n');
	}
	return 0;
}
