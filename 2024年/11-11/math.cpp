#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e3+5;
int t, n, a[N][N], vis[N], pri[N], cnt, b[N][N];
char s[N][N];

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
int gcd(int x, int y) {
	int aa = __builtin_ctz(x), bb = __builtin_ctz(y), cc;
	cc=min(aa, bb), y>>=bb;
	while(x) {
		x>>=aa;
		int d = abs(y-x);
		aa=__builtin_ctz(d);
		if(x < y) y=x;
		x=d;
	}
	return (y<<cc);
}

signed main() {
	// File("math");
	// debug("memory:", (double) (&st-&fn)*1.0/1024/1024, '\n');
	for(int i = 2; i <= 5000; ++i) {
		if(!vis[i])
			pri[++cnt]=i;
		for(int j = 1; j <= cnt && pri[j] <= 5000/i; ++j) {
			vis[i*pri[j]]=1;
			if(i%pri[j] == 0) break;
		}
	}
	read(t);
	while(t--) {
		read(n);
		for(int i = 1; i <= n; ++i)
			scanf("%s", s[i]+1);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				a[i][j]=s[i][j]-'0', b[i][j]=1;
		int pd = 1;
		for(int i = 1; i <= n && pd; ++i) {
			for(int j = i+1; j <= n && pd; ++j)
				if(a[i][j] != a[j][i])
					pd=0;
			if(i+1 <= n && a[i][i+1] == 0)
				pd=0;
		}
		if(!pd) {
			puts("No");
			continue;
		}
		if(a[1][1] == 1) {//x=0的情况
			for(int i = 1; i <= n && pd; ++i)
				for(int j = i; j <= n && pd; ++j)
					if(a[i][j] != (gcd(i,j) == 1))
						pd=0;
			if(!pd) {
				puts("No");
				continue;
			}
			else {
				puts("Yes");
				continue;
			}
		}
		for(int i = 1; i <= cnt && pri[i] <= n; ++i) {
			int lst = -1;
			for(int j = 1; j+pri[i] <= n; ++j)
				if(!a[j][j+pri[i]]) {
					if(lst == -1)
						lst=j%pri[i];
					else
						if(lst != j%pri[i])
							pd=0/*, debug("1!!!\n")*/;
				}
			// debug(pri[i], lst, "?????\n");
			if(lst == -1) {
				if(pri[i]+pri[i] <= n)
					pd=0/*, debug("2!!!\n")*/;
			}
			else
				for(int j = lst; j+pri[i] <= n; j+=pri[i])
					for(int k = pri[i]; j+k <= n; k+=pri[i])
						b[j][j+k]=0;
		}
		for(int i = 1; i <= n; ++i)
			b[i][i]=0;
		for(int i = 1; i <= n; ++i)
			for(int j = i; j <= n; ++j)
				if(a[i][j] != b[i][j])
					pd=0/*, debug(a[i][j], b[i][j], i, j, "3!!!\n")*/;
		if(pd)
			puts("Yes");
		else
			puts("No");
	}
	// debug(clock(), '\n');
	return 0;
}
/*不是哥们，怎么调都过不了第5个大样例的第11个*/