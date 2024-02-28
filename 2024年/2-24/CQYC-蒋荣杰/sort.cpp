#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int t, n, a[N], zhan[N], tot, ans, tr[N];

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
void add(int x, int w) {
	while(x)
		tr[x]+=w, x-=(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x <= n)
		ret+=tr[x], x+=(x&(-x));
	return ret;
}
int check() {
	tot=0;
	for(int i = 1; i <= n; ++i)
		tr[i]=0;
	for(int i = 1; i <= n; ++i) {
		while(tot && zhan[tot] < a[i]) --tot;
		if(ask(a[i]) != tot) return 0;
		zhan[++tot]=a[i];
		add(a[i], 1);
	}
	return 1;
}

signed main() {
	File("sort");
	read(t);
	while(t--) {
		ans=0;
		read(n);
		for(int i = 1; i <= n; ++i)
			read(a[i]);
		for(int i = 1; i <= n; ++i)
			for(int j = i+1; j <= n; ++j)
				swap(a[i], a[j]), ans+=check(), swap(a[i], a[j]);
		write(ans, '\n');
	}
	return 0;
}
