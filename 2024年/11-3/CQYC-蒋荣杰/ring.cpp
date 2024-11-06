#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
// bool st;
const int N = 1.5e5+5;
int n, m, q, opt[N], xx[N], yy[N], a[N], c[N], bl[N], ad[N], tot, ll[N], rr[N];
LL sum[N], sss[N];
vector <int> to[N];

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
LL ask(int x, int l, int r) {
	if(l > r) return 0;
	ad[x]%=(rr[x]-ll[x]+1);
	return sss[min(r+ad[x], rr[x])]-sss[l+ad[x]-1]+sss[max(ll[x]+ad[x]-1-rr[x]+r, ll[x]-1)]-sss[ll[x]-1];
}
// bool fn;
signed main() {
	File("ring");
	// debug((double) (&st-&fn)*1.0/1024/1024, '\n');
	read(n), read(m), read(q);
	int pd = 1, gs = 0;
	for(int i = 1; i <= n; ++i)
		read(c[i]), pd&=(i == 1 || c[i] >= c[i-1]);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= q; ++i) {
		read(opt[i]), read(xx[i]);
		if(opt[i] == 1) 
			++gs, read(yy[i]);
	}
	if(n <= 1000 || gs <= 100) {
		for(int i = 1; i <= n; ++i)
			bl[i]=to[c[i]].size(), to[c[i]].push_back(a[i]);
		for(int i = 1; i <= q; ++i) {
			if(opt[i] == 1) {
				LL ans = 0;
				for(int j = xx[i]; j <= yy[i]; ++j)
					ans+=to[c[j]][(bl[j]-ad[c[j]]+((int) to[c[j]].size()))%((int) to[c[j]].size())];
				write(ans, '\n');
			}
			else
				++ad[xx[i]];
		}
		// debug((double) (&st-&fn)*1.0/1024/1024, "MB\n", clock(), '\n');
		return 0;
	}
	if(pd || m == 1) {
		for(int i = 1; i <= n; ++i)
			rr[c[i]]=i, sum[c[i]]=sum[c[i]]+a[i], 
			sss[i]=sss[i-1]+a[i], ll[c[i]]=(!ll[c[i]] ? i : ll[c[i]]);
		for(int i = 1; i <= m; ++i)
			sum[i]+=sum[i-1];
		for(int i = 1; i <= q; ++i) {
			if(opt[i] == 1) {
				if(c[yy[i]] == c[xx[i]]) 
					write(ask(c[yy[i]], xx[i], yy[i]), '\n');
				else
					write(sum[c[yy[i]]]-sum[c[xx[i]]]-ask(c[yy[i]], yy[i]+1, rr[c[yy[i]]])+ask(c[xx[i]], xx[i], rr[c[xx[i]]]), '\n');
			}
			else
				++ad[xx[i]];
		}
		// debug((double) (&st-&fn)*1.0/1024/1024, "MB\n", clock(), '\n');
		return 0;
	}
	// debug((double) (&st-&fn)*1.0/1024/1024, "MB\n", clock(), '\n');
	return 0;
}