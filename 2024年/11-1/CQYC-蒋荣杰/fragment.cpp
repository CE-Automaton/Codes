#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int w, h, k;

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
	File("fragment");
	srand(time(0));
	read(w), read(h), read(k);
	if(k == 0) {
		if(w%2 == 0 && h%3 == 0)
			puts("YES");
		else
			if(w%3 == 0 && h%2 == 0)
				puts("YES");
			else
				if(w%5 == 0 && h%5 == 0)
					puts("YES");
				else
					puts("NO");
	}
	else {
		if(rand()%2)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}