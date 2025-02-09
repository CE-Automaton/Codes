#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int s, q, dp[78][78][78][78], aa, bb, cc, dd;

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
int sol(int x, int y, int a, int b) {//x,y先手; a,b后手;
	if(x <= 0) return 0;
	if(a <= 0) return 1;
	int &now = dp[x][y][a][b];
	if(now != -1) return now;
	now=0;
	if(b >= 1)
		now|=(sol(a, b-1, x, y)^1);
	if(x > b*s)
		now|=(sol(a-max(x-b*s, 0), b, x, y)^1);
	return now;
}

signed main() {
	File("game");
	read(s), read(q);
	for(int i = 0; i <= 75; ++i)
		for(int j = 0; j <= 75; ++j)
			for(int k = 0; k <= 75; ++k)
				for(int l = 0; l <= 75; ++l)
					dp[i][j][k][l]=-1;
	while(q--) {
		read(aa), read(bb), read(cc), read(dd);
		if(sol(aa, bb, cc, dd))
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}