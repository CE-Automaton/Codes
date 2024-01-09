#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
int n, k, a[100005], b[200005], c[200005], nxt[100005];
int upd(int x) {
	return (x < 0 ? x+mod : (x >= mod ? x-mod : x));
}
void read(int& x) {
	x = 0; char c = getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+c-'0', c=getchar();
}
int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	read(n), read(k);
	if(k >= n-1) {
		puts("0");
		return 0;
	}
	for(int i = 1; i <= n; ++i) read(a[i]), a[i]=upd(a[i]);
	for(int i = 1; i <= n; ++i) read(b[i]), b[i]=upd(b[i]), b[i+n]=b[i];
	for(int i = 1; i <= k+1; ++i) {
		for(int j = 2; j <= n-i+1; ++j)
			c[j]=upd(a[j]-a[j-1]);
		for(int j = 1; j <= n-i; ++j)
			a[j]=c[j+1];
	}
	for(int i = 1; i <= k+1; ++i) {
		for(int j = 2; j <= 2*n-i+1; ++j)
			c[j]=upd(b[j]-b[j-1]);
		for(int j = 1; j <= 2*n-i; ++j)
			b[j]=c[j+1];
	}
	for(int i = 2, j = 0; i <= n-k-1; ++i) {
		while(j && a[j+1] != a[i]) j=nxt[j];
		if(a[j+1] == a[i]) ++j; nxt[i]=j;
	}
	for(int i = 1, j = 0; i <= 2*n-k-1; ++i) {
		while(j && a[j+1] != b[i]) j=nxt[j];
		if(a[j+1] == b[i]) ++j;
		if(j == n-k-1) {
			printf("%d\n", i-(n-k-1));
			return 0;
		}
	}
	puts("-1");
	return 0;
}
