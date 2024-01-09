#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
const int N = 3e5 + 5;
int n, q;

struct Itv {
	int l, r;
	inline bool operator < (const Itv &o) const { return (l != o.l ? l < o.l : r < o.r); }
};

set<Itv> st[N];

struct PQ {
	priority_queue<int, vector<int>, greater<int>> Q, Qdel;
	inline int top() {
		while (!Qdel.empty() && Q.top() == Qdel.top()) Q.pop(), Qdel.pop();
		return Q.top();
	}
	inline void push(int x) { Q.push(x); }
	inline void pop(int x) { Qdel.push(x); }
};

int rt, tot;

struct Node {
	int ls, rs, val, up, num, len, cov;
	ull sum, tagA, tagB;
	PQ pq;
} T[N << 1];

void build(int &x, int l = 1, int r = n) {
	x = ++tot;
	T[x].num = T[x].len = r - l + 1;
	if (x == 1) {
		T[x].val = 1, T[x].up = q + 1;
		for (int i = 1; i <= q + 1; ++i) T[x].pq.push(i);
	} else {
		T[x].val = q + 1, T[x].up = 1;
		T[x].pq.push(q + 1);
	}
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(T[x].ls, l, mid), build(T[x].rs, mid + 1, r);
}

inline void pushup(Node &t) {
	t.val = min({T[t.ls].val, T[t.rs].val, t.pq.top()});
	t.num = 0;
	if (t.val == T[t.ls].val) t.num += T[t.ls].num;
	if (t.val == T[t.rs].val) t.num += T[t.rs].num;
	if (t.val == t.pq.top()) t.num = t.len;
	t.sum = T[t.ls].sum + T[t.rs].sum;
}

inline void merge_tag(Node &t, ull A, ull B, int W, int C) {
	t.sum += A * t.len + B * (W <= t.val ? t.len : t.num);
	t.tagA += A + (W <= t.val) * B;
	t.tagB += (W > t.val) * B;
	if (C) t.up = C, t.cov = min(C, t.pq.top());
}

inline void pushdown(Node &t) {
	if (t.tagA || t.tagB || t.cov) {
		merge_tag(T[t.ls], t.tagA, t.tagB * (min(t.pq.top(), T[t.ls].val) == t.val), t.pq.top(), t.cov);
		merge_tag(T[t.rs], t.tagA, t.tagB * (min(t.pq.top(), T[t.rs].val) == t.val), t.pq.top(), t.cov);
		t.tagA = t.tagB = t.cov = 0;
	}
}

void insert(int L, int R, int v, int x = 1, int l = 1, int r = n) {
	if (L <= l && r <= R) {
		if (l < r) pushdown(T[x]);
		int oldw = T[x].pq.top();
		T[x].pq.push(v);
		int w = T[x].pq.top();
		if (l == r) T[x].val = w;
		else pushup(T[x]);
		if (min(w, T[x].up) != min(oldw, T[x].up)) T[x].cov = min(w, T[x].up);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(T[x]);
	if (L <= mid) insert(L, R, v, T[x].ls, l, mid);
	if (R > mid) insert(L, R, v, T[x].rs, mid + 1, r);
	pushup(T[x]);
}

void erase(int L, int R, int v, int x = 1, int l = 1, int r = n) {
	if (L <= l && r <= R) {
		if (l < r) pushdown(T[x]);
		int oldw = T[x].pq.top();
		T[x].pq.pop(v);
		int w = T[x].pq.top();
		if (l == r) T[x].val = w;
		else pushup(T[x]);
		if (min(oldw, T[x].up) != min(w, T[x].up)) T[x].cov = min(w, T[x].up);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(T[x]);
	if (L <= mid) erase(L, R, v, T[x].ls, l, mid);
	if (R > mid) erase(L, R, v, T[x].rs, mid + 1, r);
	pushup(T[x]);
}

int askmin(int L, int R, int x = 1, int l = 1, int r = n) {
	if (L <= l && r <= R) return min(T[x].val, T[x].up);
	int mid = (l + r) >> 1, res = q + 1;
	pushdown(T[x]);
	if (L <= mid) res = min(res, askmin(L, R, T[x].ls, l, mid));
	if (R > mid) res = min(res, askmin(L, R, T[x].rs, mid + 1, r));
	return res;
}

void update(int L, int R, int k, ull c, int x = 1, int l = 1, int r = n) {
	if (L <= l && r <= R) {
		if (l < r) pushdown(T[x]);
		if (T[x].up == k) T[x].sum += c * T[x].len, T[x].tagA += c;
		else if (T[x].val == k) T[x].sum += c * T[x].num, T[x].tagB += c;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(T[x]);
	if (L <= mid) update(L, R, k, c, T[x].ls, l, mid);
	if (R > mid) update(L, R, k, c, T[x].rs, mid + 1, r);
	pushup(T[x]);
}

ull query(int L, int R, int x = 1, int l = 1, int r = n) {
	if (L <= l && r <= R) return T[x].sum;
	int mid = (l + r) >> 1; ull res = 0;
	pushdown(T[x]);
	if (L <= mid) res += query(L, R, T[x].ls, l, mid);
	if (R > mid) res += query(L, R, T[x].rs, mid + 1, r);
	return res;
}

inline void cover(set<Itv> &s, int l, int r, int v, int op) {
	int L = l, R = r;
	auto it = s.lower_bound(Itv{l, r});
	if (it != s.begin() && prev(it)->r >= l) --it, L = it->l;
	for (; it != s.end() && it->l <= r; it = s.erase(it)) erase(it->l, it->r, v), R = max(R, it->r);
	if (op) {
		if (L <= R) s.insert(Itv{L, R}), insert(L, R, v);
	} else {
		if (L < l) s.insert(Itv{L, l - 1}), insert(L, l - 1, v);
		if (r < R) s.insert(Itv{r + 1, R}), insert(r + 1, R, v);
	}
}

int main() {
	freopen("minmex.in", "r", stdin);
	freopen("minmex.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	build(rt);
	for (int i = 1; i <= q + 1; ++i) st[i].insert(Itv{1, n});
	for (int i = 1; i <= q; ++i) {
		int op, l, r, x; ull c;
		cin >> op >> l >> r;
		if (op == 1) {
			cin >> x;
			cover(st[x], l, r, x, 0);
		} else if (op == 2) {
			cin >> x;
			cover(st[x], l, r, x, 1);
		} else if (op == 3) {
			cin >> c;
			int k = askmin(l, r);
			update(l, r, k, c);
		} else {
			cout << query(l, r) << '\n';
		}
	}
	return 0;
}
