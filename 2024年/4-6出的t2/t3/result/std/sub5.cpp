#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#pragma warning (disable: 4996)

struct Node {
	int BeforeL, BeforeR;
	int AfterL, AfterR;
};

bool operator<(const Node& a1, const Node& a2) {
	if (a1.BeforeL < a2.BeforeL) return true;
	return false;
}

class SegmentTree {
public:
	int mod = 0;
	int size_ = 1;
	int tmp = 0;
	vector<vector<Node>> dat;

	// Initialize SegmentTree
	void Init(int sz, int mod_) {
		mod = mod_;
		while (size_ <= sz) size_ *= 2;
		Node ZERO = Node{ 0, mod - 1, 0, mod - 1 };
		dat.resize(size_ * 2, vector<Node>{});
		for (int i = size_; i < size_ * 2; i++) dat[i].push_back(ZERO);
	}

	// Add Information: A[pos] = x
	void update(int pos, int x) {
		pos += size_;
		dat[pos].clear();
		dat[pos].push_back(Node{ 0, x - 1, (x + 1) % mod, (2 * x) % mod });
		dat[pos].push_back(Node{ x, mod - 1, (2 * x) % mod, (mod - 1 + x) % mod });
	}

	// Merge Vertex pos*2 and pos*2+1
	void Merge(int pos) {
		for (int i = 0; i < dat[pos * 2].size(); i++) {
			int pos1 = lower_bound(dat[pos * 2 + 1].begin(), dat[pos * 2 + 1].end(), Node{ dat[pos * 2][i].AfterL + 1, 0, 0, 0 }) - dat[pos * 2 + 1].begin(); pos1--;
			int pos2 = lower_bound(dat[pos * 2 + 1].begin(), dat[pos * 2 + 1].end(), Node{ dat[pos * 2][i].AfterR + 1, 0, 0, 0 }) - dat[pos * 2 + 1].begin(); pos2--;
			if (dat[pos * 2][i].AfterL > dat[pos * 2][i].AfterR) pos2 += dat[pos * 2 + 1].size();

			// Addition
			for (int j = pos1; j <= pos2; j++) {
				int idx = j % dat[pos * 2 + 1].size();
				int cl = dat[pos * 2][i].AfterL;
				int cr = dat[pos * 2][i].AfterR;
				if (cl > cr) {
					if (j >= dat[pos * 2 + 1].size()) cl = 0;
					else cr = mod - 1;
				}

				// Calculate Actual cl, cr & Offset
				cl = max(cl, dat[pos * 2 + 1][idx].BeforeL);
				cr = min(cr, dat[pos * 2 + 1][idx].BeforeR);
				int offset1 = (dat[pos * 2][i].BeforeL - dat[pos * 2][i].AfterL); if (offset1 < 0) offset1 += mod;
				int offset2 = (dat[pos * 2 + 1][idx].AfterL - dat[pos * 2 + 1][idx].BeforeL); if (offset2 < 0) offset2 += mod;

				// Add to dat[pos]
				dat[pos].push_back(Node{ (offset1 + cl) % mod, (offset1 + cr) % mod, (offset2 + cl) % mod, (offset2 + cr) % mod });
			}
		}
	}

	// Recursion
	void query_(int l, int r, int a, int b, int u) {
		if (l <= a && b <= r) {
			int pos1 = lower_bound(dat[u].begin(), dat[u].end(), Node{ tmp + 1, 0, 0, 0 }) - dat[u].begin(); pos1--;
			int offset = dat[u][pos1].AfterL - dat[u][pos1].BeforeL; if (offset < 0) offset += mod;
			tmp = (tmp + offset) % mod;
			return;
		}
		if (r <= a || b <= l) return;
		query_(l, r, a, ((a + b) >> 1), u * 2);
		query_(l, r, ((a + b) >> 1), b, u * 2 + 1);
	}

	// Answer Query [cl, cr)
	int query(int cl, int cr, int x) {
		tmp = x;
		query_(cl, cr, 0, size_, 1);
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
	int StartingPosition = 0;
	for (int i = 1; i <= N; i++) {
		if (C[i] == 'R') StartingPosition += 1;
	}
	Z.Init(M + 2, N + 1);
	for (int i = 1; i <= M; i++) Z.update(i, A[i]);
	for (int i = Z.size_ - 1; i >= 1; i--) Z.Merge(i);

	// Answer Query
	for (int i = 1; i <= Q; i++) {
		printf("%d\n", Z.query(L[i], R[i] + 1, StartingPosition));
	}
	return 0;
}
