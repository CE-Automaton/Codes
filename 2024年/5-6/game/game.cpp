#include <bits/stdc++.h>
 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#define INF 1000000000
#define FOR(i, a, b) for (int i = int(a); i < int(b); i++)
#define FORC(cont, it) \
  for (decltype((cont).begin()) it = (cont).begin(); it != (cont).end(); it++)
#define pb push_back
#define _                                               \
  if (argc == 2 && ((string)argv[1]) == "USE_IO_FILES") \
    freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout);
 
using namespace std;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef tree<int,        // key
             null_type,  // value
             less<int>, rb_tree_tag, tree_order_statistics_node_update>
    ordered_set;
 
#define maxN 101
 
int N;
double dp[maxN][maxN][maxN];
 
double solve(int n, int m, int k) {
  if (n < 0 || m < 0) return 0;
  if (n == 0 && m == 0) return 0;
  double &c = dp[n][m][k];
  if (c != -1) return c;
  double p1 = 1. * n / (n + m);
  c = p1 * solve(n - 1, m, max(0, k - 1)) + (1. - p1) * solve(n, m - 1, k + 1);
  if (!k) c += p1 * n;
  return c;
}
 
int main(int argc, char *argv[]) {
  freopen("game.in","r",stdin);
  freopen("game.out","w",stdout);
  _;
  FOR(i, 0, maxN) FOR(j, 0, maxN) FOR(k, 0, maxN) dp[i][j][k] = -1;
  while (scanf("%d", &N) != EOF) {
    printf("%.6f\n", solve(N, N, 0));
  }
  return 0;
}
