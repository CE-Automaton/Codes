#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 9;
int n, a[N][N], gs;

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
void dfs(int x, int y) {
	if(x == n+1) {
		++gs;
		return ;
	}
	if(x == y) {
		if(x != 1 && a[x][y] < a[x-1][y]) return ;
		if(y != 1 && a[x][y] < a[x][y-1]) return ;
		dfs(x+(y == n), y%n+1);
		return ;
	}
	for(int i = 1; i <= 8; ++i)
		if((x == 1 || (x != 1 && a[x-1][y] <= i)) && (y == 1 || (y != 1 && a[x][y-1] <= i))) {
			a[x][y]=i;
			dfs(x+(y == n), y%n+1);
		}
}

signed main() {
	File("suno");
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i][i]);
	dfs(1, 1);
	write(gs, '\n');
	return 0;
}