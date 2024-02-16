constexpr int N = 1e6 + 10, M = 5e6 + 10;

int n;
int sa[N], rk[N], hi[N];

int d[N];
int d1[N], d2[N];

struct addedge {
	int sz, head[N], nxt[M], to[M], val[M];
	void ae(int x, int y, int v) {
		++sz, nxt[sz] = head[x], head[x] = sz, to[sz] = y, val[sz] = v;
	}
	#define foreach(e, x) for(int e = nei.head[x]; e; e = nei.nxt[e])
} nei;
int dfn[N], low[N], nowdfn;
int cnt, cid[N]; vi cc[N];
void tar(int x) {
	static int stk[N], top; static bool ins[N];
	dfn[x] = low[x] = ++nowdfn;
	stk[top++] = x; ins[x] = true;
	foreach(e, x) {
		int y = nei.to[e];
		if(!dfn[y]) tar(y), chkmn(low[x], low[y]);
		else if(ins[y]) chkmn(low[x], dfn[y]);
	}
	if(low[x] == dfn[x]) {
		++cnt;
		while(true) {
			int y = stk[--top]; ins[y] = false;
			cid[y] = cnt, cc[cnt].pb(y);
			if(y == x) break;
		}
	}
}
int dis[N];
char a[N];
void DP() {
	REP(i, 1, n) nei.ae(i, 0, 0);
	REP(i, 0, n) if(!dfn[i]) tar(i);
	memset(dis, 0x3f, sizeof(dis)); dis[1] = 0;
	REP(i, 2, cnt) {
		for(int x : cc[i]) foreach(e, x) {
			if(i != cid[nei.to[e]]) chkmn(dis[i], dis[cid[nei.to[e]]] + nei.val[e]);
		}
	}
	REP(i, 2, cnt) for(int x : cc[i]) a[x] = 'a' - dis[i];
}

void mian() {
	n = read();
	REP(i, 1, n) sa[i] = read(), rk[sa[i]] = i;
	REP(i, 2, n) hi[i] = read();
	REP(i, 2, n) if(hi[i] != -1) {
		int x = sa[i - 1], y = sa[i];
		++d1[x], --d1[x + hi[i]];
		++d2[y], --d2[y + hi[i]];
		if(x + hi[i] <= n) nei.ae(y + hi[i], x + hi[i], -1);
	}
	REP(i, 1, n) {
		d1[i] += d1[i - 1], d2[i] += d2[i - 1];
		d[rk[i]] += d1[i], d[rk[i]] -= d2[i];
	}
	REP(i, 1, n) d[i] += d[i - 1];
	REP(i, 1, n - 1) if(d[i]) nei.ae(sa[i], sa[i + 1], 0), nei.ae(sa[i + 1], sa[i], 0);
	REP(i, 2, n) if(hi[i] == -1) {
		int x = sa[i - 1], y = sa[i];
		nei.ae(y, x, rk[x + 1] < rk[y + 1] ? 0 : -1);
	}
	cerr << (db)clock() / CLOCKS_PER_SEC << "s\n";
	DP();
	prts(a + 1), pc('\n');
}
