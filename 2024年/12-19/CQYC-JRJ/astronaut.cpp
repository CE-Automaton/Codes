#include <bits/stdc++.h>
#define inf 10007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e3+5, mod=1000000007;
int n, s[N], ss[N], t[N<<1], len[N<<1], ans;

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
void sol() {
	for(int i = 1; i <= n; ++i) t[i*2]=s[i], t[i*2-1]=-1;//马拉车
	t[2*n+1]=t[0]=-1, len[0]=len[1]=1;
	int mid=1, mr=2;
	for(int i = 2; i <= 2*n+1; ++i) {
		if(i >= mr) len[i]=1;
		else len[i]=min(len[mid*2-i], mr-i);
		while(t[i+len[i]] == t[i-len[i]]) ++len[i];
		if(i+len[i] > mr) {
			mr=i+len[i];
			mid=i;
		}
	}
	for(int i = 1; i <= 2*n+1; ++i)
		ans=max(ans, (len[i]*2-1)/2);
}

signed main() {
	File("astronaut");
	read(n);
	int pd = 1;
	for(int i = 1; i <= n; ++i)
		read(s[i]), ss[i]=s[i], pd&=(i == 1 || s[i] >= s[i-1]);
	sol();
	if(pd) {
		write(ans, '\n');
		return 0;
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = i+1; j <= n; ++j) {
			for(int k = j-1; k >= i; --k)
				if(s[k] > s[k+1]) swap(s[k], s[k+1]);
				else break;
			sol();
		}
		for(int j = i; j <= n; ++j)
			s[j]=ss[j];
	}
	write(ans, '\n');
	return 0;
}