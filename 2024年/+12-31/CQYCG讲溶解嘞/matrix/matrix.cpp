#include <bits/stdc++.h>
using namespace std;
int t, h, w;
long long m, ans[15][15]={
{},
{0, 2, 3, 4, 5, 6, 7, 8, 9}, 
{0, 3, 7, 14, 25, 41, 63, 92, 129}, 
{0, 4, 14, 45, 130, 336, 785, 1682, 3351}, 
{0, 5, 25, 130, 650, 2942, 11819, 42305, 136564}, 
{0, 6, 41, 336, 2942, 24520, 183010, 1202234, 6979061}, 
{0, 7, 63, 785, 11819, 183010, 2625117, 33345183, 371484319}, 
{0, 8, 92, 1682, 42305, 1202234, 33345183, 836488618, 18470742266LL}, 
{0, 9, 129, 3351, 136564, 6979061, 371484319, 18470742266LL, 818230288201LL}, 
{0, 10, 175, 6280, 402910, 36211867, 3651371519LL, 358194085968LL, 31887670171373LL}, 
{0, 11, 231, 11176, 1099694, 170079565, 32017940222LL, 6148026957098LL, 1096628939510047LL}
};

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
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	read(t), read(m);
	while(t--) {
		read(h), read(w);
		write(ans[h][w]%m, '\n');
	}
	return 0;
}