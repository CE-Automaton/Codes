#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e3+5;
int n, m, cnt, tot, dp[N][1524];
LL az[N], k;
vector <LL> to[N];
struct ovo {
	LL v;
	bool operator <(const ovo& A) const {
		return A.v < v;
	}
};
priority_queue <ovo> qq, pp;
struct qwq {
	LL a, b;
}p[N];
struct qaq {
	LL a;
	int b, c;
}op[N];

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
int comp(qaq A, qaq B) {
	return A.a < B.a;
}

signed main() {
	File("stick");
	read(n), read(m), read(k);
	for(int i = 1; i <= n; ++i)
		read(p[i].a), read(p[i].b), p[i].b-=k;
	if(m == 0) {
		for(int i = 0; i <= 1000; ++i)
			for(int j = 1; j <= n; ++j)
				if(p[j].a <= i && i <= p[j].b)
					dp[i][(1<<(j-1))]=1;
		for(int j = 1; j < (1<<n); ++j) 
			for(int i = 0; i <= 1000; ++i)
				if(dp[i][j])
					for(int kk = 1; kk <= n; ++kk)
						if(!((j>>(kk-1))&1) && i+k >= p[kk].a && i+k <= p[kk].b)
							dp[i+k][j|(1<<(kk-1))]=1;
		int pd = 0;
		for(int i = 0; i <= 1000; ++i)
			pd|=dp[i][(1<<n)-1];
		if(pd)
			puts("Yes");
		else
			puts("No");
		return 0;
	}
	return 0;
}