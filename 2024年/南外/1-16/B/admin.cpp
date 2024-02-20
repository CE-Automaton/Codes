#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 10;
const int Mod = 1e9 + 7;
const int D = 3;

struct Vector {
	int a[D];
	int &operator[]( int i ) { return a[i]; }
	const int &operator[]( int i ) const { return a[i]; }
};
struct Matrix {
	int a[D][D];
	void zero(){
		memset( a, 0, sizeof(a) );
	}
	void unit(){
		memset( a, 0, sizeof(a) );
		for( int i = 0; i < D; i++ ) a[i][i] = 1;
	}
	int * operator[]( int i ) { return a[i]; }
	const int * operator[]( int i ) const { return a[i]; }
};
Matrix operator*( const Matrix &r, const Matrix &s ) {
	Matrix rt;
	for( int i = 0; i < D; i++ )
		for( int j = 0; j < D; j++ ) {
			rt[i][j] = 0;
			for( int k = 0; k < D; k++ )
				rt[i][j] = int((rt[i][j] + 1LL * r[i][k] * s[k][j]) % Mod);
		}
	return rt;
}
Vector operator*( const Matrix &r, const Vector &s ) {
	Vector rt;
	for( int i = 0; i < D; i++ ) {
		rt[i] = 0;
		for( int k = 0; k < D; k++ )
			rt[i] = int((rt[i] + 1LL * r[i][k] * s[k]) % Mod);
	}
	return rt;
}

int n, m;
int sep[N];
long long f[N];

Matrix mpow( Matrix a, int b ) {
	Matrix rt;
	for( rt.unit(); b; b>>=1,a=a*a )
		if( b & 1 ) rt = rt * a;
	return rt;
}

int main() {
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	Matrix T1, T2;
	T1.zero(), T2.zero();
	T1[0][0] = T1[0][1] = T1[2][1] = 2;
	T1[0][2] = T1[1][0] = T1[1][1] = T1[2][0] = T1[2][2] = 1;
	T2[0][0] = T2[1][0] = T2[1][1] = T2[2][0] = T2[2][2] = 1;
	T2[2][1] = 2;
	Vector cur;
	cur[0] = 1;
	cur[1] = cur[2] = 0;

	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= m; i++ )  {
		scanf( "%d", sep + i );
		if( sep[i] < 1  || sep[i] >= n ) assert(false);
		if( sep[i] <= sep[i-1] ) assert(false);
	}
	int last = 0;
	for( int i = 1; i <= m; i++ ) {
		cur = mpow(T1,sep[i] - last - 1) * cur;
		cur = T2 * cur;
		last = sep[i];
	}
	cur = mpow(T1,n - last - 1) * cur;
	int ans = int((0LL + cur[0] + cur[1] * 2 + cur[2]) % Mod);
	printf( "%d\n", ans );
}

