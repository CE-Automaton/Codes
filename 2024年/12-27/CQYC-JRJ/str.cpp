#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int n, m, typ, opt, ll, rr, lst;
string s[55], t;

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
int check(int x) {
	for(int i = ll; i <= rr; ++i)
		if(x > s[i].size()) return 0;
	for(int i = ll+1; i <= rr; ++i)
		if(s[i][x-1] != s[i-1][x-1]) return 0;
	return 1;
}

signed main() {
	File("str");
	read(n), read(m), read(typ);
	for(int i = 1; i <= n; ++i)
		cin>>s[i];
	for(int i = 1; i <= m; ++i) {
		read(opt), read(ll), read(rr);
		if(opt == 1) {
			ll^=lst, rr^=lst;
			cin>>t;
			for(int j = ll; j <= rr; ++j)
				s[j]=t+s[j];
		}
		else {
			lst=0;
			while(check(lst+1))
				++lst;
			write(lst, '\n');
			lst*=typ;
		}
	}
	return 0;
}