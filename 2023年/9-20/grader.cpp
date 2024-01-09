#include "testlib.h"

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 1e3 + 5;
const int K = 2e6 + 5;

int n, m, k, k0;
string str[N];
int a[K], b[K], c[K], d[K], e[K];

bool check(InStream& ouf) {
	for(int i = 1; i <= n; ++i) {
		str[i] = ouf.readWord();
		if(str[i].length() != m) return 0;
		str[i] = ' ' + str[i];
	}
	int cc = 0;
	for(int i = 1; i <= k; ++i) {
		cc += (str[a[i]][b[i]] != str[c[i]][d[i]]) ^ (!!e[i]);
	}
	return cc <= k0;
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	registerTestlibCmd(argc, argv);
	int t = inf.readInt();
	for(int t0 = 1; t0 <= t; ++t0) {
		n = inf.readInt();
		m = inf.readInt();
		k = inf.readInt();
		k0 = inf.readInt();
		for(int i = 1; i <= k; ++i) {
			a[i] = inf.readInt();
			b[i] = inf.readInt();
			c[i] = inf.readInt();
			d[i] = inf.readInt();
			e[i] = inf.readInt();
		}
		if(!check(ouf)) quitf(_wa, "on testcase %d", t0);
		ensuref(check(ans), "on testcases %d", t0);
	}
	quitf(_ok, "%d testcase(s)", t);
	
	return 0;
}
