#include <bits/stdc++.h>
#include "tree.h"
typedef long long LL;
typedef std::pair<int, int> P;
template<typename T> inline void chkmin(T &a, const T &b) { a = a < b ? a : b; }
template<typename T> inline void chkmax(T &a, const T &b) { a = a > b ? a : b; }

using namespace std;
#define SZ(x) (int)x.size()

const int MAXN = 5005;
mt19937 mt(0);
bool vis[MAXN];

int rand(int l, int r) {
	return mt() % (r - l + 1) + l;
}

int dfs(int u, int d, int msk) {
	if (d == 0) return 0;
	if (d == 1 && !msk) return u;
	vis[u] = true;
	vector<int> un = query(u);
	if (SZ(un) == 2) return u;
	int c = 1;
	for (int i : un) if (!vis[i]) {
		int f = dfs(i, d - 1, msk | (c--));
		if (f) return f;
	}
	return 0;
}

int solve(int h) {
	memset(vis, 0, sizeof(vis));
	int n = (1 << h) - 1, s = rand(1, n), dep = 0;
	int op = 0, mx = 1e9;
	for (int i = 1; i <= h; i++) {
		int c = i * (i + 1) / 2 + (1 << (h - i)) - 2;
		if (c < mx) mx = c, op = i;
	}
	
	while (true) {
		++dep;
		if (dep == h) return s;
		vector<int> sn = query(s);
		vis[s] = true;
		if (SZ(sn) == 1) {
			s = sn[0];
			continue;
		}
		if (SZ(sn) == 2) {
			return s;
		}
		vector<int> snv;
		for (int i : sn) if (!vis[i])
			snv.push_back(i);
		
		if (SZ(snv) == 3) {
			int a = snv[0], la = s, b = snv[1], lb = s, fa;
			while (true) {
				vector<int> an = query(a), bn = query(b);
				++dep;
				if (SZ(an) == 2) return a;
				if (SZ(bn) == 2) return b;
				if (SZ(an) == 1 && SZ(bn) == 1) {
					fa = snv[2];
					break;
				} else if (SZ(an) == 1) {
					fa = snv[1];
					break;
				} else if (SZ(bn) == 1) {
					fa = snv[0];
					break;
				} else {
					int na = an[0] == la ? an[1] : an[0];
					int nb = bn[0] == lb ? bn[1] : bn[0];
					la = a, lb = b, a = na, b = nb;
				}
			}
			s = fa;
			continue;
		}
		
		if (dep <= op) {
			int a = snv[0], fa = snv[0], la = s;
			for (int i = 1; i < dep; i++) {
				vector<int> an = query(a);
				if (SZ(an) == 2) return a;
				if (SZ(an) == 1) {
					fa = snv[1];
					break;
				}
				int na = an[0] == la ? an[1] : an[0];
				la = a, a = na;
			}
			s = fa;
			continue;
		}
		
		int d = dfs(snv[0], h - dep, 1);
		if (d) return d;
		d = dfs(snv[1], h - dep, 0);
		assert(d > 0);
		return d;
	}
}
