constexpr int N = 510;

int n;
int iv[N], fc[N], ifc[N];
int dp[N][N][2];
ull f[N][3 * N][2][2];
int vis[N][3 * N][2];

void mian() {
	n = read();
	iv[1] = 1; REP(i, 2, n) iv[i] = (ll)iv[P % i] * (P - P / i) % P;
	fc[0] = ifc[0] = 1; REP(i, 1, n) fc[i] = (ll)fc[i - 1] * i % P, ifc[i] = (ll)ifc[i - 1] * iv[i] % P;
	dp[1][0][0] = dp[1][0][1] = dp[1][1][1] = 1;
	memset(f, -1, sizeof(f));
	REP(i, 2, n) REP(j, 0, i - 1) REP(k, 0, 1) { // 这优化，多是一件美逝啊…… 
		if(k == 0) {
			REP(x, 0, i - 1 - j) {
				ull &F = f[i - j - x][x + (k ? j : -j) + n][k][j || x];
				if(!~F) {
					F = 0; int c = 0;
					REP(y, 0, i - 1 - j - x) if(j || x || y) {
						int x0 = x + (k == 1) * j, y0 = y + (k == 0) * j;
						int y00 = y + (k == 1) * j;
						int ad = x0 < y0 ? dp[i - j - x - y][y0 - x0][0] : dp[i - j - x - y][x0 - y0][1];
						F += (ll)ifc[y00] * ad;
						if(++c == 18) F %= P, c = 0;
					} F %= P;
				}
				int x00 = x + (k == 0) * j;
				addto(dp[i][j][k], ifc[x00] * F % P);
			}
		} else {
			REP(y, 0, i - 1 - j) {
				ull &F = f[i - j - y][y + (!k ? j : -j) + n][k][j || y];
				if(!~F) {
					F = 0; int c = 0;
					REP(x, 0, i - 1 - j - y) if(j || x || y) {
						int x0 = x + (k == 1) * j, y0 = y + (k == 0) * j;
						int x00 = x + (k == 0) * j;
						int ad = x0 < y0 ? dp[i - j - x - y][y0 - x0][0] : dp[i - j - x - y][x0 - y0][1];
						F += (ll)ifc[x00] * ad;
						if(++c == 18) F %= P, c = 0;
					} F %= P;
				}
				int y00 = y + (k == 1) * j;
				addto(dp[i][j][k], ifc[y00] * F % P);
			}
		}
	}
	int ans = dp[n][0][0];
	ans = (ll)fc[n] * ans % P;
	prt(ans), pc('\n');
}
