#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;

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
	string nam;
	cin>>nam;
	while(1) {
		string now;
		cin>>now;
		string s = nam+".exe<"+nam+now+".in>"+nam+".ans";
		double t1 = clock();
		system(s.c_str());
		double t2 = clock();
		string ss = "fc "+nam+now+".out "+nam+".ans";
		if(system(ss.c_str())) 
			break;
		printf("%.3lf\n", 1.0*(t2-t1)/1000);
	}
	return 0;
}
