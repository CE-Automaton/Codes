#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 10005;
int n, xx[N], yy[N], dis[N], mx, mxs;

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
int qwq(int x) {
	return (x < 0 ? -x : x);
}

signed main() {
	freopen("synd.in", "r", stdin);
	freopen("synd.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) 
		read(xx[i]), read(yy[i]);
	for(int i = 1; i <= n; ++i)
		for(int j = i+1; j <= n; ++j)
			if(i != j) {
				int ww = qwq((xx[i]-xx[j])*(yy[i]-yy[j]));
				dis[i]+=ww, dis[j]+=ww;
			}
	mxs=1000000000000000000LL;
	for(int i = 1; i <= n; ++i) 
		if(dis[i] < mxs)
			mx=i, mxs=dis[i];
	write(xx[mx], ' '), write(yy[mx], ' ');
	return 0; 
}
