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
long long SumLeft[120009]; vector<int> ListLeft;
long long SumRigt[120009]; vector<int> ListRigt, ListMost;
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

	// Calculate Cumulative Sum
	for (int i = 1; i <= M; i++) {
		SumLeft[i] = SumLeft[i - 1];
		SumRigt[i] = SumRigt[i - 1];
		if (A[i] <= N / 2) { SumLeft[i] += A[i]; ListLeft.push_back(i); }
		if (A[i] > N / 2 && A[i] != N) { SumRigt[i] += (N - A[i]); ListRigt.push_back(i); }
		if (A[i] == N) { ListMost.push_back(i); }
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
	int IndexL = 0, IndexR = 0;
	int CurrentButton = bl;
	vector<int> Cand;
	int pos1 = lower_bound(ListLeft.begin(), ListLeft.end(), bl) - ListLeft.begin();
	int pos2 = lower_bound(ListRigt.begin(), ListRigt.end(), bl) - ListRigt.begin();
	int pos3 = lower_bound(ListMost.begin(), ListMost.end(), bl) - ListMost.begin();
	for (int i = pos1; i < min((int)ListLeft.size(), pos1 + 20); i++) { if (ListLeft[i] <= br) Cand.push_back(ListLeft[i]); }
	for (int i = pos2; i < min((int)ListRigt.size(), pos2 + 20); i++) { if (ListRigt[i] <= br) Cand.push_back(ListRigt[i]); }
	for (int i = pos3; i < min((int)ListMost.size(), pos3 +  1); i++) { if (ListMost[i] <= br) Cand.push_back(ListMost[i]); }
	Cand.push_back(br + 1);
	sort(Cand.begin(), Cand.end());

	// Repeat Binary Search
	for (int i = 0; i < (int)Cand.size(); i++) {
		if (CurrentButton < Cand[i]) {
			int cl = CurrentButton, cm, cr = Cand[i];
			int maxn = CurrentButton - 1;
			int maxL = IndexL;
			int maxR = IndexR;
			for (int i = 0; i < 22; i++) {
				cm = (cl + cr) / 2;
				int pos1 = min((long long)NumLeft + 1, IndexL + SumLeft[cm] - SumLeft[CurrentButton - 1]);
				int pos2 = min((long long)NumRigt + 1, IndexR + SumRigt[cm] - SumRigt[CurrentButton - 1]);
				if (LeftPos[pos1] + 1 < RigtPos[pos2]) {
					if (maxn < cm) { maxn = cm; maxL = pos1; maxR = pos2; }
					cl = cm;
				}
				else {
					cr = cm;
				}
			}

			// When it goes to phase #2
			if (maxn != Cand[i]  - 1) {
				int StartingPosition = GetNumR(maxL, maxR, A[maxn + 1]);
				return Z.query(maxn + 2, br + 1, StartingPosition);
			}
			CurrentButton = Cand[i];
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
	}
}

int main() {
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
