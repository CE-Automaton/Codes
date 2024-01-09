#include <bits/stdc++.h>
using namespace std;
const int N = 2e6+5;
int n, m, opt, l, r;
char s[N], a[2], b[2];

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
	freopen("dog.in", "r", stdin);
	freopen("dog.out", "w", stdout);
	scanf("%s", s+1);
	n=strlen(s+1);
	read(m);
	for(int i = 1; i <= m; ++i) {
		read(opt), read(l), read(r);
		if(opt == 1) {
			int mx = 0;
			for(int j = l; j+1 <= r; ++j) {
				if(s[j] == s[j+1]) {
					if(mx == 0)
						mx=1, b[0]=s[j];
					else
						if(mx == 1)
							b[0]=min(b[0], s[j]);
					continue;
				}
				char c[2];
				c[0]=s[j];
				c[1]=s[j+1];
				int k = j+1, now = 0;
				while(k+1 <= r && s[j+now] == s[k+1])
					++k, now^=1;
				if(mx < k-j+1) {
					mx=k-j+1;
					b[0]=s[j];
					b[1]=s[j+1];
				}
				else
					if(mx == k-j+1) 
						if(b[0] > s[j] || (b[0] == s[j] && b[1] > s[j+1]))
							b[0]=s[j], b[1]=s[j+1];
				j=k-1;
			}
			write(mx, ' ');
			putchar(b[0]);
			if(mx >= 2)
				putchar(b[1]);
			putchar('\n');
		}
		if(opt == 2) {
			scanf(" %c", &a[0]);
			for(int j = l; j <= r; ++j)
				s[j]=a[0];
		}
		if(opt == 3) {
			r=l+r-1;
			scanf("%s", a);
			for(int j = l, now = 0; j <= r; ++j)
				s[j]=a[now], now^=1;
		}
	}
	return 0;
}
