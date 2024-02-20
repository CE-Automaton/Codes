#include <bits/stdc++.h>
using namespace std;

#define mod 1000000007

struct mint {
	long long a;
	mint(long long a=0) {
		this->a = a % mod;
	}
	mint operator-(mint x) {
		return mint(mod + a - x.a);
	}
	mint operator*(mint x) {
		return mint(a * x.a);
	}
	mint operator+(mint x) {
		return mint(a + x.a);
	}
};

struct matrix {
	mint a, b, c, d, e, f, g, h, i;
	matrix(mint a, mint b, mint c, mint d, mint e, mint f, mint g, mint h, mint i) {
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->e = e;
		this->f = f;
		this->g = g;
		this->h = h;
		this->i = i;
	}
	matrix operator-(matrix x) {
		return matrix{a - x.a, b - x.b, c - x.c, d - x.d, e - x.e, f - x.f, g - x.g, h - x.h, i - x.i};
	}
	matrix operator*(matrix x) {
		return matrix{a * x.a + d * x.b + g * x.c, b * x.a + e * x.b + h * x.c, c * x.a + f * x.b + i * x.c, a * x.d + d * x.e + g * x.f, b * x.d + e * x.e + h * x.f, c * x.d + f * x.e + i * x.f, a * x.g + d * x.h + g * x.i, b * x.g + e * x.h + h * x.i, c * x.g + f * x.h + i * x.i};
	}
} F(4, mod - 2, 1, 1, 0, 0, 0, 1, 0), L(0, 0, 0, 1, 0, 0, 3, 0, 0), R(1, 0, 0, 0, 0, 0, 0, 0, 0), G(0, 1, 0, 0, 0, 1, 1, mod - 4, 2), I(1, 0, 0, 0, 1, 0, 0, 0, 1), ans = I;

matrix qpow(matrix b, int e) {
	return e ? e & 1 ? qpow(b * b, e >> 1) * b : qpow(b * b, e >> 1) : I;
}

int n, m, a;
int main() {
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &a);
		ans = ans * (I - qpow(F, a) * R * L * qpow(G, a));
	}
	printf("%lld\n", (L * ans * qpow(F, n) * R).a.a);
}
