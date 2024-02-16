constexpr int N = 510;

int n;
int iv[N], fc[N], ifc[N];
int dp[N][N][2];

void mian() {
	n = read(), P = read();
	iv[1] = 1; REP(i, 2, n) iv[i] = (ll)iv[P % i] * (P - P / i) % P;
	fc[0] = ifc[0] = 1; REP(i, 1, n) fc[i] = (ll)fc[i - 1] * i % P, ifc[i] = (ll)ifc[i - 1] * iv[i] % P;
	dp[1][0][0] = dp[1][0][1] = dp[1][1][1] = 1;
	REP(i, 2, n) REP(j, 0, i - 1) REP(k, 0, 1) {
		REP(x, 0, i - 1 - j) REP(y, 0, i - 1 - j - x) if(j || x || y) {
			int x0 = x + (k == 1) * j, y0 = y + (k == 0) * j;
			int x00 = x + (k == 0) * j, y00 = y + (k == 1) * j;
			int ad = x0 < y0 ? dp[i - j - x - y][y0 - x0][0] : dp[i - j - x - y][x0 - y0][1];
			addto(dp[i][j][k], (ll)ifc[x00] * ifc[y00] % P * ad % P);
		}
	}
	int ans = dp[n][0][0];
	ans = (ll)fc[n] * ans % P;
	prt(ans), pc('\n');
}
