#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n, sum[N], ans;
char s[N];

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
int f(int g) {
	int cnt = 0, mn = 0;
	for(int i = 1; i <= n; ++i) {
		if(s[i] == '1')
			++cnt;
		else if(s[i] == '0')
			--cnt;
		else {
			if(cnt+sum[i+1]+1 <= g)
				++cnt;
			else
				--cnt;
		}
		mn=min(mn, cnt);
	}
	return g-mn;
}

signed main() {
	scanf("%s", s+1);
	n=strlen(s+1);
	for(int i = n; i >= 1; --i)
		sum[i]=max(sum[i+1]+(s[i] == '1' ? 1 : -1), 0);
	ans=min(f(sum[1]), f(sum[1]+1));
	write(ans, '\n');
	return 0;
}
