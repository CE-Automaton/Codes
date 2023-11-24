#include <bits/stdc++.h>
using namespace std;
const int N = 5e4+5;
int n, a[N], mx[1003][1003], q, ll, rr;

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
int merge(int A, int B, int C) {
	if((B <= A && A <= C) || (C <= A && A <= B))
		return A;
	if((A <= B && B <= C) || (C <= B && B <= A))
		return B;
	if((A <= C && C <= B) || (B <= C && C <= A))
		return C;
}

signed main() {
	freopen("math.in", "r", stdin); 
	freopen("math.out", "w", stdout);
	read(n);
	int pd = 1;
	for(int i = 1; i <= n; ++i)
		read(a[i]), pd&=(a[i] <= 1);
	if(n <= 1000) {
		for(int i = 1; i <= n; ++i)
			mx[i][i]=a[i];
		for(int len = 3; len <= n; len+=2) 
			for(int i = 1; i+len-1 <= n; ++i) {
				int j = i+len-1;
				for(int l = 1; l+2 <= len; l+=2)
					for(int r = 1; l+r+1 <= len; r+=2) 
						mx[i][j]=max(mx[i][j], merge(mx[i][i+l-1], mx[i+l][i+l+r-1], mx[i+l+r][j]));
			}
		read(q);
		for(int i = 1; i <= q; ++i) {
			read(ll), read(rr);
			write(mx[ll][rr], '\n');
		}
	}
	else {
		if(pd) {
			read(q);
			for(int i = 1; i <= q; ++i) {
				read(ll), read(rr);
				if(ll == rr) 
					write(a[ll], '\n');
				else {
					if(a[ll] == 1 && a[rr] == 1)
						write(1, '\n');
					else {
						if(merge(a[ll], a[ll+1], a[ll+2]) == 1 && merge(a[rr], a[rr-1], a[rr-2]) == 1)
							write(1, '\n');
						else
							write(0, '\n');
					}
				}
			}
		}
	}
	return 0;
}
