#include <bits/stdc++.h>
using namespace std;
const int N = 2e3+5;
int n, ls, lt, up[N];
long long ans;
char s[N][N];

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
	for(int i = 1; i <= n; ++i)
		scanf("%s", s[i]+1);
	for(int i = 1; i <= n; ++i) {
		ls=lt=0; 
		for(int j = 1; j <= n; ++j) {
			if(s[i][j] == 'o')
				ans+=(long long) up[j]*ls+lt, ++ls, lt+=up[j], 
				++up[j];
		}
	}
	for(int i = 1; i <= n; ++i)
		up[i]=0; 
	for(int i = n; i >= 1; --i) {
		ls=lt=0; 
		for(int j = n; j >= 1; --j) {
			if(s[i][j] == 'o')
				ans+=(long long) up[j]*ls+lt, ++ls, lt+=up[j], 
				++up[j];
		}
	}
	write(ans, '\n');
	return 0;
}
