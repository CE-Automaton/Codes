#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef pair <int,int> pii;
const int N = (1<<11)+1;
int n, m;
bitset<N> b[2][N], a[N], s;
vector <pii> ans;

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
	read(n);
	n=(1<<n);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			read(m), b[0][i][j]=a[i][j]=m;
	int now = 1;
	for(int o = 1; o < n-1; ++o, now^=1) 
		for(int i = 0; i < n; ++i) {
			b[now][i]=a[i];
			b[now][i]^=b[now^1][(i == n-1 ? 0 : i+1)];
			b[now][i]^=b[now^1][(i == 0 ? n-1 : i-1)];
			s=(b[now^1][i]<<1);
			s[0]=b[now^1][i][n-1];
			b[now][i]^=s;
			s=(b[now^1][i]>>1);
			s[n-1]=b[now^1][i][0];
			b[now][i]^=s;
		}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if(b[now][i][j])
				ans.push_back(pii {i, j});
	write(ans.size(), '\n');
	for(pii y : ans)
		write(y.first, ' '), write(y.second, '\n');
	return 0;
}