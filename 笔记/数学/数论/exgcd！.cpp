//exgcd!!! 
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int x, y, a, b, c;

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
int exgcd(int u, int v, int& xx, int& yy) {
	int ret = 0;
	if(u%v == 0) xx=0, yy=1, ret=v;
	else ret=exgcd(v, u%v, yy, xx), yy-=u/v*xx;
	return ret;
}

signed main() {
	read(a), read(b), read(c);
	int d = exgcd(a, b, x, y);
	if(c%d) 
		puts("-1");
	else
		write(x*c/d, ' '), write(y*c/d, '\n');
	return 0;
}
