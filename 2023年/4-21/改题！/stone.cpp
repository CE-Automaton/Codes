#include <bits/stdc++.h>
#define mod 1000000007
#define int long long
using namespace std;
const int N = 1e7+5;
int n, a[N], ans, tot;
struct dot{
	int now, gs;
}zhan[N]; 

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
//	freopen("stone.in", "r", stdin);
//	freopen("stone.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) 
		read(a[i]);
	for(int i = n; i >= 1; --i) {
		zhan[++tot]=dot {a[i], 1};
		
	}
	return 0;
}
