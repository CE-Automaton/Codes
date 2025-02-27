#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e8+5;
bool st;
int vis[N], pri[N], mul[200005], cnt;
bitset<N> mull;
LL n, k, ans;

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
int mul2(LL x) {
	if(x == 1) return 1;
	for(LL i = 2; i <= x/i; ++i)
		if(x%i == 0) {
			x/=i;
			if(x%i == 0) return 0;
		}
	return 1;
}
bool fn;
signed main() {
	File("mu");
	// debug(1.0*(&st-&fn)/1024/1024, "MB\n");
	read(n), read(k);
	if(n-k <= 500) {
		for(int i = 1; i <= n-k; ++i)
			ans+=mul2(i)*mul2((LL) i+k);
		write(ans, '\n');
		return 0;
	}
	if(n <= 200000000LL) {
		mull[1]=1;
		for(int i = 2; i <= n; ++i) {
			if(!vis[i])
				pri[++cnt]=i, mull[i]=1;
			for(int j = 1; j <= cnt && pri[j] <= n/i; ++j) {
				vis[i*pri[j]]=1;
				if(i%pri[j] == 0) break;
				mull[i*pri[j]]=mull[i];
			}
		}
		mull&=(mull>>k);
		write(mull.count(), '\n');
		return 0;
	}
	return 0;
}
