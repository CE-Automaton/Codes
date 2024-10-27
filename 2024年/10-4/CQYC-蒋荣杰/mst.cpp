#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int N = 1e5+5;
int sedd, k, n, opt, u[N], v[N], w[N], vis[N], cnt, fa[N], cntt[N], l, r;
vector <int> to[N];
set<pii> q;
namespace qwq
{
	std::mt19937 eng;
	inline void init(register int Seed){eng.seed(Seed);}
	inline int readW(){return std::uniform_int_distribution<int>(0,1000000000)
	(eng);}
}

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
void ccc(int x) {
	for(int i = 0; i < to[l].size(); ++i)
		if(!vis[to[l][i]]) {
			q.erase(pii {w[to[l][i]], to[l][i]});
			vis[to[l][i]]=1;
		}
	to[l].clear();
}
void add(int x, int pd) {
	int gs = min(k-1, r-l+1);
	if(!pd) {
		for(int i = x+1; i <= x+gs; ++i)
			++cnt, w[cnt]=qwq::readW(), u[cnt]=x, v[cnt]=i, q.insert(pii{w[cnt], cnt}), 
			to[x].push_back(cnt), to[i].push_back(cnt);
	}
	else {
		for(int i = x-1; i >= x-gs; --i)
			++cnt, w[cnt]=qwq::readW(), u[cnt]=x, v[cnt]=i, q.insert(pii{w[cnt], cnt}), 
			to[x].push_back(cnt), to[i].push_back(cnt);
	}
}
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
int merge(int x, int y) {
	x=find(x), y=find(y);
	if(x == y) return 0;
	if(cntt[y] > cntt[x])
		swap(x, y); 
	fa[y]=x, cntt[x]+=cntt[y];
	return 1;
}
void anss() {
	for(int i = l; i <= r; ++i)
		fa[i]=i, cntt[i]=1;
	LL annn = 0;
	for(auto it : q) 
		if(merge(u[it.second], v[it.second]))
			annn+=it.first;
	write(annn, '\n');
}

signed main() {
	File("mst");
	read(sedd), read(k), read(n);
	l=r=n+1;
	qwq::init(sedd);
	for(int i = 1; i <= n; ++i) {
		read(opt);
		if(opt == 1) {
			ccc(l);
			++l;
		}
		if(opt == 2) {
			ccc(r);
			--r;
		}
		if(opt == 3) {
			add(l-1, 0);
			--l;
		}
		if(opt == 4) {
			add(r+1, 1);
			++r;
		}
		if(opt == 5)
			anss();
	}
	return 0;
}