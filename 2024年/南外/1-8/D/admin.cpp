#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
const long long INF = 1e18;
template <typename T> void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> void chkmin(T &x, T y) {x = min(x, y); } 
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
template <typename T> void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T> void writeln(T x) {
	write(x);
	puts("");
}
struct SegmentTree {
	struct Node {
		int lc, rc;
		int exist, tag;
		long long delta, timer;
	} a[MAXN * 2];
	int Root, size, n, tp;
	int val[MAXN], pre[MAXN], suc[MAXN];
	long long dp[MAXN];
	void update(int root) {
		a[root].exist = a[a[root].lc].exist + a[a[root].rc].exist;
		a[root].timer = min(a[a[root].lc].timer, a[a[root].rc].timer);
	}
	void build(int &root, int l, int r) {
		root = ++size;
		if (l == r) {
			if (l == 0) a[root].exist = 1;
			a[root].timer = INF;
			return;
		}
		int mid = (l + r) / 2;
		build(a[root].lc, l, mid);
		build(a[root].rc, mid + 1, r);
		update(root);
	}
	void init(int x, int *p, int *a) {
		n = x;
		Root = size = 0;
		for (int i = 0; i <= n; i++) {
			val[i] = a[p[i]];
			pre[i] = suc[i] = -1;
		}
		build(Root, 0, n);
	}
	void pushdown(int root) {
		if (a[root].tag) {
			int tmp = a[root].tag;
			a[a[root].lc].tag += tmp;
			a[a[root].lc].timer += tmp;
			a[a[root].rc].tag += tmp;
			a[a[root].rc].timer += tmp;
			a[root].tag = 0;
		}
		if (a[root].delta) {
			long long tmp = a[root].delta;
			a[a[root].lc].delta += tmp;
			a[a[root].rc].delta += tmp;
			a[root].delta = 0;
		}
	}
	void access(int root, int l, int r, int pos) {
		if (l == r) {
			dp[pos] -= 1ll * val[l] * a[root].tag;
			a[root].tag = 0;
			dp[pos] += a[root].delta;
			a[root].delta = 0;
			tp = root;
			return;
		}
		pushdown(root);
		int mid = (l + r) / 2;
		if (mid >= pos) access(a[root].lc, l, mid, pos);
		else access(a[root].rc, mid + 1, r, pos);
		update(root);
	}
	void delt(int root, int l, int r, int pos) {
		if (l == r) {
			a[root].tag = 0;
			a[root].delta = 0;
			a[root].exist = 0;
			a[root].timer = INF;
			int s = suc[pos], p = pre[pos];
			suc[p] = s;
			if (s != -1) pre[s] = p;
			return;
		}
		pushdown(root);
		int mid = (l + r) / 2;
		if (mid >= pos) delt(a[root].lc, l, mid, pos);
		else delt(a[root].rc, mid + 1, r, pos);
		update(root);
	}
	void recaltimer(int root, int l, int r, int pos) {
		if (l == r) {
			dp[pos] -= 1ll * val[l] * a[root].tag;
			a[root].tag = 0;
			dp[pos] += a[root].delta;
			a[root].delta = 0;
			int tpos = suc[l];
			if (tpos == -1) a[root].timer = INF;
			else {
				access(Root, 0, n, tpos);
				if (val[tpos] == val[l]) a[root].timer = INF;
				else {
					long long tmp = dp[l] - dp[tpos];
					long long tnp = val[tpos] - val[l];
					if (tmp <= 0) a[root].timer = 0;
					else if (tmp % tnp == 0) a[root].timer = tmp / tnp;
					else a[root].timer = tmp / tnp + 1;
				}
			}
			return;
		}
		pushdown(root);
		int mid = (l + r) / 2;
		if (mid >= pos) recaltimer(a[root].lc, l, mid, pos);
		else recaltimer(a[root].rc, mid + 1, r, pos);
		update(root);
	}
	int pred(int root, int l, int r, int pos) {
		if (a[root].exist == 0) return -1;
		else if (l == r) return l;
		int mid = (l + r) / 2, tmp;
		pushdown(root);
		if (mid >= pos) return pred(a[root].lc, l, mid, pos);
		else {
			tmp = pred(a[root].rc, mid + 1, r, pos);
			if (tmp != -1) return tmp;
			else return pred(a[root].lc, l, mid, pos);
		}
	}
	void modify(int root, int l, int r, int pos, long long d) {
		if (l == r) {
			dp[pos] -= 1ll * val[l] * a[root].tag;
			a[root].tag = 0;
			dp[pos] += a[root].delta;
			a[root].delta = 0;
			if (a[root].exist == 0) {
				a[root].exist = 1; dp[pos] = d;
				int tmp = pred(Root, 0, n, pos - 1);
				pre[pos] = tmp;
				suc[pos] = suc[tmp];
				suc[tmp] = pos;
				if (suc[pos] != -1) pre[suc[pos]] = pos;
			} else chkmin(dp[pos], d);
			recaltimer(Root, 0, n, pre[pos]);
			recaltimer(Root, 0, n, pos);
			return;
		}
		pushdown(root);
		int mid = (l + r) / 2;
		if (mid >= pos) modify(a[root].lc, l, mid, pos, d);
		else modify(a[root].rc, mid + 1, r, pos, d);
		update(root);
	}
	void add(int root, int l, int r, int ql, int qr, int d) {
		if (l == ql && r == qr) {
			a[root].delta += d;
			return;
		}
		pushdown(root);
		int mid = (l + r) / 2;
		if (mid >= ql) add(a[root].lc, l, mid, ql, min(mid, qr), d);
		if (mid + 1 <= qr) add(a[root].rc, mid + 1, r, max(mid + 1, ql), qr, d);
		update(root);
	}
	int findzero(int root, int l, int r) {
		if (l == r) return l;
		int mid = (l + r) / 2;
		pushdown(root);
		if (a[a[root].lc].timer == 0) return findzero(a[root].lc, l, mid);
		else return findzero(a[root].rc, mid + 1, r);
		update(root);
	}
	void maintain() {
		while (a[Root].timer <= 0) {
			int tmp = findzero(Root, 0, n);
			int tnp = suc[tmp];
			suc[tmp] = suc[tnp];
			if (suc[tnp] != -1) pre[suc[tnp]] = tmp;
			suc[tnp] = pre[tnp] = -1;
			delt(Root, 0, n, tnp);
			recaltimer(Root, 0, n, tmp);
		}
	}
	void add(int pos, int d) {
		add(Root, 0, n, 0, pos, d);
		int tmp = pred(Root, 0, n, pos);
		recaltimer(Root, 0, n, tmp);
		maintain();
	}
	long long getpre(int pos) {
		int tmp = pred(Root, 0, n, pos);
		access(Root, 0, n, tmp);
		return dp[tmp];
	}
	void modify(int pos, long long d) {
		modify(Root, 0, n, pos, d);
		maintain();
	}
	long long getans() {
		int now = 0;
		long long ans = INF;
		while (now != -1) {
			access(Root, 0, n, now);
			chkmin(ans, dp[now]);
			now = suc[now];
		}
		return ans;
	}
	void inc(int root, int l, int r, int ql, int qr) {
		if (l == ql && r == qr) {
			a[root].tag -= 1;
			a[root].timer -= 1;
			return;
		}
		pushdown(root);
		int mid = (l + r) / 2;
		if (mid >= ql) inc(a[root].lc, l, mid, ql, min(mid, qr));
		if (mid + 1 <= qr) inc(a[root].rc, mid + 1, r, max(mid + 1, ql), qr);
		update(root);
	}
	void inc(int pos) {
		inc(Root, 0, n, pos, n);
		int tmp = pred(Root, 0, n, pos - 1);
		recaltimer(Root, 0, n, tmp);
		maintain();
	}
	void debug() {
		int now = 0;
		while (now != -1) {
			access(Root, 0, n, now);
			cerr << now << ':' << dp[now] << ':' << a[tp].timer << ' ';
			now = suc[now];
		}
		cerr << endl;
	}
} ST;
int n, a[MAXN], rk[MAXN], p[MAXN];
bool cmp(int x, int y) {
	return a[x] < a[y];
}
int main() {
	freopen("stairs.in", "r", stdin);
	freopen("stairs.out", "w", stdout);
	read(n);
	for (int i = 1; i <= n; i++)
		read(a[i]), p[i] = i;
	sort(p + 1, p + n + 1, cmp);
	for (int i = 1; i <= n; i++)
		if (a[p[i]] != a[p[i - 1]]) rk[p[i]] = i;
		else rk[p[i]] = rk[p[i - 1]];
	ST.init(n, p, a);
	int Max = 0;
	for (int i = 1; i <= n; i++) {
		if (rk[i] > Max) ST.add(Max, a[i]), Max = rk[i];
		else {
			long long tmp = ST.getpre(rk[i]) + a[i];
			ST.add(rk[i] - 1, a[p[Max]]);
			ST.inc(rk[i]);
			ST.modify(rk[i], tmp);
		}
	}
	writeln(ST.getans());
	return 0;
}
