int dp[50][50][50][50];
int field[50][50];
int n;

int rec(int x0, int y0, int x1, int y1) {
  if (x0 > x1 || y0 > y1 || x0 < 0 || x1 >= n || y0 < 0 || y1 >= n) {
    return 0;
  }
  int & res = dp[x0][y0][x1][y1];
  if (res == -1) {

    bool U = (y0 == 0);
    bool D = (y1 == n - 1);
    bool R = (x0 == 0);
    bool L = (x1 == n - 1);

    int e, p, q, r;
    res = 0;

    if ((U || D) && !R && !L) {
      // special case: Only vertical moves:
      int s = U + D;
      // best s in column
      int a = 0, b = 0;
      for (int y = y0; y <= y1; y++) {
        int c = field[x1][y];
        if (c > a) {
          b = a;
          a = c;
        } else if (c > b) {
          b = c;
        }
      }
      res = a + ((s == 2) ? b : 0) + rec(x0, y0, x1 - 1, y1);
      return res;
    } else if (!U && !D && (R || L)) {
      // special case: Only horizontal moves:
      int s = R + L;
      int a = 0, b = 0;
      for (int x = x0; x <= x1; x++) {
        int c = field[x][y1];
        if (c > a) {
          b = a;
          a = c;
        } else if (c > b) {
          b = c;
        }
      }
      res = a + ((s == 2) ? b : 0) + rec(x0, y0, x1, y1 - 1);
      return res;
    }
    if (R) { //can go from right to left
      for (int y = y0; y <= y1; y++) {
        for (int x = 0; x <= x1; x++) {
          e = field[x][y];
          p = rec(0, y0, x, y - 1);
          q = rec(0, y + 1, x, y1);
          r = rec(x + 1, y0, x1, y1);
          res = std::max(res, e + p + q + r);
        }
      }
    }
    if (L) { //from left to right:
      for (int y = y0; y <= y1; y++) {
        for (int x = x0; x <= n - 1; x++) {
          e = field[x][y];
          p = rec(x, y0, n - 1, y - 1);
          q = rec(x, y + 1, n - 1, y1);
          r = rec(x0, y0, x - 1, y1);
          res = std::max(res, e + p + q + r);
        }
      }
    }
    if (U) { //can go from bottom to top
      for (int x = x0; x <= x1; x++) {
        for (int y = 0; y <= y1; y++) {
          e = field[x][y];
          p = rec(x0, 0, x - 1, y);
          q = rec(x + 1, 0, x1, y);
          r = rec(x0, y + 1, x1, y1);
          res = std::max(res, e + p + q + r);
        }
      }
    }
    if (D) { //can go from top to bottom
      for (int x = x0; x <= x1; x++) {
        for (int y = y0; y <= n - 1; y++) {
          e = field[x][y];
          p = rec(x0, y, x - 1, n - 1);
          q = rec(x + 1, y, x1, n - 1);
          r = rec(x0, y0, x1, y - 1);
          res = std::max(res, e + p + q + r);
        }
      }
    }
  }
  return res;
}

int maxSum(vector < string > field) {
  n = field.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      this - > field[i][j] = field[i][j] - '0';
    }
  }

  memset(dp, -1, sizeof(dp));
  int res = rec(0, 0, n - 1, n - 1); //Case 1

  // do case 2:
  for (int a = 1; a <= n; a++) {
    for (int b = n - a + 1; b <= n; b++) {
      for (int c = 1; c <= n; c++) {
        for (int d = n - c + 1; d <= n; d++) {
          int p, q, r, s;
          //2.1:
          p = rec(0, 0, n - b - 1, c - 1);
          q = rec(n - b, 0, n - 1, n - d - 1);
          r = rec(a, n - d, n - 1, n - 1);
          s = rec(0, c, a - 1, n - 1);
          res = std::max(res, p + q + r + s);

          //2.2
          p = rec(0, 0, a - 1, n - d - 1);
          q = rec(a, 0, n - 1, c - 1);
          r = rec(n - b, c, n - 1, n - 1);
          s = rec(0, n - d, n - b - 1, n - 1);
          res = std::max(res, p + q + r + s);
        }
      }
    }
  }

  return res;
}
