#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, k, xx, vis[2][N], ans[N];

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
int pd(int x) {
	for(int i = x; i >= 1; --i)
		if(!vis[0][i] && vis[1][i]) return 1;
		else if(vis[0][i] && !vis[1][i]) return 0;
	return 1;
}

signed main() {
	File("mcmf");
	read(n);
	for(int i = 0; i < n; ++i) {
		read(k);
		for(int j = 1; j <= k; ++j)
			read(xx), vis[i][xx]=1;
	}
	int pdd = 1;
	for(int i = 1000000; i >= 1; --i)
		if(vis[0][i] && vis[1][i]) {
			pdd=0;
			int l = i;
			while(vis[0][l] || vis[1][l])
				++l;
			ans[l]=1;
			if(pd(l-1)) {
				for(int j = l-1; j >= 1; --j)
					ans[j]=vis[0][j];
			}
			else {
				for(int j = l-1; j >= 1; --j)
					ans[j]=vis[1][j];
			}
			break;
		}
		else
			ans[i]=(vis[0][i]|vis[1][i]);
	int st = 1000001;
	while(!ans[st]) --st;
	while(st >= 1) putchar('0'+ans[st]), --st;
	return 0;
}
