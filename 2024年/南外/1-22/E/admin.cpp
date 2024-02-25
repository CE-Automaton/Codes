#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9+7;
const int inv2 = (mod + 1) / 2;
const int maxn = 100010;
const int maxw = 100000;

int ans = 0, A, B, n;
int lx, rx, ly, ry;

inline int mo(int x) {if (x >= mod) return x - mod; if (x < 0) return x + mod; return x;}
inline int s1(int x) {return 1LL * x * (x + 1) % mod * inv2 % mod;}

struct Point {
	int x, y;
	Point(int x=0, int y=0) : x(x), y(y) {}
} P[maxn], px[maxn], py[maxn], _px[maxn], _py[maxn];

bool operator<(const Point &p1, const Point &p2) {
	return p1.x > p2.x;
}

Point operator+(const Point &p1, const Point &p2) {
	return Point(min(p1.x, p2.x), min(p1.y, p2.y));
}

struct SegmentTree {
	int sz;
	vector<int> sum, cnt;
	SegmentTree(int s = 0) : sz(s), sum(s * 4 + 10, 0), cnt(s * 4 + 10, 0) {}
	void update(int p, int l, int r, int rt) {
		sum[rt] = mo(sum[rt] + p);
		++ cnt[rt];
		if (l == r) return;
		int m = (l + r) >> 1;
		if (p <= m) update(p, l, m, rt<<1);
		else update(p, m+1, r, rt<<1|1);
	}
	int query(int L, int R, int l, int r, int rt) {
		if (L <= l && r <= R) return sum[rt];
		int ret = 0;
		int m = (l + r) >> 1;
		if (L <= m) ret = mo(ret + query(L, R, l, m, rt<<1));
		if (R > m) ret = mo(ret + query(L, R, m+1, r, rt<<1|1));
		return ret;
	}
	int query0(int L, int R, int l, int r, int rt) {
		if (L <= l && r <= R) return cnt[rt];
		int ret = 0;
		int m = (l + r) >> 1;
		if (L <= m) ret = mo(ret + query0(L, R, l, m, rt<<1));
		if (R > m) ret = mo(ret + query0(L, R, m+1, r, rt<<1|1));
		return ret;
	}
	void update(int p) {update(p, 1, sz, 1);}
	int query(int L, int R) {if (L > R) return 0; return query(L, R, 1, sz, 1);}
	int query0(int L, int R) {if (L > R) return 0; return query0(L, R, 1, sz, 1);}
};

int solve(vector<Point> v1, vector<Point> v2) {
	SegmentTree s1(maxw), s2(maxw);
	int ret = 0;
	vector<pair<Point, int> > vec;
	for (int i = 0; i < v1.size(); i++) vec.push_back(make_pair(v1[i], 1));
	for (int i = 0; i < v2.size(); i++) vec.push_back(make_pair(v2[i], 2));
	sort(vec.begin(), vec.end());
	for (int i = 0; i < vec.size(); i++) {
		int t = vec[i].second;
		if (t == 1) {
			ret = mo(ret + 1LL * vec[i].first.x * s2.query(1, vec[i].first.y) % mod);
			ret = mo(ret + 1LL * vec[i].first.x * vec[i].first.y % mod * s2.query0(vec[i].first.y+1, maxw) % mod);
			s1.update(vec[i].first.y);
		} else {
			ret = mo(ret + 1LL * vec[i].first.x * s1.query(1, vec[i].first.y) % mod);
			ret = mo(ret + 1LL * vec[i].first.x * vec[i].first.y % mod * s1.query0(vec[i].first.y+1, maxw) % mod);
			s2.update(vec[i].first.y);
		}
	}
	return ret;
}

int solve(vector<int> v1, vector<int> v2, vector<int> v3) {
	vector<pair<int, int> > vec;
	for (int i = 0; i < v1.size(); i++) vec.push_back(make_pair(v1[i], 1));
	for (int i = 0; i < v2.size(); i++) vec.push_back(make_pair(v2[i], 2));
	for (int i = 0; i < v3.size(); i++) vec.push_back(make_pair(v3[i], 3));
	int cnt[4]; cnt[1] = cnt[2] = cnt[3] = 0;
	sort(vec.begin(), vec.end(), greater<pair<int, int> >());
	int ret = 0;
	for (int i = 0; i < vec.size(); i++) {
		++ cnt[vec[i].second];
		int t = 1;
		for (int j = 1; j <= 3; j++) if (j != vec[i].second) t = 1LL * t * cnt[j] % mod;
		ret = mo(ret + 1LL * t * vec[i].first % mod);
	}
	return ret;
}

int cal(int l1, int r1, int l2, int r2) {
	if (l1 > r1 || l2 > r2) return 0;
	int ret = 0;
	for (int i = l1; i <= r1; i++) {
		int _l = l2, _r = r2;
		_r = min(_r, i + 1);
		if (_l <= _r) ret = mo(ret + _r - _l + 1);
	}
	return ret;
}

void swapxy() {
	swap(A, B), swap(lx, ly), swap(rx, ry);
	for (int i = 1; i <= maxw; i++) swap(px[i], py[i]), swap(_px[i], _py[i]);
}

void revx() {
	lx = A - lx + 1, rx = A - rx + 1; swap(lx, rx);
	for (int i = 1; i <= maxw; i++) py[i] = Point(py[i].y, py[i].x), _px[i] = Point(_px[i].y, _px[i].x);
	reverse(px + 1, px + A + 1); reverse(_px + 1, _px + A + 1);
}

void revy() {
	ly = B - ly + 1, ry = B - ry + 1; swap(ly, ry);
	for (int i = 1; i <= maxw; i++) px[i] = Point(px[i].y, px[i].x), _py[i] = Point(_py[i].y, _py[i].x);
	reverse(py + 1, py + B + 1); reverse(_py + 1, _py + B + 1);
}

int main() {
	freopen("contest.in", "r", stdin);
	freopen("contest.out", "w", stdout);
	scanf("%d%d%d", &n, &A, &B);
	for (int i = 1; i <= n; i++) scanf("%d%d", &P[i].x, &P[i].y);
	lx = A, ly = B, rx = ry = 1;
	for (int i = 1; i <= n; i++) lx = min(lx, P[i].x), ly = min(ly, P[i].y), rx = max(rx, P[i].x), ry = max(ry, P[i].y);
	for (int i = 0; i <= maxw; i++) py[i] = _px[i] = Point(A, A), px[i] = _py[i] = Point(B, B);
	for (int i = 1; i <= n; i++) px[P[i].x] = px[P[i].x] + Point(P[i].y, B - P[i].y + 1), py[P[i].y] = py[P[i].y] + Point(P[i].x, A - P[i].x + 1);
	for (int i = 1; i <= n; i++) _px[P[i].x] = _px[P[i].x] + Point(P[i].x, A - P[i].x + 1), _py[P[i].y] = _py[P[i].y] + Point(P[i].y, B - P[i].y + 1);
	{
		ans = mo(ans + 1LL * lx * ly % mod * (A - rx + 1) % mod * (B - ry + 1) % mod * s1(A) % mod * s1(B) % mod);
	}
	{
		for (int T1 = 0; T1 < 2; T1++) {
			swapxy();
			{
				vector<Point> v1, v2;
				Point t1(maxw, maxw), t2(maxw, maxw);
				for (int i = ly; i < B; i++) {
					t1 = t1 + Point(py[i].x, py[i].y);
					v1.push_back(t1);
				}
				for (int i = ry; i > 1; i--) {
					t2 = t2 + Point(py[i].x, py[i].y);
					v2.push_back(t2);
				}
				ans = mo(ans + 1LL * solve(v1, v2) * ly % mod * (B - ry + 1) % mod * lx % mod * (A - rx + 1) % mod);
				ans = mo(ans - 1LL * cal(ly, B-1, 2, ry) * lx % mod * ly % mod * (A - rx + 1) % mod * (B - ry + 1) % mod * lx % mod * (A - rx + 1) % mod);
			}
			for (int T2 = 0; T2 < 2; T2++) {
				revy();
				Point t1(maxw, maxw), t2(maxw, maxw);
				for (int i = ly; i < ry; i++) {
					t1 = t1 + Point(py[i].x, py[i].y);
					t2 = t2 + Point(_py[i].x, _py[i].y);
					ans = mo(ans + 1LL * t1.x * t1.y % mod * t2.x % mod * t2.y % mod * lx % mod * (A - rx + 1) % mod * (B-ry+1) % mod);
				}
			}
		}
	}
	{
		for (int T1 = 0; T1 < 2; T1++) {
			revx();
			for (int T2 = 0; T2 < 2; T2++) {
				revy();
				vector<Point> v1, v2;
				Point t1(maxw, maxw), t2(maxw, maxw);
				for (int i = rx; i > lx; i--) {
					t1 = t1 + Point(_px[i].x, px[i].x);
					v1.push_back(t1);
				}
				for (int i = ry; i > ly; i--) {
					t2 = t2 + Point(py[i].x, _py[i].x);
					v2.push_back(t2);
				}
				ans = mo(ans + 1LL * solve(v1, v2) * (A - rx + 1) % mod * (B - ry + 1) % mod * lx % mod * ly % mod);
			}
		}
		for (int T1 = 0; T1 < 2; T1++) {
			swapxy();
			for (int T2 = 0; T2 < 2; T2++) {
				revx();
				vector<int> v1, v2, v3;
				int t1 = maxw, t2 = maxw, t3 = maxw;
				for (int i = rx; i > lx; i--) {
					t1 = min(t1, _px[i].x);
					v1.push_back(t1);
				}
				for (int i = ly; i < B; i++) {
					t2 = min(t2, py[i].x);
					v2.push_back(t2);
				}
				for (int i = ry; i > 1; i--) {
					t3 = min(t3, py[i].x);
					v3.push_back(t3);
				}
				ans = mo(ans + 1LL * solve(v1, v2, v3) * ly % mod * (B - ry + 1) % mod * (A - rx + 1) % mod * lx % mod);
				ans = mo(ans - 1LL * cal(ly, B-1, 2, ry) * (rx-lx) % mod * ly % mod * lx % mod * (B - ry + 1) % mod * (A - rx + 1) % mod * lx % mod);
			}
		}
		{
			if (lx < rx && ly < ry) {
				ans = mo(ans + 1LL * lx * ly % mod * (A - rx + 1) * (B - ry + 1) % mod * s1(rx-lx-1) % mod * s1(ry-ly-1) % mod);
			}
		}
	}
	{
		int res = 0;
		res = mo(res + 1LL * s1(lx-1) * s1(B) % mod);
		res = mo(res + 1LL * s1(A-rx) * s1(B) % mod);
		res = mo(res + 1LL * s1(ly-1) * s1(A) % mod);
		res = mo(res + 1LL * s1(B-ry) * s1(A) % mod);
		res = mo(res - 1LL * s1(lx-1) * s1(ly-1) % mod);
		res = mo(res - 1LL * s1(lx-1) * s1(B-ry) % mod);
		res = mo(res - 1LL * s1(A-rx) * s1(ly-1) % mod);
		res = mo(res - 1LL * s1(A-rx) * s1(B-ry) % mod);
		ans = mo(ans + 1LL * res * lx % mod * ly % mod * (A - rx + 1) % mod * (B - ry + 1) % mod % mod);
	}
	printf("%d\n", ans);
	return 0;
}
