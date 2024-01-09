#include <bits/stdc++.h>
#define mod 1000003
using namespace std;
const int N = 1e6+5;
int n, h[N], ans;

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
	freopen("repair.in", "r", stdin);
	freopen("repair.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(h[i]);
	for(int i = 1; i <= n; ++i) {
		int pd = 1;
		for(int j = i; j-1 >= 1; --j)
			pd&=(h[j-1] >= h[j]);
		for(int j = i; j+1 <= n; ++j)
			pd&=(h[j] <= h[j+1]);
		if(pd) {
//			cout<<"!?\n";
			int l = i, r = i;
			while(l != 1 && r != n) {
				while(l-1 >= 1 && h[l-1] <= h[l])
					--l;
				while(r+1 <= n && h[r] >= h[r+1])
					++r;
				if(l == 1 || r == n) break;
				int w = min(h[l-1], h[r+1]);
//				cout<<l<<" "<<r<<" "<<h[l]<<"->"<<w<<"\n";
				ans=(ans+1LL*(r-l+1)*(w-h[l])%mod*(h[l-1]+h[r+1])%mod+1LL*(r-l+1)*(1LL*(h[l]+w-1)*(w-h[l])/2%mod)%mod)%mod;
				h[l]=h[r]=w;
				while(l-1 >= 1 && h[l-1] <= h[l])
					--l;
				while(r+1 <= n && h[r] >= h[r+1])
					++r;
			}
			write(ans, '\n');
			return 0;
		}
	}
	return 0;
}
