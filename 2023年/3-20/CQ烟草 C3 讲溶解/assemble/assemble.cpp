#include <bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n, m, ans[4005][4005], gs[2][4005][4005], vis[4005][4005], x, y, tot[3], fx[4][2]={
{0, -1}, {0, 1}, {-1, 0}, {1, 0}}, sum;
struct qwq {
	int l, r;
}que[3][16000005];

template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}

signed main() {
	freopen("assemble.in", "r", stdin);
	freopen("assemble.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i) {
		read(x), read(y);
		tot[0]=tot[1]=tot[2]=0;
		gs[0][x+m][y+m]=1;
		que[0][++tot[0]]=qwq{x+m, y+m};
		int now = 0, lst = 2, llst = 1, haha = 0;
		for(int j = 1; j <= m; ++j) {
			haha^=1;
			now = (now+1)%3;
			lst = (lst+1)%3;
			llst = (llst+1)%3;
			tot[now]=0;
			for(int o = 1; o <= tot[llst]; ++o)
				gs[haha][que[llst][o].l][que[llst][o].r]=0;
			for(int o = 1; o <= tot[lst]; ++o) {
				int xx = que[lst][o].l, yy = que[lst][o].r;
				for(int p = 0; p <= 3; ++p) {
					int X = xx+fx[p][0], Y = yy+fx[p][1];
					if(gs[haha][X][Y] == 0)
						que[now][++tot[now]]=qwq{X, Y};
					gs[haha][X][Y]=(gs[haha][X][Y]+gs[haha^1][xx][yy])%mod;
				}
			}
		}
		if(i == 1)
			for(int o = 1; o <= tot[now]; ++o)
				ans[que[now][o].l][que[now][o].r]=gs[haha][que[now][o].l][que[now][o].r],
				++vis[que[now][o].l][que[now][o].r];
		else
			for(int o = 1; o <= tot[now]; ++o)
				ans[que[now][o].l][que[now][o].r]=1LL*ans[que[now][o].l][que[now][o].r]*gs[haha][que[now][o].l][que[now][o].r]%mod,
				++vis[que[now][o].l][que[now][o].r];
		for(int o = 1; o <= tot[now]; ++o)
			gs[haha][que[now][o].l][que[now][o].r]=0;
		for(int o = 1; o <= tot[lst]; ++o)
			gs[haha^1][que[lst][o].l][que[lst][o].r]=0;
	}
	for(int i = 0; i <= 4*m; ++i)
		for(int j = 0; j <= 4*m; ++j)
			ans[i][j] = (vis[i][j] != n ? 0 : ans[i][j]), 
			sum=(sum+ans[i][j])%mod;
	write(sum);
	return 0;
}
