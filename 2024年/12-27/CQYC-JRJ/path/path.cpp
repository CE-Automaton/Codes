#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 305;
int t, td, n, a[N], b[N], wn/*万能*/, gs[N], ss[N], to[N];
vector <int> bz[N], vis[N][N], gss[N], www;

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
template <typename T> void readd(T& x) {
	x = 0; int f = 0, ff = 0; char c = getchar();
	while((c < '0' || c > '9') && !ff) f |= (c == '-'), ff |= (c == '?'), c=getchar();
	if(ff) { x=-1; return ; }
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
	File("path");
	read(t), read(td);
	while(t--) {
		read(n);
		int pd = 0;
		wn=0;
		www.clear();
		for(int i = 0; i <= n; ++i) {
			gs[i]=ss[i]=0;
			gss[i].clear();
			for(int j = 0; j <= n; ++j)
				vis[i][j].clear();
		}
		for(int i = 1; i <= n; ++i) {
			readd(a[i]), readd(b[i]);
			pd|=(a[i] > n || b[i] > n);
			if(a[i] == -1 && b[i] == -1)
				++wn, www.push_back(i);
			else
				if(a[i] == -1)
					++gs[b[i]], gss[b[i]].push_back(i);
				else
					if(b[i] == -1)
						bz[a[i]].push_back(i);
					else
						vis[b[i]][a[i]].push_back(i);
		}
		if(pd) {
			puts("-1");
			continue;
		}
		if(td == 3) {
			for(int i = 1; i <= n; ++i) 
				++ss[b[i]];
			for(int i = 1; i <= n; ++i)
				if(ss[i]) {
					if(vis[i][0].size() == 0) {
						if(!gss[i].empty())
							vis[i][0].push_back(gss[i].back()), gss[i].pop_back();
						else
							pd=1;
					}
					while(vis[i][0].size()%i != 0 && !gss[i].empty())
						vis[i][0].push_back(gss[i].back()), gss[i].pop_back();
					if(vis[i][0].size()%i != 0) pd=1;
					for(int j = 1; j <= n; ++j) {
						if(vis[i][j].size() == 0 && !gss[i].empty())
							vis[i][j].push_back(gss[i].back()), gss[i].pop_back();
						if(vis[i][j].size() != 0 && vis[i][j-1].size() == 0)
							pd=1;
					}
				}
			if(pd) {
				puts("-1");
				continue;
			}
			for(int i = 1; i <= n; ++i)
				if(ss[i]) {
					for(int p = 1; p*i <= vis[i][0].size(); ++p)
						for(int j = 0; j < i; ++j)
							to[vis[i][0][j+p*i-i]]=vis[i][0][(j+1)%i+p*i-i];
					for(int j = 1; j <= n; ++j)
						if(vis[i][j].size() != 0)
							for(int k = 0; k < vis[i][j].size(); ++k)
								to[vis[i][j][k]]=vis[i][j-1][0];
				}
			for(int i = 1; i <= n; ++i)
				write(to[i], ' ');
			putchar('\n');
			continue;
		}
		if(td == 2) {
			for(int i = 1; i <= n; ++i) 
				++gs[b[i]];
			for(int i = 1; i <= n; ++i)
				if(gs[i]) {
					if(vis[i][0].size()%i != 0) pd=1;
					for(int j = 1; j <= n; ++j)
						if(vis[i][j].size() != 0 && vis[i][j-1].size() == 0)
							pd=1;
				}
			if(pd) {
				puts("-1");
				continue;
			}
			for(int i = 1; i <= n; ++i)
				if(gs[i]) {
					for(int p = 1; p*i <= vis[i][0].size(); ++p)
						for(int j = 0; j < i; ++j)
							to[vis[i][0][j+p*i-i]]=vis[i][0][(j+1)%i+p*i-i];
					for(int j = 1; j <= n; ++j)
						if(vis[i][j].size() != 0)
							for(int k = 0; k < vis[i][j].size(); ++k)
								to[vis[i][j][k]]=vis[i][j-1][0];
				}
			for(int i = 1; i <= n; ++i)
				write(to[i], ' ');
			putchar('\n');
			continue;
		}
	}
	return 0;
}