#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6+5;
int n, a[N], l[N][25], r[N][25], sum[N][2], ans[2];

namespace FastIO {
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=obuf;
	char* flush(){fwrite(obuf,1,oT-oS,stdout);return oT=obuf;}
	struct Flusher{~Flusher(){flush();}}flusher;
	inline char gc(){return iS==iT && (iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT)?EOF:*iS++;}
	inline void pc(char c){if(oT==oS+SIZE) flush();*oT++=c;}
	template <typename T> void read(T& x) {
		x = 0; int f = 0; char c = gc();
		while(c < '0' || c > '9') f |= (c == '-'), c=gc();
		while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=gc();
		x=(f ? -x : x);
	}
	int lne; char put[105];
	template <typename T> void write(T x, char ch) {
		lne = 0; if(x < 0) pc('-'), x=-x;
		do { put[++lne]=x%10, x/=10; } while(x);
		while(lne) pc(put[lne--]^48);
		pc(ch);
	}
}
using FastIO::gc; using FastIO::pc; using FastIO::read; using FastIO::write;

signed main() {
	freopen("cake.in", "r", stdin);
	freopen("cake.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), a[i+n]=a[i+2*n]=a[i];
//	for(int i = 1; i <= 3*n; ++i) {
//		l[i][0]=a[i];
//		for(int j = 1; j <= 20; ++j)
//			if(i >= (1<<(j-1)))
//				l[i][j]=min(l[i][j-1], l[i-(1<<(j-1))][j-1]);
//			else
//				l[i][j]=l[i][j-1];
//	}
//	for(int i = 3*n; i >= 1; --i) {
//		r[i][0]=a[i];
//		for(int j = 1; j <= 20; ++j)
//			if(i+(1<<(j-1)) <= n)
//				r[i][j]=min(r[i][j-1], r[i+(1<<(j-1))][j-1]);
//			else
//				r[i][j]=r[i][j-1];
//	}
//	for(int i = 1; i <= 3*n; ++i) {
//		int now = (i&1);
//		sum[i][now]=sum[i-1][now]+a[i];
//		sum[i][now^1]=sum[i-1][now^1];
//	} 
	for(int i = 1; i <= n; ++i) {
		int l = n+i-1, r = n+i+1, now = 0;
		ans[0] = ans[1] = 0;
		ans[now]+=a[n+i];
		for(int j = 1; j <= n-1; ++j) {
			now^=1;
			if(a[l] > a[r])
				ans[now]+=a[l], --l;
			else
				ans[now]+=a[r], ++r;
		}
		write(ans[0], '\n');
	}
	return 0;
}
