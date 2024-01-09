#include <cstdio>

typedef long long LL;
const int Mod = 998244353;
const int MN = 250005;

int N, M, b[MN];

int main() {
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	scanf("%d%d", &N, &M);
	int lst = 0, mxv = 0;
	for (int i = 1; i <= M; ++i) {
		int x;
		scanf("%d", &x);
		if (x > lst) {
			b[x] = i;
			lst = x;
			mxv = x;
		} else {
			b[x] = -1;
			lst = N;
		}
	}
	int Ans = 1, V = 0;
	for (int i = 1; i <= N; ++i) {
		if (!b[i]) Ans = (LL)Ans * V % Mod, ++V;
		else if (b[i] != -1) V += 1 + (i == mxv);
	}
	printf("%d\n", Ans);
	return 0;
}
