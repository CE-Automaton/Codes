#include <bits/stdc++.h>

#define SZ(x) (int(x.size()))

using namespace std;
using i64 = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

char buf[(1<<21)+5],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)

inline int read() {
	int x = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return f ? -x : x;
}

const int N = 1e6 + 100;

int n, sa[N], h[N], rk[N], a[N]; char s[N];
signed main() {
	freopen("hush.in", "r", stdin);
	freopen("hush.out", "w", stdout);
	n = read();
	for (int i = 1; i <= n; ++i) sa[i] = read(), rk[sa[i]] = i;
	for (int i = 2; i <= n; ++i) { h[i] = read();
		if (rk[sa[i] + 1] < rk[sa[i - 1] + 1]) h[i] = 0;
		if (h[i] != -1) {
			int r = rk[sa[i] + h[i]];
			a[r] = max(a[r], rk[sa[i - 1] + h[i]]);
		}
	}
	for (int i = 1, p = 0, q = 0; i <= n; ++i) {
		if (!h[i]) p = i; if (h[i] == -1) q = i;
		if (p <= a[i]) h[p = q] = 0;
	}
	s[sa[1]] = 'a';
	for (int i = 2; i <= n; ++i) s[sa[i]] = s[sa[i - 1]] + (!h[i]);
	for (int i = 1; i <= n; ++i) putchar(s[i]);
	return 0;
}
