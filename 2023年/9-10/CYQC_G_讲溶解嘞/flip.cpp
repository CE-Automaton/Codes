#include <bits/stdc++.h>
#define mod 1000003
using namespace std;
const int N = 1e6+5;
int len, ln;
char s[N], t[4];

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
	freopen("flip.in", "r", stdin);
	freopen("flip.out", "w", stdout);
	scanf("%s\n%s", s+1, t+1);
	len=strlen(s+1);
	ln=strlen(t+1);
	if(ln == 1) {
		char lx = t[1];
		for(int i = 1; i <= len; ++i)
			if(s[i] == lx) {
				puts("-1");
				return 0;
			}
		puts("0");
		return 0;
	}
	puts("0");
	return 0;
}
