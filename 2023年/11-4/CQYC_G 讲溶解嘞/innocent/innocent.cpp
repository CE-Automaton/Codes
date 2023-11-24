#include <bits/stdc++.h>
#define inf 1000000000000000000LL
using namespace std;
const int N = 1e3+5;
int n, m, u, v, w;
long long dis[N][N][2]/*ÅÜ×î¶ÌÂ·*/;

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
	freopen("innocent.in", "r", stdin);
	freopen("innocent.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i) 
		for(int j = i+1; j <= n; ++j)
			for(int o = 0; o <= 1; ++o)
				dis[i][j][o]=inf, dis[j][i][o]=inf; 
	for(int i = 1; i <= n; ++i) 
		dis[i][i][1]=inf;
	for(int i = 1; i <= m; ++i)
		read(u), read(v), read(w), ++u, ++v, 
		dis[u][v][(w+10000000)&1]=min(dis[u][v][(w+10000000)&1], 1LL*w);
	for(int k = 1; k <= n; ++k)
		for(int i = 1; i <= n; ++i)
			for(int o1 = 0; o1 <= 1; ++o1)
				for(int j = 1; j <= n; ++j)
					for(int o2 = 0; o2 <= 1; ++o2)
						dis[i][j][o1^o2]=min(dis[i][j][o1^o2], dis[i][k][o1]+dis[k][j][o2]);
	for(int i = 1; i <= n; ++i)
		if(dis[i][i][1] < 0) 
			puts("Twinkle");
		else
			if(dis[i][i][1] >= 1000000000000LL)
				puts("a-w-r-y");
			else
				write(dis[i][i][1], '\n');
	return 0;
}
