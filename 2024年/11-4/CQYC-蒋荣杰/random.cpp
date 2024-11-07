#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int n, q, a[N], opt, l, r;
set<int> to[N];

namespace FastIO {
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=obuf;
	char* flush(){fwrite(obuf,1,oT-oS,stdout);return oT=obuf;}
	struct Flusher{~Flusher(){flush();}}flusher;
	inline char gc(){return iS==iT && (iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT)?EOF:*iS++;}
	inline void pc(char c){if(oT==oS+SIZE) flush();*oT++=c;}
	#define getchar gc
	#define putchar pc
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
}
using FastIO::gc;
using FastIO::pc;
using FastIO::read;
using FastIO::write;
int check(int x) {
    auto it = to[x].lower_bound(l);
    if(it == to[x].end() || (*it) > r)
        return 0;
    return 1;
}

signed main() {
    File("random");
	read(n), read(q);
    for(int i = 1; i <= n; ++i)
        read(a[i]), to[a[i]].insert(i);
    for(int i = 1; i <= q; ++i) {
        read(opt), read(l), read(r);
        if(opt == 1)
            to[a[l]].erase(l), a[l]=r, to[r].insert(l);
        else {
            int ans = 0;
            while(check(ans)) ++ans;
            write(ans, '\n');
        }
    }
    // write(clock(), '\n');
    FastIO::flusher.~Flusher();
	return 0;
}