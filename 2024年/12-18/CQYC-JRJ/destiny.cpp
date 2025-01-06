#include <bits/stdc++.h>
#define mod 998244353
#define inv (mod-mod/2)
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3e3+5;
int n, u, v, lll[N][N][8], rrr[N][6], ans, sum;
vector <int> to[N];

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
void dfs(int x, int fa) {
	for(int j = 1; j <= n; ++j)
		lll[x][j][1]=lll[x][j][2]=0, lll[x][j][0]=1;
	lll[x][0][1]=1;
	for(int y : to[x])
		if(y != fa) {
			dfs(y, x);
			for(int i = 1; i <= n; ++i) {
				for(int o = 1; o >= 0; --o)
					lll[x][i][o+1]=upd(lll[x][i][o+1]+1LL*lll[x][i][o]*lll[y][i-1][1]%mod);
				lll[x][i][2]=upd(lll[x][i][2]+lll[y][i][2]);
			}
		}
}

signed main() {
	File("destiny");
	read(n);
	for(int i = 2; i <= n; ++i)
		read(u), read(v), to[u].push_back(v), to[v].push_back(u);
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j)
			lll[i][j][1]=lll[i][j][2]=lll[i][j][3]=lll[i][j][4]=0,
			rrr[j][1]=rrr[j][2]=rrr[j][3]=rrr[j][4]=0,
			lll[i][j][0]=rrr[j][0]=1;
		for(int y : to[i]) {
			dfs(y, i);
			for(int j = 1; j <= n; ++j)
				for(int o = 3; o >= 0; --o) {
					lll[i][j][o+1]=upd(lll[i][j][o+1]+1LL*lll[i][j][o]*lll[y][j-1][1]%mod);
					rrr[j][o+1]=upd(rrr[j][o+1]+1LL*rrr[j][o]*lll[y][j-1][1]%mod);
					if(o+2 <= 4)
						lll[i][j][o+2]=upd(lll[i][j][o+2]+1LL*lll[i][j][o]*lll[y][j][2]%mod);
				}
		}
		for(int j = 1; j <= n; ++j)
			sum=upd(sum+lll[i][j][4]), ans=upd(ans+rrr[j][4]);
	}
	// debug(sum, ans, "???\n");
	write(upd(1LL*upd(sum-ans+mod)*inv%mod+ans), '\n');
	return 0;
}
/*
7
1 2
1 3
1 5
4 6
7 6
6 1
*/