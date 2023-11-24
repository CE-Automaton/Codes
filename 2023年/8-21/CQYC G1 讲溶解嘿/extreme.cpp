#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 1e6+5;
int t, n, a[N];

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
	freopen("extreme.in", "r", stdin);
	freopen("extreme.out", "w", stdout);
	read(t);
	while(t--) {
		read(n);
		for(int i = 1; i <= n; ++i)
			read(a[i]);
		int sum = 0; 
		for(int l = 1; l <= n; ++l) {
			for(int r = l; r <= n; ++r) {
				int lst = 100005, ans = 0;
				for(int i = r; i >= l; --i) 
					if(a[i] > lst) {
						int x = (a[i]+lst-1)/lst;
						ans=upd(ans+x-1);
						lst=a[i]/x;
					}
					else
						lst=a[i];
				sum=upd(sum+ans);
			} 
		}
		write(sum, '\n');
	}
	return 0;
}
