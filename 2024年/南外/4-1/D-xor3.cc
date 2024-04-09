const int dx[5] = {
  0,
  0,
  1,
  -1,
  0
};
const int dy[5] = {
  -1,
  1,
  0,
  0,
  0
};
const int MEMO_COND = 9;
struct XorLife {
  map < pair < vector < string > , int > , long long > mem;
  long long countAliveCells(vector < string > field, int K) {
    int w = field.size(), h = field[0].size();

    // memoization for small fields:
    pair < vector < string > , long long > memokey;
    if (w * h <= MEMO_COND) {
      memokey = make_pair(field, K);
      if (mem.count(memokey)) {
        return mem[memokey];
      }
    }
    long long res = 0;
    if ((K == 0) && (w == 1) && (h == 1)) {
      // If the field is larger than 1x1, we can still
      // partition it. This saves us the code of
      // iterating through all the cells to count the
      // live ones.
      res = (field[0][0] == 'o');

    } else if (K % 2 == 1) {
      //simulate a single step:
      vector < string > newfield(w + 2, string(h + 2, '.'));
      // Add an extra row to the top, an extra row to the bottom
      // an extra column to the left and an extra column to the right.

      for (int i = 0; i < w + 2; i++) {
        for (int j = 0; j < h + 2; j++) {
          int c = 0;
          for (int r = 0; r < 5; r++) {
            int nx = i + dx[r] - 1;
            int ny = j + dy[r] - 1;
            if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
              c += (field[nx][ny] == 'o');
            }
          }
          if (c & 1) {
            newfield[i][j] = 'o';
          }
        }
      }
      res = countAliveCells(newfield, K - 1);

    } else if (w % 2 != 0) {
      // Before partitioning, it simplifies to make sure the field
      // has an even number of rows.
      vector < string > newfield(field);
      newfield.push_back(string(h, '.'));
      res = countAliveCells(newfield, K);

    } else if (h % 2 != 0) {
      // Before partitioning, it simplifies to make sure the field
      // has an even number of columns.
      vector < string > newfield(field);
      for (int i = 0; i < w; i++) {
        newfield[i] += '.';
      }
      res = countAliveCells(newfield, K);

    } else {
      //We can partition the field in 4 parts
      res = 0;
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          vector < string > newfield(w / 2, string(h / 2, '.'));
          for (int x = 0; x < w / 2; x++) {
            for (int y = 0; y < h / 2; y++) {
              if ((x * 2 + i < w) && (y * 2 + j < h)) {
                newfield[x][y] = field[x * 2 + i][y * 2 + j];
              }
            }
          }
          res += countAliveCells(newfield, K / 2);
        }
      }
    }
    // Save the result if the field is small enough:
    if (w * h <= MEMO_COND) {
      mem[memokey] = res;
    }
    return res;

  }
};
