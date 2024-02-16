//Template
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

#define N 1000
const double eps = 5e-5;
const double INFI = 1e20;

int T, n, S;
struct point {
	int x, y, z;
	int vx, vy, vz;
	inline void read() {
		scanf("%d%d%d%d%d%d", &x, &y, &z, &vx, &vy, &vz);
	}
} p[N + 1];

bool v[N + 1];
struct edge {
	bool ok;
	double l, r;
} e[N + 1][N + 1];

struct item {
	int x, y;
	bool left;
	double val;
	item() { }
	item(int _x, int _y, bool _left, double _val) : x(_x), y(_y), left(_left), val(_val) { }
} seq[N * N + 1];

inline bool cmp(const item &a, const item &b) {
	return a.val == b.val ? a.left > b.left : a.val < b.val;
}

int deg[N + 1];
double dfn[N + 1];

template<class T, int L>
struct Queue {
	T q[L + 1];
	int h, t;
	void clear() {
		h = t = 0;
	}
	inline bool empty() const {
		return h == t;
	}
	inline int inc(int &x) {
		return x = x == L ? 0 : x + 1;
	}
	inline void push(const T &x) {
//		q[inc(t)] = x;
		q[t++] = x;
	}
	inline T &top() {
//		return q[h == L ? 0 : h + 1];
		return q[h];
	}
	inline T &pop() {
//		return q[inc(h)];
		return q[h++];
	}
};
struct Pair {
	double first;
	int second;
};
Queue<int, N * 10> q;
Queue<Pair, N * 10> Sq;

double coef[N + 1][N + 1][3];

inline Pair make_pair(double first, int second) {
	Pair ret;
	ret.first = first, ret.second = second;
	return ret;
}

bool check(double d) {
	int cnt = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			double a = coef[i][j][0];
			double b = coef[i][j][1];
			double c = coef[i][j][2] - d * d;
			double delta = b * b - 4 * a * c;
			if (a < eps) {
				if (c < eps) {
					e[i][j].ok = true;
					e[i][j].l = -INFI, e[i][j].r = INFI;
				} else {
					e[i][j].ok = false;
				}
			} else {
				if (delta < 0) {
					e[i][j].ok = false;
				} else {
					delta = sqrt(delta);
					e[i][j].ok = true;
					e[i][j].l = (-b - delta) / a / 2;
					e[i][j].r = (-b + delta) / a / 2;
				}
			}
			if (e[i][j].ok) {
				seq[++cnt] = item(i, j, true, e[i][j].l);
				seq[++cnt] = item(i, j, false, e[i][j].r);
			}
			e[j][i] = e[i][j];
		}
	sort(seq + 1, seq + cnt + 1, cmp);
	
	Sq.clear(), q.clear();
	for (int i = 1; i <= n; ++i)
		v[i] = false, deg[i] = 0, dfn[i] = INFI;
	
	int _t;
	for (_t = 1; _t <= cnt; ++_t) {
		item &it = seq[_t];
		double tick = it.val;
		if (tick > 0.0) break;
		if (it.left) {
			++deg[it.x], ++deg[it.y];
		} else {
			--deg[it.x], --deg[it.y];
		}
	}
	
	q.push(1), v[1] = true;
	while (!q.empty()) {
		int cur = q.pop();
		for (int i = 1; i <= n; ++i)
			if (!v[i] && e[cur][i].ok && e[cur][i].l <= 0 && 0 <= e[cur][i].r)
				v[i] = true, q.push(i);
	}
	for (int i = 1; i <= n; ++i)
		if (v[i] && !deg[i]) dfn[i] = 0, Sq.push(make_pair(0.0, i));
	
	
	for (; _t <= cnt; ++_t) {
		item &it = seq[_t];
		double tick = it.val;
		
		while (!Sq.empty()) {
			Pair top = Sq.top();
			if (dfn[top.second] != top.first) {
				Sq.pop();
			} else if (tick - top.first <= S) {
				break;
			} else {
				v[top.second] = false;
				dfn[top.second] = INFI;
				Sq.pop();
			}
		}
		
		if (it.left) {
			++deg[it.x], ++deg[it.y];
			dfn[it.x] = INFI, dfn[it.y] = INFI;
			if (!v[it.x] && v[it.y]) swap(it.x, it.y);
			if (v[it.x] && !v[it.y]) {
				q.push(it.y), v[it.y] = true;
				while (!q.empty()) {
					int cur = q.pop();
					for (int i = 1; i <= n; ++i)
						if (!v[i] && e[cur][i].ok && e[cur][i].l <= tick && tick <= e[cur][i].r)
							v[i] = true, q.push(i);
				}
			}
		} else {
			--deg[it.x], --deg[it.y];
			if (v[it.x] && !deg[it.x]) {
				dfn[it.x] = tick;
				Sq.push(make_pair(tick, it.x));
			}
			if (v[it.y] && !deg[it.y]) {
				dfn[it.y] = tick;
				Sq.push(make_pair(tick, it.y));
			}
		}
		if (v[2]) return true;
	}
	
	return false;
}

int main(int argc, char *argv[]) { 
	
	scanf("%d%d", &n, &S);
	for (int i = 1; i <= n; ++i)
		p[i].read();
		
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			double vx = p[i].vx - p[j].vx;
			double vy = p[i].vy - p[j].vy;
			double vz = p[i].vz - p[j].vz;
			double x = p[i].x - p[j].x;
			double y = p[i].y - p[j].y;
			double z = p[i].z - p[j].z;
			coef[i][j][0] = vx * vx + vy * vy + vz * vz;
			coef[i][j][1] = 2 * (vx * x + vy * y + vz * z);
			coef[i][j][2] = x * x + y * y + z * z;
		}
	
	double l = 0.0, r = 2000.0;
	while (r - l > eps) {
		double mid = (l + r) / 2.0;
		if (check(mid)) r = mid;
		else l = mid;
	}
	
	printf("%.8lf\n", l); 
	return 0;
}
