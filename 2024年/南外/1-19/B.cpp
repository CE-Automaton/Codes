#include <bits/stdc++.h>
#define int LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const signed N = 1e6+5;
int n, E, a[N], b[N], c[N], su[N], st[N][22], to[N], cnt, tr[N], ans;
struct qwq {
	int u, v;
}az[N];

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
int stask(int l, int r) {
	int ln = log2(r-l+1);
	return max(st[l][ln], st[r-(1<<ln)+1][ln]);
}
signed comp(qwq A, qwq B) {
	return A.u < B.u;
}
void add(int x, int w) {
	while(x <= cnt)
		tr[x]+=w, x=x+(x&(-x));
}
int ask(int x, int ret = 0) {
	while(x >= 1)
		ret+=tr[x], x=x-(x&(-x));
	return ret;
}

signed main() {
	File("top");
	read(n), read(E);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= n; ++i)
		read(b[i]), st[i][0]=min(a[i], b[i])-E;
	for(int i = 1; i <= 19; ++i)
		for(int j = 1; j+(1<<i)-1 <= n; ++j)
			st[j][i]=max(st[j][i-1], st[j+(1<<(i-1))][i-1]);
	for(int i = 1; i <= n; ++i)
		c[i]=min(0LL, b[i]-a[i])+c[i-1], 
		su[i]=su[i-1]+b[i]-a[i], az[i]=qwq {su[i], i};
	az[0]=qwq {0, 0};
	sort(az, az+1+n, comp);
	for(int i = 0; i <= n; ++i) {
		if(i == 0 || az[i].u != az[i-1].u) 
			to[++cnt]=az[i].u;
		su[az[i].v]=cnt;
	}
	ans=n*(n+1)/2;
	int qvq = 0;
	for(int i = 1; i <= n; ++i) {
		while(qvq < i && stask(qvq+1, i) > c[i]-c[qvq])
			add(su[qvq], -1), ++qvq;
		add(su[i-1], 1);
		ans-=i-ask(su[i]);
	}
	write(ans, '\n');
	return 0;
}