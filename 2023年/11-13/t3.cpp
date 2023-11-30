#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int x, y, u, v;

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
	read(x), read(y), read(u), read(v);
	read(x), read(y), read(u), read(v);
	if(v == 0) 
		swap(x, u), swap(y, v);
    long double d=acos(-1)/atan2((long double) v, (long double) u);
    cout<<ceil(d-1e-8)-1;
	return 0;
}
