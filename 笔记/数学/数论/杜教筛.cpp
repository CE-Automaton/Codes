#include <bits/stdc++.h>
using namespace std;
const int B = 1664511;
int t, n, mul[B+5], o[B+5], vis[B+5], pri[B+5], cnt;
unordered_map <int, long long> summul, sumo;
long long get_mul(int x) {
	if(summul.find(x) != summul.end()) return summul[x];
	long long ret = 1;
	for(int l = 2, r = 0; 1LL*r+1 <= x; l=r+1) {
		r=x/(x/l);
		ret-=1LL*(r-l+1)*get_mul(x/l);
	}
	return summul[x]=ret;
}
long long get_o(int x) {
	if(sumo.find(x) != sumo.end()) return sumo[x];
	long long ret = 1LL*x*(1LL*x+1)/2;
	for(int l = 2, r = 0; 1LL*r+1 <= x; l=r+1) {
		r=x/(x/l);
		ret-=1LL*(r-l+1)*get_o(x/l);
	}
	return sumo[x]=ret;
}

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
	read(t);
	mul[1]=o[1]=1;
	for(int i = 2; i <= B; ++i) {
		if(!vis[i]) pri[++cnt]=i, o[i]=i-1, mul[i]=-1;
		for(int j = 1; j <= cnt && 1LL*pri[j]*i <= B; ++j) {
			vis[pri[j]*i]=1;
			if(i%pri[j] == 0) {
				o[pri[j]*i]=o[i]*pri[j];
				break;
			}
			o[pri[j]*i]=o[i]*(pri[j]-1);
			mul[pri[j]*i]=-mul[i];
		}
	}
	long long oo = 0;
	for(int i = 1; i <= B; ++i)
		oo+=mul[i], summul[i]=oo;
	oo=0;
	for(int i = 1; i <= B; ++i)
		oo+=o[i], sumo[i]=oo;
	while(t--) {
		read(n);
		write(get_o(n), ' ');
		write(get_mul(n), '\n');
	}
	return 0;
}
