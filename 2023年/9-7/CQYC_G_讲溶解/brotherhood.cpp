#include <bits/stdc++.h>
using namespace std;
const int N = 15;
int n, q;
string f[N];
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
	freopen("brotherhood.in", "r", stdin);
	freopen("brotherhood.out", "w", stdout);
	read(n), read(q);
	f[1]="0";
	f[2]="1";
	for(int i = 3; i <= n; ++i)
		f[i]=f[i-1]+f[i-2];
//	cout<<f[n]<<"\n";
	for(int i = 1; i <= q; ++i) {
		scanf("%s", t);
		int len = strlen(t), ans = 0;
		for(int j = 0; j+len-1 < f[n].size(); ++j) {
			int pdd = 1;
			for(int o = 0; o <= len-1; ++o)
				if(f[n][j+o] != t[o]) {
					pdd=0;
					break;
				}
			ans+=pdd;
		}
		write(ans, '\n');
	}
	return 0;
}
