#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5, K = 1e2+5;
int n, k, c[K], sum[N][5], f[N][K], g[N][K], xx[N], yy[N];
char b[N];

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
	File("pro");
	scanf("%s", b+1), n=strlen(b+1);
	read(k);
	for(int i = 1; i <= k; ++i) 
		read(c[i]);
	for(int i = 1; i <= n; ++i)
		sum[i][1]=sum[i-1][1]+(b[i] == '_'), 
		sum[i][2]=sum[i-1][2]+(b[i] == 'X'), 
		sum[i][3]=sum[i-1][3]+(b[i] == '.');
	f[0][0]=1;
	for(int i = 1; i <= n; ++i) {
		if(b[i] == '.' || b[i] == '_')
			for(int j = 0; j <= k; ++j)
				f[i][j]|=f[i-1][j];//为'_'的情况
		if(b[i] == '.' || b[i] == 'X') {
			for(int j = 1; j < k; ++j)//为'X'的情况
				if(f[i-1][j-1] && i+c[j] <= n && sum[i+c[j]-1][1]-sum[i-1][1] == 0/*中间没有必填'_'的*/ 
				&& (b[i+c[j]] == '.' || b[i+c[j]] == '_')/*后面必须接一个'_'*/) 
					f[i+c[j]][j]=1;
			if(f[i-1][k-1] && i+c[k]-1 <= n && sum[i+c[k]-1][1]-sum[i-1][1] == 0/*中间没有必填'_'的*/) 
				f[i+c[k]-1][k]=1;
		}
	}
	g[n+1][k+1]=1;
	for(int i = n; i >= 1; --i) {
		if(b[i] == '.' || b[i] == '_')
			for(int j = 1; j <= k+1; ++j)
				g[i][j]|=g[i+1][j];//为'_'的情况
		if(b[i] == '.' || b[i] == 'X') {
			for(int j = k; j >= 2; --j)//为'X'的情况
				if(g[i+1][j+1] && i-c[j] >= 1 && sum[i][1]-sum[i-c[j]][1] == 0/*中间没有必填'_'的*/ 
				&& (b[i-c[j]] == '.' || b[i-c[j]] == '_')/*后面必须接一个'_'*/) 
					g[i-c[j]][j]=1;
			if(g[i+1][2] && i-c[1]+1 >= 1 && sum[i][1]-sum[i-c[1]][1] == 0/*中间没有必填'_'的*/ ) 
				g[i-c[1]+1][1]=1;
		}
	}
	for(int i = 1; i <= n; ++i) {
		if(b[i] == '.' || b[i] == '_') {//为'_'的情况
			for(int j = 1; j < k; ++j)
				if(f[i][j] && (g[i][j+1]))
					yy[i]=1;
			if(f[i][0] && g[i+1][1])
				yy[i]=1;
			if(f[i-1][k] && g[i][k+1])
				yy[i]=1;
		}
		if(b[i] == '.' || b[i] == 'X') {
			//为'X'的情况
			for(int j = 1; j < k; ++j)
				if(f[i-1][j-1] && i+c[j] <= n && sum[i+c[j]-1][1]-sum[i-1][1] == 0/*中间没有必填'_'的*/ 
				&& (b[i+c[j]] == '.' || b[i+c[j]] == '_') && g[i+c[j]][j+1]) 
					++xx[i], --xx[i+c[j]];
			if(f[i-1][k-1] && i+c[k]-1 <= n  && sum[i+c[k]-1][1]-sum[i-1][1] == 0/*中间没有必填'_'的*/
			&& g[i+c[k]][k+1]) 
				++xx[i], --xx[i+c[k]];
		}
		xx[i]+=xx[i-1];
	}
	// for(int i = 0; i <= n+1; ++i) 
	// 	for(int j = 0; j <= k+1; ++j)
	// 		debug(i, j, "f:", f[i][j], "g:", g[i][j], '\n');
	for(int i = 1; i <= n; ++i)
		if(xx[i] && yy[i])
			putchar('?');
		else if(xx[i])
			putchar('X');
		else if(yy[i])
			putchar('_');
		else
			debug(i, "!?\n");
	putchar('\n');
	return 0;
}