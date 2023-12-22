#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5, base = 31, mod = 7000007;
int n, b, hs[N];
char s[N];
bitset<mod+5> vv;
bitset<N> pd[1005];

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}

signed main() {
	read(n);
	scanf("%s", s+1);
	b=(int) floor(sqrt((n<<1)))+1;
	for(int i = 1; i <= n; ++i)
		hs[i]=s[i]-'a'+1;
	pd[1].set();
	for(int ans = 2, sum = 0; ans <= b; ++ans) {
		sum+=ans;
		for(int i = n-sum+1; i >= 1; --i) {
			if(pd[ans-1][i+ans])
				vv[hs[i+ans]]=1;
			if(vv[hs[i]] || vv[hs[i+1]])
				pd[ans][i]=1;
		}
		if(pd[ans].none()) {
			write(ans-1, '\n');
			return 0;
		}
		vv.reset();
		for(int j = 1; j <= n-sum+1; ++j)
			hs[j]=upd(1LL*hs[j]*base%mod+s[j+ans-1]-'a'+1);
	}
	write(b, '\n');
	return 0;
}
