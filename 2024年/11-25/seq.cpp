#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, m, lst[2], f[N][2], ll[N][2][2], rr[N][2][2]/*右边选0/1能最远/近选到哪里*/, nb, nw, zhan[N], tot;
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
void check(int x) {
	if(f[nb][0] <= x && x <= f[nb][1] && s[x] == t[nb] && rr[x][t[nb+1]-'0'][0] <= nw && nw <= rr[x][t[nb+1]-'0'][1])
		zhan[++tot]=x, --nb, nw=x;
}

signed main() {
	File("seq");
	scanf("%s\n%s", s+1, t+1);
	n=strlen(s+1);
	m=strlen(t+1);
	lst[0]=lst[1]=n+1;
	for(int i = n; i >= 1; --i) {
		int j = i, now = s[i]-'0';
		while(j-1 >= 1 && s[j-1] == s[i])
			--j;
		ll[lst[now]][now][0]=i;
		rr[i][now][0]=lst[now];
		rr[i][now][1]=lst[now];
		rr[i][now^1][0]=i+1;
		rr[i][now^1][1]=lst[now]-1;
		for(int op = i-1; op >= j; --op)
			rr[op][now][0]=op+1, 
			rr[op][now][1]=i, 
			rr[op][now^1][0]=rr[op][now^1][1]=i+1;
		lst[now]=j;
		i=j;
	}
	if(s[1] != t[1])
		f[1][0]=f[1][1]=rr[1][(s[1]-'0')^1][0];
	else
		f[1][0]=1, f[1][1]=lst[(s[1]-'0')^1]-1;
	rr[n+1][0][1]=rr[n+1][1][1]=n+1;
	for(int i = 2; i <= m; ++i) {
		f[i][0]=rr[f[i-1][0]][t[i]-'0'][0];
		f[i][1]=rr[f[i-1][1]][t[i]-'0'][1];
		if(f[i][0] > f[i][1] || f[i][0] > n) {
			puts("NO");
			return 0;
		}
	}
	if(f[m][0] > n) {
		puts("NO");
		return 0;
	}
	int now = n;
	while(now > 1 && s[now-1] == s[n])
		--now;
	--now;
	if(f[m][1] < now) {
		puts("NO");
		return 0;
	}
	puts("YES");
	for(int j = f[m][0]; j <= f[m][1]; ++j)
		if(j >= now && s[j] == t[m])
			nw=j;
	nb=m-1;
	zhan[++tot]=nw;
	for(int i = nw-1; i >= 1; --i)
		check(i);
	sort(zhan+1, zhan+1+tot);
	for(int i = 1; i <= tot; ++i)
		write(zhan[i], ' ');
	return 0;
}