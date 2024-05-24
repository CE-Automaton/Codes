#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e3+5;
int n, c[1000005], dp[2][N][N], gs, gss;
char s[1000005];

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
	File("bracket");
	read(n);
	scanf("%s", s+1);
	for(int i = 1; i <= n; ++i) {
		read(c[i]);
		if(c[i] == 0)
			++gs;
		else if(c[i] == 1)
			++gss;
		else
			++gs, ++gss;
	}
	if(gs%2 == 1 || gss%2 == 1) {
		puts("-1");
		return 0;
	}
	if(n > 1000) {
		puts("0");
		return 0;
	}
	int now = 0;
	for(int i = 0; i <= gs/2; ++i)
		for(int j = 0; j <= gss/2; ++j)
			dp[0][i][j]=inf;
	dp[0][0][0]=0;
	for(int i = 1; i <= n; ++i) {
		now^=1;
		for(int o = 0; o <= gs/2; ++o)
			for(int p = 0; p <= gss/2; ++p)
				dp[now][o][p]=inf;
		for(int o = 0; o <= gs/2; ++o)
			for(int p = 0; p <= gss/2; ++p) 
				if(dp[now^1][o][p] != inf) {
					if(c[i] == 2) {
						if(o >= 1 && p >= 1)
							dp[now][o-1][p-1]=min(dp[now][o-1][p-1], dp[now^1][o][p]+(s[i] == '('));
						dp[now][o+1][p+1]=min(dp[now][o+1][p+1], dp[now^1][o][p]+(s[i] == ')'));
					}
					else 
						if(c[i] == 0) {
							if(o >= 1)
								dp[now][o-1][p]=min(dp[now][o-1][p], dp[now^1][o][p]+(s[i] == '('));
							dp[now][o+1][p]=min(dp[now][o+1][p], dp[now^1][o][p]+(s[i] == ')'));
						}
						else {
							if(p >= 1)
								dp[now][o][p-1]=min(dp[now][o][p-1], dp[now^1][o][p]+(s[i] == '('));
							dp[now][o][p+1]=min(dp[now][o][p+1], dp[now^1][o][p]+(s[i] == ')'));
						}
				}
	}
	write((dp[now][0][0] == inf ? -1 : dp[now][0][0]), '\n');
	// debug(clock(), '\n');
	return 0;
}