#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
const uLL base1 = 29, base2 = 31;
int T, n, m, x, y, ans;
uLL hs[1005][1005], ht[1005][1005], bs1[1005], bs2[1005];
char s[1005][1005], t[105][105];
int main() {
	scanf("%d", &T);
	bs1[0]=bs2[0]=1;
	for(int i = 1; i <= 1000; ++i)
		bs1[i]=bs1[i-1]*base1, bs2[i]=bs2[i-1]*base2;
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			scanf("%s", s[i]+1);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				hs[i][j]=hs[i][j-1]*base2+s[i][j]-'a'+1;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				hs[i][j]+=hs[i-1][j]*base1;
		scanf("%d%d", &x, &y);
		for(int i = 1; i <= x; ++i)
			scanf("%s", t[i]+1);
		for(int i = 1; i <= x; ++i)
			for(int j = 1; j <= y; ++j)
				ht[i][j]=ht[i][j-1]*base2+t[i][j]-'a'+1;
		for(int i = 1; i <= x; ++i)
			for(int j = 1; j <= y; ++j)
				ht[i][j]+=ht[i-1][j]*base1;
		ans=0;
		for(int i = 1, k = x; k <= n; ++k, ++i)
			for(int j = 1, l = y; l <= m; ++l, ++j)
				if(hs[k][l]-hs[i-1][l]*bs1[x]-hs[k][j-1]*bs2[y]+hs[i-1][j-1]*bs1[x]*bs2[y] == ht[x][y])
					++ans;
		printf("%d\n", ans);
	}
	return 0;
}
