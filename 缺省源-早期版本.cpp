#include <bits/stdc++.h>
//#define mod 1000000007 or 998244353//要取模吗 
//#define inf 1000000007//极值够大吗 
//#define int long long//要开long long吗 
using namespace std;
//题目看对了吗,空间有超吗,数组开的够大吗,下标会是负数吗,operator打对了吗 
template <typename T> 
inline void read(T& x) {
	x=0; int f=1; char c=getchar(); while(c<'0' || c>'9') f=(c == '-' ? -1 : f), c=getchar();
	while('0'<=c && c<='9') x=(x<<1)+(x<<3)+(c^48), c=getchar(); x=x*f;
}
char ot[32]; int ln;
template <typename T> 
inline void write(T x) {
	ln=0; if(x < 0) x=-x, putchar('-');
	do { ot[++ln]=x%10, x/=10; }while(x);
	while(ln) putchar(ot[ln]+'0'), --ln; putchar('\n');
}
//int upd(int x) { return (x >= mod ? x-mod :x); }//加法有都用upd吗,负数有+mod吗,加一个够吗,乘法有*1LL%mod吗 
signed main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	
	return 0;
}
