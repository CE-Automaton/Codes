#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5, V = 2e3+5;
int sub, t, n, a[N], mx, lst[2][N];

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

signed main() {
	File("highscore");
	read(sub);
	read(t);
	while(t--) {
		read(n);
		mx=0;
		for(int i = 1; i <= n; ++i)
			read(a[i]), mx=max(mx, a[i]);
		int now = 0;
		for(int i = 1; i < a[1]; ++i)
			lst[0][i]=(i == a[1]-i ? 1 : 2);
		for(int i = 2; i <= n; ++i) {
			now^=1;
			int mn = inf;
			for(int j = 1; j < a[i-1]; ++j)
				mn=min(mn, lst[now^1][j]);
			for(int j = 1; j < a[i]; ++j)
				if(a[i]-j < a[i-1])
					lst[now][j]=min(lst[now^1][a[i]-j]+(j == a[i]-j ? 0 : 1), mn+(j == a[i]-j ? 1 : 2));
				else
					lst[now][j]=mn+(j == a[i]-j ? 1 : 2);
		}
		int ans = inf;
		for(int i = 1; i < a[n]; ++i)
			ans=min(ans, lst[now][i]);
		write(ans, '\n');
	}
	return 0;
}