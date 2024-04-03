#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
int h, w, s, n, a[8][8], b[8][8], ans, hh[8], l[8], ad;
map <pii, int> aa;

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
	File("snow");
	read(h), read(w);
	n=h*w;
	for(int i = 1; i <= h; ++i)
		for(int j = 1; j <= w; ++j)
			read(a[i][j]), s|=(a[i][j]<<((i-1)*w+j-1)), ad+=a[i][j];
	ans=n;
	for(int i = 0; i < (1<<n); ++i) 
		if((s&i) == s) {
			int now = 0;
			for(int j = 1; j <= h; ++j)
				for(int k = 1; k <= w; ++k)
					b[j][k]=((i>>((j-1)*w+k-1))&1), now += b[j][k];
			int pdd = 1;
			for(int k = 1; k <= w; ++k) 
				l[k]=0;
			aa.clear();
			for(int j = 1; j <= h && pdd; ++j) {
				hh[0]=0;
				for(int k = 1; k <= w; ++k) {
					l[k]+=b[j][k], hh[k]=hh[k-1]+b[j][k];
					if(b[j][k] && aa.find(pii {hh[k], l[k]}) != aa.end()) {
						pdd = 0;
						break;
					}
					aa[pii {hh[k], l[k]}]=1;
				}
			}
			if(pdd) 
				ans=min(ans, now);
		}
	write(ans-ad, '\n');
	return 0;
}