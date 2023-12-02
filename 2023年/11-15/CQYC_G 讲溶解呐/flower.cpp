#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5, V = 1e6;
int n, q, fa[N], vv[N], cnt[N], to[V+5], pd[N], pd2[N], ans[N], tot, u, v, zhan[N];
vector <int> ltk[N];

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
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
void merge(int x, int y) {
	x=find(x), y=find(y);
	if(x == y) return ;
	int ppd = (pd[x]|pd[y]), ppd2 = (pd2[x]|pd2[y]);
	if(cnt[x] < cnt[y]) swap(x, y);
	cnt[x]+=cnt[y];
	pd[x]=ppd;
	pd2[x]=ppd2;
	fa[y]=x;
}
long long gcd(long long x, long long y) {
	int aa = __builtin_ctz(x), bb = __builtin_ctz(y);
	long long cc;
	cc=min(aa, bb), y>>=bb;
	while(x) {
		x>>=aa;
		int d = abs(y-x);
		aa=__builtin_ctz(d);
		if(x < y) y=x;
		x=d;
	}
	return (y<<cc);
}

signed main() {
	freopen("flower.in", "r", stdin);
	freopen("flower.out", "w", stdout);
	read(n), read(q);
	for(int i = 1; i <= n; ++i) {
		fa[i]=i, cnt[i]=1;
		read(vv[i]);
		if(vv[i]%2 == 0)
			pd[i]=1;
		else
			pd2[i]=1;
		if(!to[vv[i]]) to[vv[i]]=i;
		else merge(to[vv[i]], i), to[vv[i]]=find(to[vv[i]]);
	}
	for(int i = 2; i <= V; ++i) {
		int lst = 0;
		for(int j = i; j <= V; j+=i) 
			if(to[j]) {
				if(!lst) lst=find(to[j]);
				else merge(lst, to[j]), lst=find(lst);
			}
	}
	for(int i = 1; i <= n; ++i) 
		fa[i]=find(i), ltk[fa[i]].push_back(i);
	for(int i = 1; i <= q; ++i) {
		read(u), read(v);
		if(vv[u] == 1 || vv[v] == 1) {
			putchar('-');
			putchar('1');
			putchar('\n');
			continue;
		}
		u=find(u), v=find(v);
		if(u == v) {
			putchar('0');
			putchar('\n');
			continue;
		}
		if((pd[u] && pd2[v]) || (pd[v] && pd2[u])) {
			putchar('1');
			putchar('\n');
			continue;
		}
		int pdd = 0;
		for(int j = 1; j <= n; ++j) {
			int l = 0, r = 0;
			for(int x : ltk[u])
				if(gcd(1LL*vv[j]*(vv[j]+1), 1LL*vv[x]) != 1) {
					l=1;
					break;
				}
			for(int y : ltk[v])
				if(gcd(1LL*vv[j]*(vv[j]+1), 1LL*vv[y]) != 1) {
					r=1;
					break;
				}
			if(l && r) {
				pdd=1;
				break;
			}
		}
		if(pdd) {
			putchar('1');
			putchar('\n');
		}
		else {
			putchar('2');
			putchar('\n');
		}
	}
	return 0;
}
