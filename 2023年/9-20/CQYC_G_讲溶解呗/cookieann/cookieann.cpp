#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int t, n, a[N], tot, pd[N][2], ans;
struct qwq {
	int w, t;
}b[N];

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
int check() {
	for(int i = 1; i <= n; ++i)
		pd[i][0]=pd[i][1]=0;
	tot=0;
	for(int i = 1; i <= n; ++i)
		if(a[i] >= a[1])
			b[++tot]=qwq{a[i], i};
	if(tot == 1) {
		for(int o = b[1].t; o <= n; ++o)
			pd[o][0]=1;
	}
	else {
		for(int i = 2; i <= tot; ++i) 
			if(b[i].w < b[i-1].w) {
				int pdd = 1;
				for(int j = i; j+1 <= tot; ++j)
					if(b[j].w < b[j+1].w) {
						pdd=0;
						break;
					}
				if(pdd) 
					for(int o = b[i-1].t+1; o <= b[i].t; ++o)
						pd[o][0]=1;
				else
					return 0;
				break;
			}
			else
				if(i == tot)
					for(int o = b[i].t; o <= n; ++o)
						pd[o][0]=1;
	}

	tot=0;
	for(int i = 1; i <= n; ++i)
		if(a[i] < a[1])
			b[++tot]=qwq{a[i], i};
	if(tot) {
		if(tot == 1) {
			for(int o = b[1].t; o <= n; ++o)
				pd[o][1]=1;
		}
		else {
			for(int i = 2; i <= tot; ++i) 
				if(b[i].w > b[i-1].w) {
					int pdd = 1;
					for(int j = i; j+1 <= tot; ++j)
						if(b[j].w > b[j+1].w) {
							pdd=0;
							break;
						}
					if(pdd) 
						for(int o = b[i-1].t+1; o <= b[i].t; ++o)
							pd[o][1]=1;
					else
						return 0;
					break;
				}
				else
					if(i == tot)
						for(int o = b[i].t; o <= n; ++o)
							pd[o][1]=1;
		}
	}
	else
		for(int o = 1; o <= n; ++o)
			pd[o][1]=1;
	int ppd = 0;
	for(int i = 1; i <= n; ++i)
		ppd|=(pd[i][0]&pd[i][1]);
	return ppd;
}

signed main() {
	freopen("cookieann.in", "r", stdin);
	freopen("cookieann.out", "w", stdout);
	read(t);
	while(t--) {
		read(n);
		ans=0;
		for(int i = 1; i <= n; ++i)
			read(a[i]);
		ans|=check();
		for(int i = 1; i*2 <= n; ++i)
			swap(a[i], a[n-i+1]);
		ans|=check();
		if(ans)
			puts("yes");
		else
			puts("no");
	}
	return 0;
}
