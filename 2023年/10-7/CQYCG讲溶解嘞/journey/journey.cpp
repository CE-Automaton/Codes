#include <bits/stdc++.h>
#define pi pair<int, int>
using namespace std;
const int N = 1e3+5, M = 2e5+5, Q = 1e6+5;
int n, m, q, u[M], v[M], dp[N][N], A, B, C, D, ans[Q];
struct qwq {
	int l, u, v, d;
};
vector <qwq> pro[M];

namespace FastIO {
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=obuf;
	char* flush(){fwrite(obuf,1,oT-oS,stdout);return oT=obuf;}
	struct Flusher{~Flusher(){flush();}}flusher;
	inline char gc(){return iS==iT && (iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT)?EOF:*iS++;}
	inline void pc(char c){if(oT==oS+SIZE) flush();*oT++=c;}
	#define getchar gc
	#define putchar pc
	template <typename T> void read(T& x) {
		x = 0; int f = 0; char c = getchar();
		while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
		while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
		x=(f ? -x : x);
	}
	int lne; char put[105];
	template <typename T> void write(T x, char ch) {
		lne = 0; if(x < 0) putchar('-'), x=-x;
		do { put[++lne]=x%10, x/=10; } while(x);
		while(lne) putchar(put[lne--]^48);
		putchar(ch);
	}
}
using FastIO::gc;
using FastIO::pc;
using FastIO::read;
using FastIO::write;

signed main() {
	freopen("journey.in", "r", stdin);
	freopen("journey.out", "w", stdout);
	read(n), read(m), read(q);
	for(int i = 1; i <= m; ++i)
		read(u[i]), read(v[i]);
	for(int i = 1; i <= q; ++i) {
		read(A), read(B), read(C), read(D);
		if(C == D)
			ans[i]=1;
		else
			pro[B].push_back(qwq {A, C, D, i});
	}
	for(int i = 1; i <= m; ++i) {
		for(int j = 1; j <= n; ++j)
			if(j != u[i] && j != v[i]) {
				int ww = max(dp[j][v[i]], dp[j][u[i]]);
				dp[j][v[i]]=dp[j][u[i]]=ww;
			}
		dp[u[i]][v[i]]=dp[v[i]][u[i]]=i;
		for(qwq az : pro[i])
			if(dp[az.u][az.v] >= az.l)
				ans[az.d]=1;
	}
	for(int i = 1; i <= q; ++i)
		if(ans[i])
			putchar('Y'), putchar('e'), putchar('s'), putchar('\n');
		else
			putchar('N'), putchar('o'), putchar('\n');
	FastIO::flusher.~Flusher();
	return 0;
}
