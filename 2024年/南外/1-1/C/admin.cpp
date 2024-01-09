#include <algorithm>
#include <cstdio>

struct Vector {
	int x, y;
	Vector &operator+=(const Vector &o) {
		x += o.x;
		y += o.y;
		return *this;
	}
	Vector &operator-=(const Vector &o) {
		x -= o.x;
		y -= o.y;
		return *this;
	}
};

const int N = 1e6, M = 2e6 + 2;

int n, m, to[M], weight[M], next[M], head[N], vis[N], deg[N], queue[N], vertex[N], tot[2], current_cnt, difference_cnt;
bool evis[M];
Vector p0, current[N], convex[N], difference[N];

Vector operator+(Vector a, const Vector &b)
{
	return a += b;
}

Vector operator-(Vector a, const Vector &b)
{
	return a -= b;
}

bool operator<(const Vector &a, const Vector &b)
{
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

long long cross(const Vector &a, const Vector &b)
{
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

bool cmp_argument(const Vector &a, const Vector &b)
{
	return cross(a, b) > 0;
}

void dfs_tree(int u)
{
	current[current_cnt++] = {tot[0], tot[1]};
	for (int i = head[u]; i; i = next[i]) {
		if (evis[i / 2]) {
			int v = to[i];
			evis[i / 2] = false;
			tot[u & 1] += weight[i];
			tot[v & 1] -= weight[i ^ 1];
			dfs_tree(v);
			evis[i / 2] = true;
			tot[u & 1] -= weight[i];
			tot[v & 1] += weight[i ^ 1];
		}
	}
}

void dfs_circle(int u)
{
	bool flag = true;
	for (int i = head[u]; i; i = next[i]) {
		if (!evis[i / 2]) {
			flag = false;
			int v = to[i];
			evis[i / 2] = true;
			tot[u & 1] += weight[i];
			dfs_circle(v);
			evis[i / 2] = false;
			tot[u & 1] -= weight[i];
		}
	}
	if (flag)
		current[current_cnt++] = {tot[0], tot[1]};
}

int main()
{
	freopen("world.in", "r", stdin);
	freopen("world.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1, j = 2; i <= m; ++i) {
		int x, y, a, b;
		scanf("%d%d%d%d", &x, &y, &a, &b);
		x = 2 * x - 2;
		y = 2 * y - 1;
		to[j] = y;
		weight[j] = a;
		next[j] = head[x];
		head[x] = j++;
		to[j] = x;
		weight[j] = b;
		next[j] = head[y];
		head[y] = j++;
		++deg[x];
		++deg[y];
	}
	for (int i = 0; i < 2 * n; ++i) {
		if (vis[i])
			continue;
		int *qhead = queue, *qtail = queue, cnt = 0, ecnt = 0;
		*qtail++ = i;
		vis[i] = 1;
		while (qhead != qtail) {
			int u = *qhead++;
			vertex[cnt++] = u;
			ecnt += deg[u];
			for (int j = head[u]; j; j = next[j]) {
				int v = to[j];
				if (!vis[v]) {
					vis[v] = 1;
					*qtail++ = v;
				}
			}
		}
		ecnt /= 2;
		qhead = qtail = queue;
		for (int j = 0; j < cnt; ++j) {
			if (deg[vertex[j]] == 1)
				*qtail++ = vertex[j];
		}
		tot[0] = tot[1] = 0;
		while (qhead != qtail) {
			int u = *qhead++;
			vis[u] = 2;
			for (int j = head[u]; j; j = next[j]) {
				if (!evis[j / 2]) {
					tot[u % 2] += weight[j];
					evis[j / 2] = true;
					if (--deg[to[j]] == 1)
						*qtail++ = to[j];
				}
			}
		}
		current_cnt = 0;
		if (ecnt < cnt) {
			int u;
			for (int j = 0; j < cnt; ++j) {
				u = vertex[j];
				if (deg[u] == 0)
					break;
			}
			dfs_tree(u);
		} else {
			int u;
			for (int j = 0; j < cnt; ++j) {
				u = vertex[j];
				if (vis[u] == 1)
					break;
			}
			dfs_circle(u);
		}
		std::sort(current, current + current_cnt);
		Vector *end = convex;
		for (int i = 0; i < current_cnt; ++i) {
			Vector u = current[i];
			while (end - convex > 1 && cross(end[-1] - end[-2], u - end[-1]) <= 0)
				--end;
			*end++ = u;
		}
		p0 += convex[0];
		for (int i = 1; i < end - convex; ++i)
			difference[difference_cnt++] = convex[i] - convex[i - 1];
	}
	std::sort(difference, difference + difference_cnt, cmp_argument);
	long long ans = 1ll * p0.x * p0.y;
	for (int i = 0; i < difference_cnt; ++i) {
		p0 += difference[i];
		ans = std::min(ans, 1ll * p0.x * p0.y);
	}
	printf("%lld\n", ans);
	return 0;
}

