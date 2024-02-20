#include <bits/stdc++.h>

using namespace std;

const int N = 11;

int n;
int a[1 << N][1 << N], b[1 << N][1 << N];
vector<pair<int, int>> ans;

int main() {
  freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
  scanf("%d", &n);
  for (int i = 0; i < 1 << n; ++i)
    for (int j = 0; j < 1 << n; ++j) scanf("%d", a[i] + j);
  for (int k = 0; k < n - 1; ++k) {
    memset(b, 0, sizeof b);
    for (int i = 0; i < 1 << n; ++i)
      for (int j = 0; j < 1 << n; ++j)
        if (a[i][j])
          b[i][j] ^= 1,
          b[(i + (1 << k)) & ((1 << n) - 1)][j] ^= 1,
          b[(i + (1 << n) - (1 << k)) & ((1 << n) - 1)][j] ^= 1,
          b[i][(j + (1 << k)) & ((1 << n) - 1)] ^= 1,
          b[i][(j + (1 << n) - (1 << k)) & ((1 << n) - 1)] ^= 1;
    memcpy(a, b, sizeof a);
  }
  for (int i = 0; i < 1 << n; ++i)
    for (int j = 0; j < 1 << n; ++j)
      if (a[i][j]) ans.emplace_back(i, j);
  printf("%d\n", ans.size());
  for (auto [x, y]: ans) printf("%d %d\n", x, y);
}
