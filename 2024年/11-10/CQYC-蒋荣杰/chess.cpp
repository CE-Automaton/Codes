#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 15;
int t, n, m, ans[N][N][N], xx[N][N][N], yy[N][N][N];
char fx[N][N][N];

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
	File("chess");
	read(t);
	while(t--) {
		read(n), read(m);
		if(n == 1 && m == 1) {
			puts("0");
			continue;
		}
		if(n == 1 && m == 2) {
			puts("1");
			puts("2 2 R");
			continue;
		}
		if(n == 1 && m == 3) {
			puts("1");
			puts("2 3 L");
			continue;
		}
		if(n == 1 && m == 4) {
			puts("2");
			puts("2 3 L");
			puts("2 4 R");
			continue;
		}
		if(n == 2 && m == 1) {
			puts("1");
			puts("2 2 D");
			continue;
		}
		if(n == 2 && m == 2) {
			puts("3");
			puts("2 2 D");
			puts("2 3 D");
			puts("4 3 L");
			continue;
		}
		if(n == 2 && m == 3) {
			puts("4");
			puts("3 2 U");
			puts("3 3 U");
			puts("3 4 U");
			puts("1 3 L");
			continue;
		}
		if(n == 2 && m == 4) {
			puts("7");
			puts("3 2 U");
			puts("3 3 U");
			puts("1 2 R");
			puts("3 5 U");
			puts("1 5 L");
			puts("3 4 U");
			puts("1 3 R");
			continue;
		}
		if(n == 3 && m == 1) {
			puts("1");
			puts("3 2 U");
			continue;
		}
		if(n == 3 && m == 2) {
			puts("4");
			puts("3 2 U");
			puts("3 3 U");
			puts("1 3 L");
			puts("4 3 L");
			continue;
		}
		if(n == 3 && m == 3) {
			puts("6");
			puts("2 3 L");
			puts("4 3 U");
			puts("2 4 L");
			puts("2 1 R");
			puts("3 2 D");
			puts("3 4 D");
			continue;
		}
		if(n == 3 && m == 4) {
			puts("8");
			puts("2 3 L");
			puts("4 3 U");
			puts("2 4 L");
			puts("2 1 R");
			puts("3 2 D");
			puts("3 4 D");
			puts("3 5 D");
			puts("5 4 R");
			continue;
		}
		if(n == 4 && m == 1) {
			puts("2");
			puts("3 2 U");
			puts("4 2 D");
			continue;
		}
		if(n == 4 && m == 2) {
			puts("7");
			puts("2 3 L");
			puts("3 3 L");
			puts("2 1 D");
			puts("5 3 L");
			puts("5 1 U");
			puts("4 3 L");
			puts("3 1 D");
			continue;
		}
		if(n == 4 && m == 3) {
			puts("8");
			puts("2 3 L");
			puts("4 3 U");
			puts("2 4 L");
			puts("2 1 R");
			puts("3 2 D");
			puts("3 4 D");
			puts("3 5 D");
			puts("5 4 R");
			continue;
		}
		if(n == 4 && m == 3) {
			puts("11");
			puts("2 3 L");
			puts("4 3 U");
			puts("2 4 L");
			puts("2 1 R");
			puts("3 2 D");
			puts("3 4 D");
			puts("2 3 L");
			puts("4 3 U");
			puts("2 4 L");
			puts("2 1 R");
			puts("3 2 D");
			continue;
		}
	}
	return 0;
}