#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
// bool st;
const int N = 5e3+5;
int t, n, a[N][N], gs[N], zhan[N], tot, pri[N], vis[N], cnt, len[N];
char s[N][N];
bitset <N> qwq[N], ss;

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
// bool fn;
signed main() {
	File("math");
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
		// if(t == 114-36) {
		// 	debug(n, '\n');
		// 	for(int i = 1; i <= n; ++i, debug('\n'))
		// 		for(int j = 1; j <= n; ++j)
		// 			debug(s[i][j]);
		// }
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				a[i][j]=s[i][j]-'0';
		int pd = 1;
		for(int i = 1; i <= n; ++i) {
			for(int j = i+1; j <= n; ++j)
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
			for(int i = 1; i <= n; ++i)
				for(int j = i+1; j <= n; ++j)
					if(a[i][j] != (__gcd(i,j) == 1))
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
		// for(int i = 1; i <= n; ++i)
		// 	for(int j = i; j <= n; j+=i)
		// 		for(int k = 1; k+j <= n; ++k)
		// 			huo[k][i]|=a[k][k+j];
		// for(int i = 1; i <= n; ++i) 
		// 	for(int j = 1; i+j <= n; ++j)
		// 		for(int k = j; k <= n; k+=j)
		// 			hho[i][k]|=(a[i][i+j]^1);
		// for(int i = 2; i+i <= n; ++i) 
		// 	if(!a[i][i+i]) {
		// 		// debug(i, "???\n");
		// 		for(int j = i; j <= n; j+=i)
		// 			if(huo[j][i])
		// 				pd=0;
		// 	}
		// 	else {
		// 		// debug(i, "!!!\n");
		// 		for(int j = i; j <= n; j+=i)
		// 			if(hho[j][i])
		// 				pd=0;
		// 	}
		// for(int op = 1; op < n; ++op)
		// 	for(int i = 2; op+i <= n; ++i) 
		// 		if(!a[op][op+i]) {
		// 			// debug(i, "???\n");
		// 			for(int j = op; j <= n; j+=i)
		// 				if(huo[j][i])
		// 					pd=0;
		// 		}
		// 		else {
		// 			// debug(i, "!!!\n");
		// 			for(int j = op; j <= n; j+=i)
		// 				if(hho[j][i])
		// 					pd=0;
		// 		}
		for(int i = 1; i <= cnt && pri[i] <= n; ++i) {
			qwq[i].reset();
			len[i]=n-pri[i];
			if(pri[i]*2 <= n)
				qwq[i][0]=a[pri[i]][pri[i]+pri[i]];
			for(int j = 1; j+pri[i] <= n; ++j)
				qwq[i][j]=a[j][j+pri[i]];
		}
		for(int j = 2; j < n; ++j) {
			int mx = n;
			ss.set();
			for(int k = 1; k <= cnt && pri[k] <= j; ++k)
				if(j%pri[k] == 0)
					ss=(ss&qwq[k]), mx=len[k];
			if(j+j <= n && ss[0] != a[j][j+j])
				pd=0;
			for(int i = 1; i+j <= n; ++i)
				pd&=(ss[i] == a[i][i+j]);
			// debug(j, ": ");
			// for(int k = 0; k <= mx; ++k)
			// 	debug(ss[k]);
			// debug("?\n");
			if(mx >= j) {
				int ppd = 0;
				for(int i = 1; i <= j; ++i)
					if(j%i == 0) {
						int now = 1;
						for(int k = i; k <= mx; ++k)
							now&=(ss[k] == ss[k-i]);
						// debug(i, now, "????\n");
						ppd|=now;
					}
				if(!ppd)
					pd=0;
			}
		}
		if(!pd) {
			puts("No");
			continue;
		}
		puts("Yes");
	}
	// debug(clock(), '\n');
	return 0;
}
/*不是哥们，怎么调都过不了第5个大样例的第11个*/