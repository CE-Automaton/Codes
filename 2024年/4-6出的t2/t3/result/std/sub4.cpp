#include <iostream>
#include <vector>
using namespace std;
#pragma warning (disable: 4996)

class SegmentTree {
public:
	int size_ = 1, tmp;
	vector<vector<int>> dat;

	void init(int sz) {
		while (size_ <= sz) size_ *= 2;
		dat.resize(size_ * 2, vector<int>(11, 0));
		for (int i = size_; i < size_ * 2; i++) {
			for (int j = 0; j < 11; j++) dat[i][j] = j;
		}
	}

	void update(int pos, int x) {
		pos += size_;
		for (int i = 0; i < 11; i++) {
			if (i < x) dat[pos][i] = (i + x + 1) % 11;
			else dat[pos][i] = (i + x) % 11;
		}
	}

	void Merge() {
		for (int i = size_ - 1; i >= 1; i--) {
			for (int j = 0; j < 11; j++) dat[i][j] = dat[i * 2 + 1][dat[i * 2][j]];
		}
	}

	void query_(int l, int r, int a, int b, int u) {
		if (l <= a && b <= r) { tmp = dat[u][tmp]; return; }
		if (r <= a || b <= l) { return; }
		query_(l, r, a, ((a + b) >> 1), u * 2);
		query_(l, r, ((a + b) >> 1), b, u * 2 + 1);
	}

	int query(int l, int r) {
		tmp = 10;
		query_(l, r, 0, size_, 1);
		return tmp;
	}
};

// Input
int N; char C[120009];
int M, A[120009];
int Q, L[120009], R[120009];
SegmentTree Z;

int main() {
	// Input
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) cin >> C[i];
	for (int i = 1; i <= M; i++) scanf("%d", &A[i]);
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++) scanf("%d%d", &L[i], &R[i]);

	// Precount
	Z.init(M + 2);
	for (int i = 1; i <= M; i++) Z.update(i, A[i]);
	Z.Merge();

	// Answer Query
	for (int i = 1; i <= Q; i++) {
		printf("%d\n", Z.query(L[i], R[i] + 1));
	}
	return 0;
}
