#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 3e5+5;
int n, c[N];
LL f[2][N][2];
struct qwq {
	int t; LL w;
};
vector <qwq> to[N];

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
int check(LL ss) {
	for(int i = 1; i <= n; ++i)
		if(c[i]+c[i+n] > ss) return 0;
	// debug("???\n");
	// (qwq {i+n, c[i]});
	// (qwq {i, c[i+n]-ss});
	memset(f, -0x3f, sizeof f);
	f[0][n][1]=0, f[0][n][0]=c[n+n]-ss;
	f[1][n][0]=0, f[1][n][1]=c[n];
	for(int op = 0; op <= 1; ++op)
		for(int i = n-1; i >= 1; --i)
			f[op][i][0]=max(f[op][i+1][0], f[op][i+1][1]+c[i+n]-ss), 
			f[op][i][1]=max(f[op][i+1][1], f[op][i+1][0]+c[i]);
	return f[0][1][0] <= 0 /*不存在正环*/ && max(f[1][1][1], f[1][1][0]+f[0][1][1])/*S2n应该大于的值？*/ <= ss;
}

signed main() {
	read(n);
	for(int i = 1; i <= n+n; ++i)
		read(c[i]);
	LL l = 0, r = 1000000000000000000, ans=-1;
	while(l <= r) {
		LL mid = ((l+r)>>1);
		if(check(mid))
			ans=mid, r=mid-1;
		else 
			l=mid+1;
	}
	write(ans, '\n');
	return 0;
}