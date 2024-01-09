#include <bits/stdc++.h>

/** My code begins here **/

constexpr int N = 500005;
constexpr int M = 7;
std::vector<int> e[N];
int n, m, w2id[N], w[N];

constexpr int gu = 1, gl = 1; int gr;

struct STree {
  struct Node {
    int min = 0;
    int add = 0; 
    int cnt[M] = {0};
    void push_add(int delta) { min += delta; add += delta; }
    void push_up(const Node *a, const Node *b);
    void push_down(Node *a, Node *b) { 
      a->push_add(add); b->push_add(add); add=0; } };
  Node p[N * 4];

  void init(int u, int l, int r) {
    if (r - l == 1) { p[u].min = 1; p[u].cnt[0] = 1; return; }
    int mid = (l + r) / 2; init(u + u, l, mid); init(u + u + 1, mid, r);
    p[u].push_up(&p[u + u], &p[u + u + 1]); }

  void modify(int u, int l, int r, int ml, int mr, int det) {
    if (ml <= l && r <= mr) { p[u].push_add(det); return; } 
    p[u].push_down(&p[u + u], &p[u + u + 1]); int mid = (l + r) / 2;
    if (ml < mid) modify(u + u, l, mid, ml, mr, det);
    if (mr > mid) modify(u + u + 1, mid, r, ml, mr, det);
    p[u].push_up(&p[u + u], &p[u + u + 1]); }
} __attribute__ ((aligned(64)));

STree T;

void STree::Node::push_up(const Node *a, const Node *b) {
  if (a->min > b->min) { std::swap(a, b); }
  int d = b->min - a->min; min = a->min;
  memcpy(cnt, a->cnt, sizeof(int) * 7); 
  for (int i=d; i<M; i++) cnt[i] += b->cnt[i - d]; }

void preInit() {  } 
void init() 
{
  scanf("%d%d", &n, &m);
  gr = n + 1;
  T.init(gu, gl, gr);
  for (int i=1; i<=n; i++) {
    scanf("%d", &w[i]);
    w2id[w[i]] = i; }
  for (int i=1; i<n; i++) { 
    int u, v;
    scanf("%d%d", &u, &v);
    e[u].push_back(v); e[v].push_back(u); }
} 

void solve() 
{
  long long ans = 0;
  for (int i=1; i<=n; i++) { int u = w2id[i]; 
    if (i != 1) T.modify(gu, gl, gr, gl, i, 1);
    for (int v: e[u]) if (w[v] < w[u]) {
      T.modify(gu, gl, gr, gl, w[v] + 1, -1); }
    for (int i=0; i<m; i++) ans += T.p[gu].cnt[i];
    ans -= (n - i); }
  printf("%lld\n", ans);
}

int main()
{ 
  freopen("toccare.in", "r", stdin);
  freopen("toccare.out", "w", stdout); 

  init();
  solve();
  return 0;
}
