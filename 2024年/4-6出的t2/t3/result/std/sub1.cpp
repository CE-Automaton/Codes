#include <iostream>
using namespace std;

int N; char C[120009], D[120009];
int M, A[120009];
int Q, L[120009], R[120009];

int Simulation(int cl, int cr) {
	// Initialize
	for (int i = 1; i <= N; i++) D[i] = C[i];
	
	// Main
	for (int i = cl; i <= cr; i++) {
		int cx = A[i]; D[cx] = 'R';
		while (cx >= 1 && cx <= N) {
			if (D[cx] == 'B') { D[cx] = 'R'; cx -= 1; }
			else { D[cx] = 'B'; cx += 1; }
		}
	}
	
	// Return Answer
	int Answer = 0;
	for (int i = 1; i <= N; i++) {
		if (D[i] == 'R') Answer += 1;
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
	
	// Output
	for (int i = 1; i <= Q; i++) {
		cout << Simulation(L[i], R[i]) << endl;
	}
	return 0;
}
