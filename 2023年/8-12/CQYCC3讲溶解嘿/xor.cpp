#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, q, w, c, tot, opt, haha[1000005], to[N];
struct qwq {
	int w, c;
}az[N];

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
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	read(q);
	for(int i = 1; i <= q; ++i) {
		read(opt);
		if(opt == 1) {
			read(w), read(c);
			for(int i = 0; i <= (1<<n)-1; ++i)
				haha[i|(1<<n)]=(haha[i]^c);
			az[++n]=qwq {w, c};
			to[i]=n;
//			for(int i = 0; i <= (1<<n)-1; ++i) 
//				if(haha[i] == 0)
//					for(int j = 1; j <= n; ++j)
//						if((i>>(j-1))&1)
//							az[j].w=0;
		}
		else {
			read(c);
			c=to[c];
			for(int i = 0; i <= (1<<n)-1; ++i)
				if((i>>(c-1))&1)
					haha[i]=(haha[i]^az[c].c);
			az[c].c=0;
			az[c].w=0;
//			for(int i = 0; i <= (1<<n)-1; ++i) 
//				if(haha[i] == 0)
//					for(int j = 1; j <= n; ++j)
//						if((i>>(j-1))&1)
//							az[j].w=0;
		}
		int ans = 0;
		for(int i = 0; i <= (1<<n)-1; ++i) {
			if(haha[i] == 0) continue;
			int sum = 0, op = 0;
			for(int j = 1; j <= n; ++j)
				if((i>>(j-1))&1)
					sum+=az[j].w;
			for(int j = (i-1)&i; j; j=((j-1)&i))
				if(haha[j] == 0)
					op|=j;
			for(int j = 1; j <= n; ++j)
				if((op>>(j-1))&1)
					sum-=az[j].w;
			ans=max(ans, sum);
		}
		write(ans, '\n');
	}
	return 0;
}
