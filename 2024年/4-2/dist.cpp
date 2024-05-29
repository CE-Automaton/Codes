#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int N = 75;
int t, n, h, w, xx[N], yy[N], pd[N][N], gs[N][N], dis[N][N], fx[4][2]={{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
LL ans;
vector <int> sx, sy;
queue <pii> q;

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
void sol() {
	memset(pd, 0, sizeof pd);
	sx.clear(), sy.clear();
	read(h), read(w), read(n);
	ans=upd(1LL*w*(w-1)*(w+1)/6%mod*h%mod*h%mod+1LL*h*(h-1)*(h+1)/6%mod*w%mod*w%mod);
	debug(ans, "!?\n");
	sx.push_back(0), sx.push_back(h);
	sy.push_back(0), sy.push_back(w);
	for(int i = 1; i <= n; ++i) {
		read(xx[i]), read(yy[i]), sx.push_back(xx[i]),
		sy.push_back(yy[i]), sx.push_back(xx[i]-1), sy.push_back(yy[i]-1), 
		ans=upd(upd(upd(upd(ans-1LL*(xx[i]-1)*xx[i]/2%mod*w%mod+mod)-1LL*(h-xx[i]+1)*(h-xx[i])/2%mod*w%mod+mod)
		-1LL*(yy[i]-1)*yy[i]/2%mod*h%mod+mod)-1LL*(w-yy[i]+1)*(w-yy[i])/2%mod*h%mod+mod);
		for(int j = 1; j < i; ++j)
			ans=upd(ans+upd(abs(xx[j]-xx[i])+abs(yy[j]-yy[i])));
	}
	sort(sx.begin(), sx.end());
	sx.erase(unique(sx.begin(), sx.end()), sx.end());
	sort(sy.begin(), sy.end());
	sy.erase(unique(sy.begin(), sy.end()), sy.end());
	// debug("!!!\n");
	for(int i = 1; i <= n; ++i)
		xx[i]=(lower_bound(sx.begin(), sx.end(), xx[i])-sx.begin()), 
		yy[i]=(lower_bound(sy.begin(), sy.end(), yy[i])-sy.begin()), 
		pd[xx[i]][yy[i]]=1;
	h=sx.size()-1, w=sy.size()-1;
	for(int i = 1; i <= h; ++i)
		for(int j = 1; j <= w; ++j)
			gs[i][j]=1LL*(sx[i]-sx[i-1])*(sy[j]-sy[j-1])%mod;
	for(int i = 1; i <= h; ++i)
		for(int j = 1; j <= w; ++j)
			if(!pd[i][j]) {
				memset(dis, -1, sizeof dis);
				dis[i][j]=0;
				q.push(pii {i, j});
				// debug(i, j, h, w, ":::\n");
				while(!q.empty()) {
					pii it = q.front(); q.pop();
					// debug(it.first, it.second, "\n");
					if(it > pii{i, j}) 
						ans=upd(ans+1LL*(dis[it.first][it.second]-abs(it.first-i)-abs(it.second-j))*gs[i][j]%mod*gs[it.first][it.second]%mod);
					for(int o = 0; o < 4; ++o) {
						int X = it.first+fx[o][0], Y = it.second+fx[o][1];
						if(X <= 0 || X > h || Y <= 0 || Y > w || pd[X][Y] || dis[X][Y] != -1) continue;
						dis[X][Y]=dis[it.first][it.second]+1;
						q.push(pii {X, Y});
					}
				}
			}
	debug("???\n");
	write(ans, '\n');
}

signed main() {
	read(t);
	while(t--)
		sol();
	return 0;
}