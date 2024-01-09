#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#define meow(args...) fprintf(stderr, args)
template<class T1, class T2> bool cmin(T1 &a, const T2 &b) {return b<a?(a=b, true):false;}
int F()
{
	register unsigned a=0;
	register unsigned char c;
	while((c=getchar()-48)>9);
	for(; c<=9; c=getchar()-48) a=a*10+c;
	return a;
}
int dis[21][21], pts[21][1<<20];
long long f[1<<21];
int main()
{
	register int n, m, q, i, j;
	freopen("acquire.in", "r", stdin);
	freopen("acquire.out", "w", stdout);
	n=F(), m=F();
	for(i=0; i<n; ++i)
		for(j=0; j<n; ++j)
			dis[i][j]=i==j?0:2147483647;
	for(i=0; i<m; ++i) {
		register int x=F()-1, y=F()-1;
		dis[x][y]=dis[y][x]=F();
	}
	for(i=0; i<n; ++i) {
		pts[i][0]=2147483647;
		for(j=1; j<1<<(n-1); ++j) {
			register int k=__builtin_ctz(j);
			pts[i][j]=std::min(pts[i][j&j-1], dis[i][k+(k>=i)]);
		}
	}
	memset(f, 127, sizeof(long long)<<n);
	for(i=1; i<1<<n; ++i) {
		if(__builtin_popcount(i)==1) {
			f[i]=0;
			continue;
		}
		for(j=i; j; j&=j-1) {
			register int k=__builtin_ctz(j);
			cmin(f[i], f[i^j&-j]+pts[k][i&(j&-j)-1|i>>k+1<<k]);
		}
	}
	for(i=1<<n; --i; ) for(j=i; j; j&=j-1) cmin(f[i^j&-j], f[i]);
	for(q=F(); q--; ) {
		for(i=F(), j=0; i--; j|=1<<F()-1);
		printf("%lld\n", f[j]);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
