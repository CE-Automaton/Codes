#include <stdio.h>
const int M = 998244353;
long long power(register long long a, register int b) {
	register long long ans = 1;
	while(b) {
		if(b & 1) ans = ans * a % M;
		a = a * a % M;
		b >>= 1;
	}
	return ans;
}
int main() {
	int n, m;
	freopen("breeze.in", "r", stdin);
	freopen("breeze.out", "w", stdout);
	scanf("%d%d", &n, &m);
	printf("%d", power(n + 1 << 1, m) * power(n + 1, M - 2) % M * (n - m + 1) % M);
	return 0;
}
