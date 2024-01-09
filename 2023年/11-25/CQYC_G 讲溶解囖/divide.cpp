#include <bits/stdc++.h>
using namespace std;
int t, m, n;

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
	freopen("divide.in", "r", stdin);
	freopen("divide.out", "w", stdout);
	read(t);
	while(t--) {
		read(n), read(m);
		if(n == 1) {
			puts("-1");
			continue;
		}
		if(n == 2) {
			if(m%2 == 0) {
				write(m/2, ' '), 
				write(m/2, '\n');
				continue;
			}
		}
		puts("-1");
	}
	return 0;
}
