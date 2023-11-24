#include <bits/stdc++.h>
using namespace std;
int t, k, n, a[5], zhan[5], tot;

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
	freopen("device.in", "r", stdin);
	freopen("device.out", "w", stdout);
	read(t);
	while(t--) {
		read(k), read(n);
		if(n == 0) {
			putchar('1'), putchar('\n');
			continue;
		}
		a[1]=k%10, a[2]=k/10%10, a[3]=k/100;
		sort(a+1, a+1+3);
		tot=0;
		int gs = 0;
		for(int i = 1; i <= 3; ++i) {
			if(i != 1 && a[i] != a[i-1])
				zhan[++tot]=gs, gs=0;
			++gs;
		}
		zhan[++tot]=gs;
		if(tot == 1) 
			putchar('1'), putchar('\n');
		else 
			if(tot == 2) {
				if(n == 1)
					putchar('7'), putchar('\n');
				else
					putchar('8'), putchar('\n');
			}
			else {
				if(n == 1)
					putchar('2'), putchar('4'), putchar('\n');
				else
					putchar('2'), putchar('7'), putchar('\n');
			}
	}
	return 0;
}
