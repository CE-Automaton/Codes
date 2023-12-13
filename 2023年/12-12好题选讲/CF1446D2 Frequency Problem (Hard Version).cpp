#include <bits/stdc++.h>
using namespace std;
const int N = 4e5+5;
int n, B, a[N], ton[N], op[N], mx, ans;

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
	B=(int) sqrt(n);
	for(int i = 1; i <= n; ++i)
		read(a[i]), ++ton[a[i]];
	for(int i = 1; i <= n; ++i)
		if(ton[mx] < ton[i])
			mx=i;
	for(int i = 1; i <= n; ++i)
		if(ton[i] >= B) {
			for(int j = 0; j <= n*2; ++j)
				op[j]=0;
			for(int j = 1, w = 0; j <= n; ++j) {
				w+=(a[j] == mx ? 1 : (a[j] == i ? -1 : 0));
				if(!op[w+n] && w != 0)
					op[w+n]=j;
				else
					ans=max(ans, j-op[w+n]);
			}
		}
	for(int i = 1; i < B; ++i) {
		for(int j = 1; j <= n; ++j) 
			ton[j]=0;
		int l = 1, cnt = 0;
		for(int j = 1; j <= n; ++j) {
			++ton[a[j]];
			if(ton[a[j]] == i)
				++cnt;
			while(l <= j && ton[a[j]] > i) {
				if(ton[a[l]] == i)
					--cnt;
				--ton[a[l]], ++l;
			}
			if(cnt >= 2)
				ans=max(ans, j-l+1);
		}
	}
	write(ans, '\n');
	return 0;
}
