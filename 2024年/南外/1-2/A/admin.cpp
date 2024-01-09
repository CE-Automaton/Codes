#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int Mod = 1000000007;
int fpow(int a, int b)
{
	int ans = 1, t = a;
	while (b)
	{
		if (b & 1) ans = 1ll * ans * t % Mod;
		t = 1ll * t * t % Mod;
		b >>= 1;
	}
	return ans;
}
int inv(int x)
{
	return fpow(x, Mod - 2);
}

struct Poly{
	int a[10], n;
	Poly(int x = 0){
		n = 0;
		memset(a, 0, sizeof(a));
		a[0] = x;
	}
	Poly(int x, int y)
	{
		memset(a, 0, sizeof(a));
		n = 1;
		a[0] = y;
		a[1] = x;
	}
	int calc(int x)
	{
		int ans = 0;
		for (int i = n; i >= 0; i--)
			ans = (1ll * ans * x + a[i]) % Mod;
		return ans;
	}
};
Poly operator + (const Poly& a, const Poly& b)
{
	Poly ans;
	ans.n = max(a.n, b.n);
	for (int i = 0; i <= ans.n; i++)
	{
		ans.a[i] = 0;
		if (i <= a.n) ans.a[i] = (ans.a[i] + a.a[i]) % Mod;
		if (i <= b.n) ans.a[i] = (ans.a[i] + b.a[i]) % Mod;
		if (ans.a[i] >= Mod) ans.a[i] -= Mod;
	}
	return ans;
}
Poly operator * (const Poly& a, const Poly& b)
{
	Poly ans;
	ans.n = a.n + b.n;
	for (int i = 0; i <= a.n; i++)
		for (int j = 0; j <= b.n; j++)
			ans.a[i + j] = (ans.a[i + j] + 1ll * a.a[i] * b.a[j]) % Mod;
	return ans;
}
Poly operator * (const Poly& a, int b)
{
	Poly ans;
	ans.n = a.n;
	for (int i = 0; i <= ans.n; i++)
		ans.a[i] = 1ll * a.a[i] * b % Mod;
	return ans;
}

Poly c[100010];
Poly p[100010];
Poly P(int i, int k)
{
	int r = 1;
	Poly ans(1);
	for (int t = 1; t < k; t++)
	{
		ans = ans * Poly(1, (Mod + t - i) % Mod);
		r = 1ll * r * t % Mod;
	}
	ans = ans * inv(r);
	return ans;
}

int n, m, k;
inline int lowbit(int x){ return x & (-x); }
void add(int x, int y)
{
	Poly add = p[x] * y;
	for (; x <= n; x += lowbit(x))
		c[x] = c[x] + add;
}
Poly query(int x)
{
	Poly ans;
	for (; x; x -= lowbit(x))
		ans = ans + c[x];
	return ans;
}

int main()
{
	freopen("sum.in", "r" ,stdin);
	freopen("sum.out", "w", stdout);
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		p[i] = P(i, k);
	for (int i = 1; i <= n; i++)
	{
		int x; scanf("%d", &x);
		add(i, x);
	}
	for (int i = 1; i <= m; i++)
	{
		int op, a, b;
		scanf("%d %d %d", &op, &a, &b);
		if (op == 1) add(a, b);
		else{
			int ans = (query(b).calc(b) - query(a - 1).calc(b) + Mod) % Mod;
			printf("%d\n", ans);
		}
	}
	return 0;
}
