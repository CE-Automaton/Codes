#include <iostream>
#include <vector>
using namespace std;

int N; char C[120009];
int M, A[120009];
int Q, L[120009], R[120009];
int IndexL[120009], NumIndexL = 0;
int IndexR[120009], NumIndexR = 0;

int Query(int cl, int cr) {
	int LeftBar = 0;
	int RigtBar = 0;

	// Simulation
	for (int t = cl; t <= cr; t++) {
		int change = 0;
		if (A[t] >= IndexR[RigtBar]) change = 1;
		else if (A[t] > IndexL[LeftBar] && C[A[t]] == 'B') change = 1;

		// Get pos1, pos2
		int pos1 = min(NumIndexL + 1, LeftBar + A[t] + change);
		int pos2 = min(NumIndexR + 1, RigtBar + (N + 1 - A[t]) - change);
		if (IndexL[pos1] < IndexR[RigtBar]) {
			LeftBar = pos1;
		}
		else if (IndexL[LeftBar] < IndexR[pos2]) {
			RigtBar = pos2;
		}
		else {
			int Current = (IndexL[LeftBar] + change) % (N + 1);
			for (int i = IndexL[LeftBar] + 1; i <= IndexR[RigtBar] - 1; i++) {
				if (C[i] == 'R') Current = (Current + 1) % (N + 1);
			}
			Current = (Current + A[t]) % (N + 1);
			for (int i = t + 1; i <= cr; i++) {
				int change = (Current < A[i]);
				Current = (Current + A[i] + change) % (N + 1);
			}
			return Current;
		}
	}

	// All Simulation Finished
	int Answer = IndexL[LeftBar];
	for (int i = IndexL[LeftBar] + 1; i <= IndexR[RigtBar] - 1; i++) {
		if (C[i] == 'R') Answer = (Answer + 1) % (N + 1);
	}
	return Answer;
}

int main() {
	// Input
	cin >> N >> M;
	for (int i = 1; i <= N; i++) cin >> C[i];
	for (int i = 1; i <= M; i++) cin >> A[i];
	cin >> Q;
	for (int i = 1; i <= Q; i++) cin >> L[i] >> R[i];

	// Precount
	for (int i = 1; i <= N; i++) {
		if (C[i] == 'B') { NumIndexL += 1; IndexL[NumIndexL] = i; }
	}
	for (int i = N; i >= 1; i--) {
		if (C[i] == 'R') { NumIndexR += 1; IndexR[NumIndexR] = i; }
	}
	IndexL[0] = 0; IndexL[NumIndexL + 1] = N + 1;
	IndexR[0] = N + 1; IndexR[NumIndexR + 1] = 0;

	// Output
	for (int i = 1; i <= Q; i++) {
		cout << Query(L[i], R[i]) << endl;
	}
	return 0;
}
