#include <bits/stdc++.h>
#define int long long
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e3+5;
int k, a, b, p, kk, n, tot, A[31], now;
struct qwq {
	int x, y, z;
}zhan[N];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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

signed main() {
	File("myth");
	read(k);
	if(k == (k&(-k))) {
		puts("-1");
	}
	a=(k&(-k));
	b=(k-a);
	p=k/a-1;
	if(k <= 1000) {
		zhan[++tot]=qwq {0, 1, a};
		zhan[++tot]=qwq {0, 2, b};
		zhan[++tot]=qwq {0, 3, a};
		kk=0;
		now=3;
		int nw = 1;
		while(p) {
			kk=(kk+a+a)%k;
			zhan[++tot]=qwq {nw, now+1, (k-kk)};
			++now;
			zhan[++tot]=qwq {nw, now+1, kk};
			++now;
			p-=2;
			nw=(nw == 1 ? 3 : 1);
		}
		write(tot+1, '\n');
		for(int i = 1; i <= tot; ++i)
			write((zhan[i].x == 0 ? now+1 : zhan[i].x), ' '), write(zhan[i].y, ' '), write(zhan[i].z, '\n');
		return 0;
	}
	else {
		zhan[++tot]=qwq {0, 1, a};
		zhan[++tot]=qwq {0, 2, b};
		zhan[++tot]=qwq {0, 3, a};
		zhan[++tot]=qwq {1, 4, (b+b)%k};
		zhan[++tot]=qwq {1, 5, (a+a)%k};
		A[2]=5;
		zhan[++tot]=qwq {3, 6, 4*b%k};
		zhan[++tot]=qwq {3, 7, 4*a%k};
		zhan[++tot]=qwq {1, 8, 6*b%k};
		zhan[++tot]=qwq {1, 9, 6*a%k};
		A[3]=9;
		zhan[++tot]=qwq {2, 10, 6*b%k};
		zhan[++tot]=qwq {3, 11, 6*a%k};
		now=11;
		kk=(6*a)%k;
		int i = 4;
		for(; i <= 29 && (1<<i) <= p; ++i) {
			kk=(kk+(1<<(i-2))*a%k)%k;
			zhan[++tot]=qwq {A[i-2], now+1, k-kk};
			++now;
			zhan[++tot]=qwq {A[i-2], now+1, kk};
			++now;
			kk=(kk+(1<<(i-2))*a%k)%k;
			zhan[++tot]=qwq {3, now+1, k-kk};
			++now;
			zhan[++tot]=qwq {3, now+1, kk};
			++now;
			zhan[++tot]=qwq {2, now+1, k-kk};
			++now;
			zhan[++tot]=qwq {1, now+1, kk};
			++now;
			A[i]=now;
			zhan[++tot]=qwq {2, now+1, k-kk};
			++now;
			zhan[++tot]=qwq {3, now+1, kk};
			++now;
		}
	}
	return 0;
}