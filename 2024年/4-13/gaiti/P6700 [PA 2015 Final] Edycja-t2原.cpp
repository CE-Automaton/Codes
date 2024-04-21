#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, c, gs[28], gss[28][28], to[28][28], az[28], dp[29][(1<<14)+5][2], cnt, bl[28], in[28], ans;
char s[N], t[N];
vector <int> tt[28];
queue <int> q;

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
void mnn(int &x, int y) { x=min(x, y); }

signed main() {
	read(n), read(c);
	scanf("%s\n%s", s+1, t+1);
	for(int i = 1; i <= n; ++i)
		++gs[s[i]-'a'+1], ++gss[s[i]-'a'+1][t[i]-'a'+1];
	for(int i = 1; i <= 26; ++i) {
		int o = 0;
		to[i][0]=0x3f3f3f3f;
		for(int j = 1; j <= 26; ++j)
			to[i][j]=(i == j ? 0 : c)+gs[i]-gss[i][j], 
			o=(to[i][j] > to[i][o] ? o : j);
		az[i]=o;
		++in[az[i]];
	}
	// debug(ans, "???\n");
	int pd = 0;
	for(int i = 1; i <= 26; ++i)
		if(!in[i])
			q.push(i), pd=1;
	while(!q.empty()) {
		int it = q.front(); q.pop();
		--in[az[it]];
		if(!in[az[it]])
			q.push(az[it]);
	}
	for(int i = 1; i <= 26; ++i)
		if(in[i] && az[i] != i) {
			int now = i;
			++cnt;
			do {
				bl[now]=cnt;
				in[now]=0;
				now=az[now];
			} while(now != i);
		}
	if(cnt == 0) {
		for(int i = 1; i <= 26; ++i)
			ans+=to[i][az[i]];
		write(ans, '\n');
		return 0;
	}
	for(int i = 1; i <= 26; ++i) 
		debug(i, ":", az[i], bl[i], '\n');
	memset(dp, 0x3f, sizeof dp);
	debug(dp[0][0][0], cnt, pd, "???\n");
	dp[1][0][0]=0;
	for(int i = 1; i <= 26; ++i)
		for(int j = 0; j < (1<<cnt); ++j)
			for(int k = 0; k <= 1; ++k) 
				for(int o = 1; o <= 26; ++o) {
					int nxt = j;
					if(bl[i] && az[i] != o)
						nxt|=(1<<(bl[i]-1));
					if(bl[o] && (bl[o] != bl[i] || az[i] != o)) 
						nxt|=(1<<(bl[o]-1));
					mnn(dp[i+1][nxt][k|(az[i] != o)], dp[i][j][k]+to[i][o]);
				}
	int st = 0x3f3f3f3f;
	for(int i = 0; i < (1<<(cnt)); ++i)
		st=min(st, (pd ? min(dp[27][i][1], dp[27][i][0]) : dp[27][i][1])+c*(cnt-__builtin_popcount(i))), 
		debug(dp[27][i][0], dp[27][i][1], i, __builtin_popcount(i), "\n");
	write(st, '\n');
	return 0;
}