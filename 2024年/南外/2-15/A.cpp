#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e5+5;
int n, m, k, s, t, ds[2][N];
LL ans;
set <int> g[2][N], st[2];
set< pair<int,int> > dl;
queue <int> az;
queue< pair<int,int> > q;

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

int main() {
    File("anger");
	read(n), read(m), read(k), read(s), read(t);
	for(int i = 1; i <= n; ++i)
		st[0].insert(i);
	for(int i = 1; i <= m; ++i)
		st[1].insert(i);
	memset(ds, 0x3f, sizeof(ds));
	ds[0][s]=ds[1][t]=0;
	st[0].erase(s),st[1].erase(t);
	q.push({0, s});
	q.push({1, t});
	int cnt[2]={n, m};
	for(int i = 1; i <= k; ++i) 
		read(s), read(t), dl.insert({s, t}), g[0][s].insert(t), g[1][t].insert(s);
	while(q.size()) {
		int now=q.front().first, u=q.front().second;
		q.pop();
		--cnt[now];
		ans+=1ll*(ds[now][u]+1)*cnt[now^1];
		for(auto v:st[now^1])
			if(!g[now][u].count(v)) {
				ds[now^1][v]=ds[now][u]+1;
				az.push(v);
				q.push({now^1,v});
			}
        while(!az.empty())
			st[now^1].erase(az.front()), az.pop();
	}
	for(auto x : dl) {
		int t = min(ds[0][x.first], ds[1][x.second]);
		ans-=(t > 1e9 ? 0 : t+1);
	}
	write(ans-1, '\n');
	return 0;
}