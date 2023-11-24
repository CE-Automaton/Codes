#include <bits/stdc++.h>
#define uLL unsigned long long
using namespace std;
const int N = 5e5+5;
const uLL base = 31;
int tt;
uLL hs[N], bs[N], fhs[N];
char t[N];

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
	freopen("short.in", "r", stdin);
	freopen("short.out", "w", stdout);
	read(tt);
	bs[0]=1;
	for(int i = 1; i <= 300000; ++i)
		bs[i]=bs[i-1]*base;
	while(tt--) {
		scanf("%s", t+1);
		int n = strlen(t+1);
		for(int i = 0; i <= n+1; ++i)
			hs[i]=fhs[i]=0;
		for(int i = 1; i <= n; ++i)
			hs[i]=hs[i-1]*base+t[i]-'a'+1;
		for(int i = n; i >= 1; --i)
			fhs[i]=fhs[i+1]*base+t[i]-'a'+1;
		while(n%2 == 0) {
			int mid = n/2;
			if(hs[mid] != fhs[mid+1]-fhs[n+1]*bs[mid])
				break;
			n=n/2;
		}
		for(int i = 1; i <= n; ++i)
			putchar(t[i]);
		putchar('\n');
	}
	return 0;
}
