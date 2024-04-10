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
int LeftPos[120009], NumLeft;
int RigtPos[120009], NumRigt;
int NextQ[22][22][120009], Haba[22], UpLimit;
long long SumLeft[22][120009];
long long SumRigt[22][120009];
long long SumRed[120009];
SegmentTree Z;

// Initializing
void Initialize() {
	for (int i = 1; i <= N; i++) {
		if (C[i] == 'B') { NumLeft += 1; LeftPos[NumLeft] = i; }
		if (C[i] == 'R') { NumRigt += 1; RigtPos[NumRigt] = i; }
	}
	LeftPos[0] = 0; LeftPos[NumLeft + 1] = N + 1;
	RigtPos[0] = 0; RigtPos[NumRigt + 1] = N + 1;
	reverse(RigtPos, RigtPos + NumRigt + 2);

	// Calculate NextQ
	while ((1 << UpLimit) < N / 2) UpLimit += 1;
	for (int i = 1; i <= UpLimit; i++) {
		Haba[i] = (1 << (i - 1));
	}
	for (int i = 0; i <= UpLimit; i++) {
		for (int j = 0; j <= UpLimit; j++) {
			NextQ[i][j][M + 1] = M + 1;
			for (int k = M; k >= 0; k--) {
				NextQ[i][j][k] = NextQ[i][j][k + 1];
				if (Haba[i] < A[k] && A[k] <= N - Haba[j] && (C[N] == 'R' || A[k] != N)) NextQ[i][j][k] = k; // Changed from uso1_e869120.cpp
			}
		}
	}

	// Calculate Cumulative Sum
	for (int i = 0; i <= UpLimit; i++) {
		SumLeft[i][0] = 0;
		SumRigt[i][0] = 0;
		for (int j = 1; j <= M; j++) {
			SumLeft[i][j] = SumLeft[i][j - 1]; if (A[j] <= Haba[i]) SumLeft[i][j] += A[j];
			SumRigt[i][j] = SumRigt[i][j - 1]; if (N - Haba[i] < A[j]) SumRigt[i][j] += (N - A[j]);
		}
	}
	for (int i = 1; i <= N; i++) {
		SumRed[i] = SumRed[i - 1];
		if (C[i] == 'R') SumRed[i] += 1;
	}
}

// Get number of 'R's when putting ball at place pos
int GetNumR(int cl, int cr, int pos) {
	int val = LeftPos[cl] + (SumRed[RigtPos[cr] - 1] - SumRed[LeftPos[cl]]);
	if (pos != -1) {
		val += pos;
		if (RigtPos[cr] <= pos || (LeftPos[cl] < pos && C[pos] == 'B')) val += 1;
		val %= (N + 1);
	}
	return val;
}

// Answer query [bl, br]
int solve(int bl, int br) {
	int IndexL = 0, LeftLevel = 0;
	int IndexR = 0, RigtLevel = 0;
	int CurrentButton = bl;

	// Repeat Binary Search
	while (true) {
		int Target = min(br + 1, NextQ[LeftLevel][RigtLevel][CurrentButton]);

		// Binary Search
		if (CurrentButton < Target) {
			int cl = CurrentButton, cm, cr = Target;
			int maxn = CurrentButton - 1;
			int maxL = IndexL;
			int maxR = IndexR;
			for (int i = 0; i < 22; i++) {
				cm = (cl + cr) / 2;
				int pos1 = min((long long)NumLeft + 1, IndexL + SumLeft[LeftLevel][cm] - SumLeft[LeftLevel][CurrentButton - 1]);
				int pos2 = min((long long)NumRigt + 1, IndexR + SumRigt[RigtLevel][cm] - SumRigt[RigtLevel][CurrentButton - 1]);
				if (LeftPos[pos1] + 1 < RigtPos[pos2]) {
					if (maxn < cm) { maxn = cm; maxL = pos1; maxR = pos2; }
					cl = cm;
				}
				else {
					cr = cm;
				}
			}

			// When it goes to phase #2
			if (maxn != Target - 1) {
				int StartingPosition = GetNumR(maxL, maxR, A[maxn + 1]);
				return Z.query(maxn + 2, br + 1, StartingPosition);
			}
			CurrentButton = Target;
			IndexL = maxL;
			IndexR = maxR;
		}
		
		// If all query finished
		int CurrentR = GetNumR(IndexL, IndexR, -1);
		if (CurrentButton == br + 1) return CurrentR;

		// Performing "O(1) operation"
		int NewIndexL = IndexL;
		int NewIndexR = IndexR;
		int Change = 0;
		if (RigtPos[IndexR] <= A[CurrentButton] || (LeftPos[IndexL] < A[CurrentButton] && C[A[CurrentButton]] == 'B')) Change = 1;
		if (N - CurrentR >= A[CurrentButton]) NewIndexL += A[CurrentButton] + Change;
		else NewIndexR += (N + 1 - A[CurrentButton]) - Change;

		// When it goes to phase #2
		if (LeftPos[min(NumLeft + 1, NewIndexL)] + 1 >= RigtPos[min(NumRigt + 1, NewIndexR)]) {
			return Z.query(CurrentButton + 1, br + 1, (CurrentR + Change + A[CurrentButton]) % (N + 1));
		}
		IndexR = NewIndexR;
		IndexL = NewIndexL;
		CurrentButton += 1;

		// Update Level
		while (LeftLevel < UpLimit && Haba[LeftLevel + 1] <= LeftPos[IndexL]) LeftLevel += 1;
		while (RigtLevel < UpLimit && Haba[RigtLevel + 1] <= N + 1 - RigtPos[IndexR]) RigtLevel += 1;
	}
}

int main() {
	freopen("machine.in", "r", stdin);
	freopen("machine.out", "w", stdout);
	// Input
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) cin >> C[i];
	for (int i = 1; i <= M; i++) scanf("%d", &A[i]);
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++) scanf("%d%d", &L[i], &R[i]);

	// Precount
	Z.Init(M + 2, N + 1);
	for (int i = 1; i <= M; i++) Z.update(i, A[i]);
	for (int i = Z.size_ - 1; i >= 1; i--) Z.Merge(i);
	Initialize();

	// Answer Query
	for (int i = 1; i <= Q; i++) {
		printf("%d\n", solve(L[i], R[i]));
	}
	return 0;
}
