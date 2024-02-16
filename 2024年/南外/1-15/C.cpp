#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 195, M = 5e6+5;
int n, m, b[N][N], pw[18], f[M], g[M], ans;
char a[N][N];

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
	File("daredevil");
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		scanf("%s", a[i]+1);
	if(n < m) {
		for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j)
			b[j][i]=a[i][j]-'0';
		swap(n, m);
	}
	else
		for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j)
			b[i][j]=a[i][j]-'0';
	pw[0]=1;
	for(int i = 1; i <= 16; ++i)
		pw[i]=pw[i-1]*3;
	for(int i = 0; i <= pw[m+1]-1; ++i)
		f[i]=inf;
	f[0]=0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			for(int k = 0; k <= pw[m+1]-1; ++k)
				g[k]=inf;
			for(int k = 0; k <= pw[m+1]-1; ++k) 
                if(f[k] != inf) {
                    int x = k/pw[j]%3, y = k%3;
                    if(b[i][j] != 1) {
                        if(!x && !y) 
                            g[k+pw[j]]=min(g[k+pw[j]], f[k]), g[k+1]=min(g[k+1], f[k]);
                        else
                            g[k]=min(g[k], f[k]);
                        g[k-x*pw[j]+pw[j]*2-y+2]=min(g[k-x*pw[j]+pw[j]*2-y+2], f[k]+1);
                    }
                    if(b[i][j] != 0 && x != 1 && y != 1)
                        g[k-x*pw[j]-y]=min(g[k-x*pw[j]-y], f[k]);
                }
			for(int k = 0; k <= pw[m+1]-1; ++k)
				f[k]=g[k];
		}
		for(int k = 0; k <= pw[m+1]-1; k+=3)
			f[k]=min(f[k], f[k+2]), f[k+1]=f[k+2]=inf;
	}
	ans=inf;
	for(int k = 0; k <= pw[m+1]-1; k+=3) {
		int pd = 1;
		for(int j = 1; j <= m; ++j) 
			if(k/pw[j]%3 == 1) {
				pd=0;
				break;
			}
		if(pd)
			ans=min(ans, f[k]);
	}
	write(ans, '\n');
	return 0;
}