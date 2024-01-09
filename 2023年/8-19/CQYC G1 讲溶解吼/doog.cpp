#include <bits/stdc++.h>
using namespace std;
const int N = 5e3+5;
int n, q, tot, dp[1005][1005];
char s[N], zhan[N];
struct qwq {
	int opt, l, r;
}que[500005];

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
	freopen("doog.in", "r", stdin);
	freopen("doog.out", "w", stdout);
	read(n), read(q);
	scanf("%s", s+1);
	int pd = 1;
	for(int i = 1; i <= q; ++i)
		read(que[i].opt), pd&=(que[i].opt == 2), read(que[i].l), read(que[i].r);
	if(pd && n <= 1000 && q <= 500000) {
//		puts("!!!");
		for(int i = 1; i <= n; ++i) {
			tot=0;
			for(int j = i; j <= n; ++j) {
				if(tot && zhan[tot] == s[j])
					--tot;
				else
					zhan[++tot]=s[j];
				if(tot == 0)
					dp[i][j]=1;
			} 
		}
		for(int i = 1; i <= q; ++i)
			puts(dp[que[i].l][que[i].r] ? "YES" : "NO");
	}
	else {
		for(int i = 1; i <= q; ++i) {
			if(que[i].opt == 1) 
				for(int j = que[i].l; j <= que[i].r; ++j)
					s[j]=(s[j]-'0')%3+1+'0';
			else {
				tot=0;
				for(int j = que[i].l; j <= que[i].r; ++j) {
					if(tot && zhan[tot] == s[j])
						--tot;
					else
						zhan[++tot]=s[j];
				} 
				if(tot == 0)
					puts("YES");
				else
					puts("NO");
			}
		}
	}
	return 0;
}
