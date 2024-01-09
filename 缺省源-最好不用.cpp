#include <bits/stdc++.h>
#define entr putchar('\n')
#define F(i,l,r) for(int i = l; i r; ++i)
#define R(i,r,l) for(int i = r; i l; --i)
#define RF(i,l,r,j) for(int i = l; i r; i = j)
using namespace std;

inline void read() {}
template <typename T, typename ...T_>
inline void read(T &x, T_ &...p) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x), read(p...);
}
int lne; char put[105];
inline void write() {}
template <typename T, typename ...T_>
inline void write(T x, T_...p) {
	if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
	putchar(' '), write(p...);
}

signed main() {

	return 0;
}
