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
		D[A[i]] = 'R';
		int cnt = 0;
		for (int j = 1; j <= N; j++) {
			if (D[j] == 'B') cnt += 1;
		}
		
		// If ball goes left
		if (cnt >= A[i]) {
			int rem = A[i];
			for (int j = 1; j <= N; j++) {
				if (D[j] == 'B') { rem -= 1; D[j] = 'R'; }
				if (rem == 0) break;
			}
		}
		
		// If ball goes right
		if (cnt < A[i]) {
			int rem = N + 1 - A[i];
			for (int j = N; j >= 1; j--) {
				if (D[j] == 'R') { rem -= 1; D[j] = 'B'; }
				if (rem == 0) break;
			}
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
