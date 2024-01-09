#include <bits/stdc++.h>
using namespace std;
const long double pi=acos(-1);
int t, l, r, n, f[100005], mu[100005], vis[100005], pri[100005], cnt, a, b;
long double haha;
template <typename T> void read(T& x) {
	x = 0; int f = 0; char c = getchar();
	while(c < '0' || c > '9') f |= (c == '-'), c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
	x=(f ? -x : x);
}
int lne; char put[105];
template <typename T> void write(T& x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne--]^48);
}
void solve(int& ret) {
	for(int d = 1; d*d <= l; d+=2) 
		for(int i = 1; i*i <= l/(d*d); ++i) {
			int j = sqrt(l/(d*d)-(i*i));
			ret+=mu[d]*(j+!(i&1))/2;
		}
}
int gcd(int x, int y) {
	int aa = __builtin_ctz(x), bb = __builtin_ctz(y), cc;
	cc=min(aa, bb), y>>=bb;
	while(x) {
		x>>=aa;
		int d = abs(y-x);
		aa=__builtin_ctz(d);
		if(x < y) y=x;
		x=d;
	}
	return (y<<cc);
}

int main() {
	mu[1]=1;
	for(int i = 2; i <= 100000; ++i) {
		if(!vis[i])
			pri[++cnt]=i, mu[i]=-1;
		for(int j = 1; j <= cnt && 1LL*pri[j]*i <= 100000; ++j) {
			vis[i*pri[j]]=1;
			if(i%pri[j] == 0) break;
			mu[i*pri[j]]=-mu[i];
		}
	}
	read(t);
	while(t--) {
		read(l), read(r);
		n=r-l+1;
		for(int i = 1; i <= n; ++i) 
			f[i]=0;
		solve(f[1]);
		for(int i = 1; i*i <= r; ++i) 
			for(int j = sqrt(r-i*i); j >= 1 && i*i+j*j > l; --j)
				if((i*i+j*j)%2 == 1 && gcd(i, j) == 1)
					++f[i*i+j*j-l+1];
		haha=1000000000;
		a=1, b=0; 
		for(int i = 1, now = 0; i <= n; ++i) {
			now+=f[i];
			long double ha = abs((i+l-1)*1.0/now-pi);
			if(ha < haha) {
				int qwq = gcd(i+l-1, now);
				haha=ha;
				a=(i+l-1)/qwq, b=(now)/qwq;
			}
		}
		write(a), putchar(' '), putchar('/'), putchar(' '), write(b), putchar('\n');
	}
	return 0;
}
