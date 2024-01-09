#include <bits/stdc++.h>
using namespace std;
const int N = 1e3+5;
int t, n, m, h[N][2], l[N][2], gsh[N], gsl[N];
char a[N][N], b[N][N];

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
	freopen("yue.in", "r", stdin);
	freopen("yue.out", "w", stdout);
	read(t);
	while(t--) {
		read(n), read(m);
		for(int i = 1; i <= n; ++i)
			scanf("%s", a[i]+1);
		for(int i = 1; i <= n; ++i)
			scanf("%s", b[i]+1);
		for(int i = 1; i <= n; ++i) 
			gsh[i]=0, h[i][0]=h[i][1]=0;
		for(int j = 1; j <= m; ++j)
			gsl[j]=0, l[j][0]=l[j][1]=0;
		int pd1 = 0, pd2 = 0, pd = 0, ans = 1; 
		for(int i = 1; i <= n; ++i) 
			for(int j = 1; j <= m; ++j)
				if(b[i][j] == '1')
					++gsh[i], ++gsl[j];
		for(int i = 1; i <= n; ++i) 
			if(gsh[i] == 1)
				for(int j = 1; j <= m; ++j)
					if(gsl[j] == 1)
						pd2|=1, h[i][1]=1, l[j][1]=1;
		for(int i = 1; i <= n; ++i) 
			if(gsh[i] == 0)
				pd1|=1, h[i][0]=1;
		for(int i = 1; i <= m; ++i) 
			if(gsl[i] == 0)
				pd1|=1, l[i][0]=1;
		for(int i = 1; i <= n; ++i) 
			for(int j = 1; j <= m; ++j)
				if((h[i][0] || h[i][1]) && (l[j][0] || l[j][1]) && a[i][j] == '0') 
					pd|=1;//pd表示A是否有一个位置是0使得能够操作得到B的一些行列 
		if(pd1) {
			if(pd2) {
				if(pd) {
					for(int i = 1; i <= n; ++i)
						for(int j = 1; j <= m; ++j) {
							if(h[i][0] || h[i][1] || l[j][0] || l[j][1])
								continue;
							if(a[i][j] != b[i][j])
								ans=0;
						}
				}
				else {
					for(int i = 1; i <= n; ++i)
						for(int j = 1; j <= m; ++j) 
							if(a[i][j] != b[i][j])
								ans=0;
				}
			}
			else {
				for(int i = 1; i <= n; ++i)
					for(int j = 1; j <= m; ++j) 
						if(a[i][j] != b[i][j])
							ans=0;
			}
		}
		else {
			if(pd2) {
				if(pd) {
					for(int i = 1; i <= n; ++i)
						for(int j = 1; j <= m; ++j) {
							if(h[i][0] || h[i][1] || l[j][0] || l[j][1])
								continue;
							if(a[i][j] != b[i][j])
								ans=0;
						}
				}
				else {
					for(int i = 1; i <= n; ++i)
						for(int j = 1; j <= m; ++j) 
							if(a[i][j] != b[i][j])
								ans=0;
				}
			}
			else {
				for(int i = 1; i <= n; ++i)
					for(int j = 1; j <= m; ++j) 
						if(a[i][j] != b[i][j])
							ans=0;
			}
		}
		if(ans)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}
