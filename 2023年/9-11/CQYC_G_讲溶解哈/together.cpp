#include <bits/stdc++.h>
#define mod 4294967296LL
using namespace std;
const int N = 3e5+5;
int n, m, a[N], b[N], opt, ll, rr;
unsigned int ans[5005][5005], sans[5005][5005];
struct node {
	int ls, rs, a, idd, b, siz;
	unsigned int sum;
}tr[N];
struct tree {
	int rt, gs;
	int addnode(int i) {
		++gs;
		tr[gs].ls=tr[gs].rs=0;
		tr[gs].a=a[i];
		tr[gs].sum=tr[gs].b=b[i];
		tr[gs].idd=i;
		tr[gs].siz=1;
		return gs;
	}
	void upup(int x) {
		tr[x].siz=tr[tr[x].ls].siz+tr[tr[x].rs].siz+1;
		tr[x].sum=tr[tr[x].ls].sum+tr[tr[x].rs].sum+((unsigned int) tr[x].b*tr[x].siz);
	}
	int merge(int x, int y) {
		if(!x || !y)
			return (x|y);
		if(tr[x].a < tr[y].a) {
			if(tr[x].idd < tr[y].idd) 
				tr[y].ls=merge(x, tr[y].ls);
			else
				tr[y].rs=merge(x, tr[y].rs);
			upup(y);
			return y;
		}
		else {
			if(tr[y].idd < tr[x].idd) 
				tr[x].ls=merge(y, tr[x].ls);
			else
				tr[x].rs=merge(y, tr[x].rs);
			upup(x);
			return x;
		}
	}
	void insertt(int i) {
		rt=merge(rt, addnode(i));
	}
}A;

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

signed main() {
	freopen("together.in", "r", stdin);
	freopen("together.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i)
		read(a[i]);
	for(int i = 1; i <= n; ++i)
		read(b[i]);
	for(int i = 1; i <= n; ++i) {
		A.gs=0;
		A.rt=A.addnode(i);
		sans[i][i]=ans[i][i]=tr[A.rt].sum;
		for(int j = i+1; j <= n; ++j) {
			A.insertt(j);//有点难跑过5000?希望能跑吧 
			ans[i][j]=tr[A.rt].sum;
		}
	}
	for(int len = 2; len <= n; ++len)
		for(int i = 1, j = len; j <= n; ++i, ++j)
			sans[i][j]=sans[i+1][j]+sans[i][j-1]-sans[i+1][j-1]+ans[i][j];
	for(int i = 1; i <= m; ++i) {
		read(opt), read(ll), read(rr);
		if(opt == 1) 
			write((unsigned int) 114514*ans[ll][rr], '\n');
		else
			write((unsigned int) 114514*sans[ll][rr], '\n');
	}
	FastIO::flusher.~Flusher();
	return 0;
}
