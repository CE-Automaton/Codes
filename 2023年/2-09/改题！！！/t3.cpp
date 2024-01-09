#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, x, ans[205], tot, pd, m;
const int Mt=1e5;
inline char getc(){
	static char buf[Mt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mt,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int r=0,f=1;char c=getc();
	while(!isdigit(c)){if(c=='-')f=-1;c=getc();}
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getc();
	return r*f;
}
int len;
char put[78];
inline void write(int x) {
	do {put[++len]=x%10, x/=10;}while(x);
	while(len) putchar(put[len--]^48); putchar(' ');
}
signed main() {
	freopen("original.in", "r", stdin);
	freopen("original.out", "w", stdout);
	n = read(), m= read(), x=n;
	if(n <= 100000000000000LL) pd=1;
	for(int i = 2; i <= 10000000LL && i*i <= n; ++i)
		if(n%i == 0) {
			m=m/(i-1)*i;
			while(n%i == 0) ans[++tot]=i, n/=i;
		}
	if(pd) {
		if(n != 1) ans[++tot]=n;
		for(int i = 1; i <= tot; ++i) write(ans[i]), putchar('\n');
		return 0;
	}
	m=(__int128) n*m/x;
//	write(n), write(m), putchar('\n');
	if(n == m+1)
		ans[++tot]=n, n=1, m=1;
	if(n != 1) {
		int v = 1LL*sqrt(n), u = n-m+1;
		if(v*v == n) ans[++tot]=v, ans[++tot]=v;
		else {
			int qwq = sqrt(u*u-4*n);
			v = (u-qwq)/2;
			ans[++tot]=v;
			v = (u+qwq)/2;
			ans[++tot]=v;
		}
	}
	for(int i = 1; i <= tot; ++i) write(ans[i]), putchar('\n');
	return 0;
}
