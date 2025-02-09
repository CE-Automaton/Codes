#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int n, kk[N], q, cc, zhan[N], tot, gs, sss[N], cnt, to[N];
LL ans, gsl, b[N], bs;
vector <int> a[N], l[N], r[N];
struct qwq { int a, b, c; } ls[N], ad[N];

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
int comp(qwq A, qwq B) {
	return A.c < B.c;
}

signed main() {
	File("list");
	read(n);
	int ttt = 0;
	for(int i = 1; i <= n; ++i) {
		read(kk[i]);
		gs+=kk[i];
		gsl+=kk[i];
		a[i].resize(kk[i]+5);
		l[i].resize(kk[i]+5);
		r[i].resize(kk[i]+5);
		for(int j = 1; j <= kk[i]; ++j)
			read(a[i][j]), ls[++ttt]=qwq {i, j, a[i][j]}, 
			l[i][j]=j-1, r[i][j]=j+1;
		for(int j = 2; j <= kk[i]; ++j)
			ad[++q]=qwq {i, j, a[i][j]-a[i][j-1]+1};
	}
	read(cc);
	for(int i = 1; i <= n; ++i)
		read(b[i]), b[i]=1LL*i*b[i];
	sort(ls+1, ls+1+ttt, comp);
	sort(ad+1, ad+1+q, comp);
	for(int i = 1; i <= ttt; ++i) {
		if(i == 1 || ls[i].c != ls[i-1].c)
			to[++cnt]=ls[i].c;
		a[ls[i].a][ls[i].b]=cnt;
		++sss[cnt];
	}
	for(int i = 1; i <= ttt; ++i)
		bs+=b[sss[i]];
	ans=bs+1LL*cc*gsl;
	zhan[++tot]=1;
	// debug(1, "!", ans, "\n");
	for(int i = 1; i <= q; ++i) {
		int j = i;
		while(j+1 <= q && ad[j+1].c == ad[i].c)
			++j;
		for(int k = i; k <= j; ++k) {
			int xx = ad[k].a, yy = ad[k].b;
			bs-=b[sss[a[xx][yy]]];
			--sss[a[xx][yy]];
			bs+=b[sss[a[xx][yy]]];
			gsl-=to[a[xx][yy-1]]-to[a[xx][l[xx][yy]]]+1+to[a[xx][r[xx][yy]-1]]-to[a[xx][yy]]+1;
			gsl+=to[a[xx][r[xx][yy]-1]]-to[a[xx][l[xx][yy]]]+1;
			l[xx][r[xx][yy]]=l[xx][yy];
			r[xx][l[xx][yy]]=r[xx][yy];
			--gs;
		}
		// debug(gsl, gs, "???\n");
		LL now = bs+1LL*cc*(gsl+1LL*gs*(ad[i].c-1));
		// debug(ad[i].c, "!", now, "\n");
		if(now < ans)
			ans=now, tot=0;
		if(now == ans)
			zhan[++tot]=ad[i].c;
		i=j;
	}
	write(ans, ' '), write(tot, '\n');
	for(int i = 1; i <= tot; ++i)
		write(zhan[i], ' ');
	FastIO::flusher.~Flusher();
	return 0;
}