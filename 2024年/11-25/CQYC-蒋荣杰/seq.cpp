#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N= 1e5+5;
int n, m, zhan[N], sum[N], tot, ppp[N], cnt, mx[N], pd[2005][2005][2], ans[N];
struct qwq {
	int i, k, op;
} lst[2005][2005][2], now;
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
	File("seq");
	scanf("%s\n%s", s+1, t+1);
	n=strlen(s+1), m=strlen(t+1);
	int st = (s[1]-'0'), stt = (t[1]-'0');
	for(int i = 1; i <= n; ++i) {
		int j = i;
		while(j+1 <= n && s[j+1] == s[i])
			++j;
		zhan[++tot]=j-i+1;
		sum[tot]=sum[tot-1]+zhan[tot];
		i=j;
	}
	pd[0][0][1]=1;
	// debug(tot, "???\n");
	for(int i = 1, j = st; i <= tot; ++i, j^=1) {
		for(int k = 0; k <= m; ++k) 
			if(pd[i-1][k][1])
				pd[i][k][0]=1, lst[i][k][0]=qwq {i-1, k, 1};//这一块不选
		for(int k = 1; k <= m; ++k) 
			if(t[k]-'0' == j) {
				if(pd[i-1][k-1][1]) {//最左边可不选
					pd[i][k][1]=1;
					lst[i][k][1]=qwq {i-1, k-1, 1};
					if(zhan[i] > 1)
						for(int op = 2; op <= zhan[i] && t[k+op-1]-'0' == j; ++op)
							pd[i][k+op-1][1]=1,
							lst[i][k+op-1][1]=qwq {i-1, k-1, 1};
				}
				else {
					if(pd[i-1][k-1][0]) {//最左边必须选
						if(zhan[i] == 1) {
							pd[i][k][1]=1;
							lst[i][k][1]=qwq {i-1, k-1, 0};
						}
						else {
							pd[i][k][0]=1;
							lst[i][k][0]=qwq {i-1, k-1, 0};
							if(zhan[i] > 1)
								for(int op = 2; op <= zhan[i] && t[k+op-1]-'0' == j; ++op)
									pd[i][k+op-1][1]=1, lst[i][k+op-1][1]=qwq {i-1, k-1, 0};
						}
					}
				}
			}
	}
	if(pd[tot][m][0] || pd[tot][m][1]) 
		puts("YES");
	else {
		puts("NO");
		return 0;
	}
	if(pd[tot][m][1])
		now=qwq {tot, m, 1};
	else
		now=qwq {tot, m, 0};
	while(1) {
		if(now.k == 0) break;
		qwq to = lst[now.i][now.k][now.op];
		if(!to.op || now.k-to.k == zhan[now.i]) 
			ans[++cnt]=sum[now.i-1]+1, --now.k;
		int opp = sum[now.i];
		while(now.k != to.k)
			ans[++cnt]=opp, --now.k, --opp;
		now=to;
	}
	sort(ans+1, ans+1+cnt);
	for(int i = 1; i <= cnt; ++i)
		write(ans[i], ' ');
	return 0;
}