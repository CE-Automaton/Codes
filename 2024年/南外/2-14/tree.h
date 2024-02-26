#include <bits/stdc++.h>
using namespace std;

namespace Worker {
	const int MAXN = 10005;
	int arr[MAXN], mp[MAXN], h, n, S, s;
	
	template<typename ...T> void quit(const char *str, T& ...x) {
		printf(str, x...);
		exit(0);
	}
	
	vector<int> query(int x) {
		if (++s > S) quit("number of options out of bounds = %d", S);
		if (x < 1 || x > n) quit("invalid query: x = %d", x);
		vector<int> ans;
		x = mp[x];
		if (x > 1) ans.push_back(x >> 1);
		if (x << 1 < n) {
			ans.push_back(x << 1);
			ans.push_back(x << 1 | 1);
		}
		for (int &i : ans) i = arr[i];
		random_shuffle(ans.begin(), ans.end());
		return ans;
	}
	
	void init(int x, int t) {
		h = x, n = (1 << h) - 1, S = t;
		for (int i = 1; i <= n; i++) arr[i] = i;
		random_shuffle(arr + 1, arr + 1 + n);
		for (int i = 1; i <= n; i++) mp[arr[i]] = i;
		s = 0;
	}
}

vector<int> query(int x) {
	return Worker::query(x);
}

int solve(int h);

int main() {
	int h, s; unsigned seed;
	scanf("%d%d%u", &h, &s, &seed);
	srand(seed);
	assert(h <= 12 && h > 0);
	int mx = 0;
	for (int i = 1; i <= min(10000000 / s, 10000); i++) {
		Worker::init(h, s);
		int rt = solve(h);
		if (rt != Worker::arr[1]) Worker::quit("wrong answer: answer is %d but your output is %d", Worker::arr[1], rt);
		mx = max(mx, Worker::s);
	}
	Worker::quit("accepted\nmax queries: %d", mx);
	return 0;
}
