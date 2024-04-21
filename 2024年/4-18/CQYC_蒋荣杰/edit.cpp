#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5, base = 131, mod = 1000000007;
int n, m, pd[N], pp[28]/*0表示可删，1表示必须留，2表示必须删*/, st[28], fn[28], now, tot, zhan[N], bs[N];
LL dp[2][N], w[N], sss[N], sum[N];
char s[N], t[N];

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
	File("edit");
	scanf("%s\n%s", s+1, t+1);
	n=strlen(s+1), m=strlen(t+1);
	for(int i = 1; i <= n; ++i) 
		read(w[i]);
	for(int i = 1; i <= m; ++i) {
		if(st[t[i]-'a'+1] == 0)
			st[t[i]-'a'+1]=i;
		fn[t[i]-'a'+1]=i;
	}
	for(int i = 1; i <= 26; ++i)
		pd[st[i]]=1, pd[fn[i]]=1, pp[i]=2;
	bs[0]=1;
	for(int i = 1; i <= n; ++i) 
		dp[0][i]=inf, bs[i]=1LL*bs[i-1]*base%mod;
	int now = 0;
	for(int l = 1; l <= m; ++l) {
		int r = l;
		while(r+1 <= m && !pd[r]) ++r;
		if(r == m && !pd[r]) break;
		now^=1;
		for(int i = 0; i <= n; ++i) 
			dp[now][i]=inf, sum[i]=0;
		tot=0;
		int ln = r-l, ht = 0;
		for(int o = l; o < r; ++o)
			ht=(1LL*ht*base%mod+t[o]-'a'+1)%mod;
		LL mn = dp[now^1][0];
		if(r == st[t[r]-'a'+1]) {//第一次出现
			pp[t[r]-'a'+1]=0;
			for(int i = 1; i <= n; ++i) {
				sum[i]=sum[i-1];
				if(s[i] == t[r] && (ln == 0 || (tot >= ln && (zhan[tot]-1LL*zhan[tot-ln]*bs[ln]%mod+mod)%mod == ht))) 
					dp[now][i]=min(dp[now][i], (ln == 0 ? mn : sss[tot-ln+1])+sum[i]);
				if(pp[s[i]-'a'+1] == 1) {
					++tot, zhan[tot]=(1LL*zhan[tot-1]*base%mod+s[i]-'a'+1)%mod;
					sss[tot]=mn;
					mn=dp[now^1][i]-sum[i];
				}
				else
					sum[i]+=w[i];
				mn=min(mn, dp[now^1][i]-sum[i]);
			}
			pp[t[r]-'a'+1]=1;//后面必须保留
			if(r == fn[t[r]-'a'+1])
				pp[t[r]-'a'+1]=2;//如果后面没有了后面就必须删除
		}
		else {//是最后一次出现
			// debug(r, "?????\n");
			for(int i = 1; i <= n; ++i) {
				sum[i]=sum[i-1];
				if(s[i] == t[r] && (ln == 0 || (tot >= ln && (zhan[tot]-1LL*zhan[tot-ln]*bs[ln]%mod+mod)%mod == ht))) 
					dp[now][i]=min(dp[now][i], (ln == 0 ? mn : sss[tot-ln+1])+sum[i]);
				if(pp[s[i]-'a'+1] == 1) {
					// debug(s[i]), debug(' ');
					++tot, zhan[tot]=(1LL*zhan[tot-1]*base%mod+s[i]-'a'+1)%mod;
					sss[tot]=mn;
					mn=dp[now^1][i]-sum[i];
				}
				else
					sum[i]+=w[i];
				mn=min(mn, dp[now^1][i]-sum[i]);
			}
			// debug('\n');
			pp[t[r]-'a'+1]=2;//后面必须删
		}
		l=r;
		// for(int i = 1; i <= n; ++i) 
		// 	debug(dp[now][i]), debug(' ');
		// debug('\n');
	}
	now^=1;
	for(int i = 0; i <= n; ++i) 
		dp[now][i]=inf, sum[i]=0;
	LL mn = dp[now^1][0];
	for(int i = 1; i <= n; ++i)
		sum[i]=sum[i-1]+w[i], mn=min(mn, dp[now^1][i]-sum[i]), dp[now][i]=min(dp[now][i], mn+sum[i]);
	// for(int i = 1; i <= n; ++i) 
	// 	debug(dp[now][i]), debug(' ');
	// debug('\n');
	write((dp[now][n] > 200000000000000LL ? -1 : dp[now][n]), '\n');
	return 0;
}