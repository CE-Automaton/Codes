#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e3+5;
int n, m, u, v, ds[N], dt[N], cnt, cntt;
vector <int> inn, ou;
bitset<N> s[N], t[N], ss;
struct qwq {
	int a, b, c, d;
}ans[N*N], anss[N*N];

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
	read(n), read(m);
	for(int i = 1; i <= m; ++i)
		read(u), read(v), 
		++ds[u], ++ds[v], s[u][v]=s[v][u]=1;
	for(int i = 1; i <= m; ++i)
		read(u), read(v), 
		++dt[u], ++dt[v], t[u][v]=t[v][u]=1;
	for(int i = 1; i <= n; ++i)
		if(ds[i] != dt[i]) {
			puts("NO");
			return 0;
		}
	puts("YES");
	for(int i = 1; i <= n; ++i) {
		inn.clear(), ou.clear();
		for(int j = 1; j <= n; ++j) {
			if(s[i][j] && !t[i][j]) 
				ou.push_back(j);
			if(!s[i][j] && t[i][j])
				inn.push_back(j);
		}
		while(!inn.empty() && !ou.empty()) {
			int u = inn.back(), v = ou.back();
			inn.pop_back(), ou.pop_back();
			ss=(s[u]&(~s[v]));
			ss[i]=ss[u]=ss[v]=0;
			if(ss.count()) {
				int d = ss._Find_first();
				s[i][v]=s[v][i]=s[u][d]=s[d][u]=0;
				s[i][u]=s[u][i]=s[v][d]=s[d][v]=1;
				ans[++cnt]=qwq {i, v, u, d};
			}
			else {
				ss=((~t[u])&t[v]);
				ss[i]=ss[u]=ss[v]=0;
				int d = ss._Find_first();
				t[i][u]=t[u][i]=t[v][d]=t[d][v]=0;
				t[i][v]=t[v][i]=t[u][d]=t[d][u]=1;
				anss[++cntt]=qwq {i, v, u, d};
			}
		}
		for(int j = 1; j <= n; ++j)
			s[i][j]=s[j][i]=t[i][j]=t[j][i]=0;
	}
	write(cnt+cntt, '\n');
	for(int i = 1; i <= cnt; ++i)
		write(ans[i].a, ' '), write(ans[i].b, ' '), write(ans[i].c, ' '), write(ans[i].d, '\n');
	for(int i = cntt; i >= 1; --i)
		write(anss[i].a, ' '), write(anss[i].b, ' '), write(anss[i].c, ' '), write(anss[i].d, '\n');
	return 0;
}
