#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, k, now[N], to[N], gs[N][2], gss[N][2];
LL ans;
char s[N];

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
	File("mind");
	read(n), read(k);
	scanf("%s", s+1);
	for(int i = 0; i < n*k; ++i)
		now[i+1]=(s[i%n] == 'L' ? 0 : 1);
	int pd = 1;
	while(pd && ans <= 1000000000000000000LL) {
		pd=0;
		for(int i = n*k; i >= 1; --i)
			gss[i][0]=gss[i+1][0], gss[i][1]=gss[i+1][1], 
			++gss[i][now[i]];
		for(int i = 1; i <= n*k; ++i)
			gs[i][0]=gs[i-1][0], gs[i][1]=gs[i-1][1], 
			++gs[i][now[i]];
		for(int i = 1; i <= n*k; ++i) {
			to[i]=now[i];
			if(now[i] && gss[i+1][0] > gss[i+1][1]) 
				to[i]^=1;
			else
				if(!now[i] && gs[i-1][1] > gs[i-1][0])
					to[i]^=1;
			ans+=(to[i] != now[i]);
			pd|=(to[i] != now[i]);
			now[i]=to[i];
		}
		// debug(ans, "???\n");
	}
	if(ans > 1000000000000000000LL)
		puts("-1");
	else
		write(ans, '\n');
	return 0;
}
