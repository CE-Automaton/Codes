#include <bits/stdc++.h>
using namespace std;
int n, md, mdd, tot;
long long m, s[45], sum[(1<<20)+5], ans;

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
int erf(long long ss) {
	int l = 1, r = tot, ret = 0;
	while(l <= r) {
		int mid = ((l+r)>>1);
		if(sum[mid] <= ss)
			ret=mid, l=mid+1;
		else
			r=mid-1;
	}
	return ret;
}

signed main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(s[i]);
	md = (n+1)/2;
	mdd=n-md;
	for(int i = 0; i <= (1<<md)-1; ++i) {
		long long now = 0;
		for(int j = 0; j <= md-1; ++j)
			if((i>>j)&1)
				now+=s[j+1];
		sum[++tot]=now;
	}
	sort(sum+1, sum+1+tot);
	for(int i = 0; i <= (1<<mdd)-1; ++i) {
		long long now = 0;
		for(int j = 0; j <= mdd-1; ++j)
			if((i>>j)&1)
				now+=s[j+1+md];
		ans+=erf(m-now);
	}
	write(ans, '\n');
	return 0;
}
