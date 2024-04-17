#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int n, k, ans[15][15];

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
	File("transform");
	ans[1][1]=1;
	ans[2][1]=2, ans[2][2]=3;
	ans[3][1]=3, ans[3][2]=6, ans[3][3]=7;
	ans[4][1]=5, ans[4][2]=15, ans[4][3]=18, ans[4][4]=19;
	ans[5][1]=7, ans[5][2]=31, ans[5][3]=43, ans[5][4]=46, ans[5][5]=47;
	ans[6][1]=11, ans[6][2]=75, ans[6][3]=114, ans[6][4]=126, ans[6][5]=129, ans[6][6]=130;
	ans[7][1]=15, ans[7][2]=164, ans[7][3]=286, ans[7][4]=327, ans[7][5]=339, ans[7][6]=342, ans[7][7]=343;
	ans[8][1]=22, ans[8][2]=388, ans[8][3]=756, ans[8][4]=894, ans[8][5]=935, ans[8][6]=947, ans[8][7]=950, ans[8][8]=951;
	read(n), read(k);
	write(ans[n][k], '\n');
	return 0;
}