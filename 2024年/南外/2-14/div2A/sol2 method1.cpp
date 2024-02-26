// glacy (mad)
#include <bits/stdc++.h> 
using namespace std;

int n, c, x, N, a, s[100001], l, r, v[100001], p, C[100001];
void mod(int p) {
	while (p < n) {
		C[p]--;
		p += p & -p;
	}
}
int ask(int p) {
	int res = 0, sum = 0;
	for (int i = N; i >= 0; i--) {
		if (res + (1 << i) < n && C[res + (1 << i)] + sum < p) {
			res += (1 << i);
			sum += C[res];
		}
	}
	return res + 1;
}
int main() {
	freopen("tournament.in", "r", stdin);
	freopen("tournament.out", "w", stdout);
	scanf("%d%d%d", &n, &c, &x);
	N = 32 - __builtin_clz(n);
	for (int i = 1; i < n; i++) {
		scanf("%d", &a);
		s[i] = s[i - 1] + (a > x);
		C[i] = i & -i;
	}
	while (c--) {
		scanf("%d%d", &l, &r);
		int L = l ? ask(l) : 0, R = ask(r + 1) - 1;
		for (int i = l + 1; i <= r; i++) {
			mod(ask(l + 1));
		}
		if (s[L] == s[R]) {
			v[L]++;
			v[R + 1]--;
		}
	}
	for (int i = 1; i <= n; i++) {
		v[i] += v[i - 1];
		if (v[i] > v[p]) {
			p = i;
		}
	}
	printf("%d\n", p);
}
