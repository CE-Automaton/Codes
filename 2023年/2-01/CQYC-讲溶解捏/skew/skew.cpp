#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
const uLL base = 29;
uLL hs[30050], hsf[30050], bs[30050];
int n, typ, q, pd[5050][5050], sum[5050][5050], l, r, lasans;
char s[5050];
int main() {
	freopen("skew.in", "r", stdin);
	freopen("skew.out", "w", stdout);
	scanf("%d%d%s", &n, &typ, s+1);
	bs[0]=1;
	for(int i = 1; i <= n; ++i) 
		bs[i]=bs[i-1]*base, hs[i]=hs[i-1]*base+s[i]-'A'+1;
	for(int i = n; i >= 1; --i) 
		hsf[i]=hsf[i+1]*base+s[i]-'A'+1;
//	if(typ == 0 && n <= 30000) {
//		exit(0);
//	}
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; ++j) 
			if(hs[j]-hs[i-1]*bs[j-i+1] == hsf[i]-hsf[j+1]*bs[j-i+1])
				pd[i][j]=1;
	for(int i = n; i >= 1; --i)
		for(int j = i; j <= n; ++j)
			sum[i][j]=sum[i+1][j]+sum[i][j-1]-sum[i+1][j-1]+pd[i][j];
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i) {
		scanf("%d%d", &l, &r);
		if(typ) l^=lasans, r^=lasans;
		printf("%d\n", sum[l][r]);
		if(typ) lasans=sum[l][r];
	}
	return 0;
}
