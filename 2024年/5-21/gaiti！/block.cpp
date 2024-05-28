#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 2e5+5;
int n, q, u, v, rt[N], gs, tot;
LL dp[N];
vector <int> to[N];
struct qwq {
	int q, l, r;
}zhan[N];
struct node {
	int ls, rs, w1;
	LL w2, w3;
}tr[N*20];
struct tree {
	void upup(int k) {
		tr[k].w1=(tr[tr[k].ls].w1+tr[tr[k].rs].w1), tr[k].w2=(tr[tr[k].ls].w2+tr[tr[k].rs].w2), tr[k].w3=(tr[tr[k].ls].w3+tr[tr[k].rs].w3);
	}
	void add(int &k, int l, int r, int to, int w1, int w2, int w3) {
		++gs; tr[gs]=tr[k]; k=gs;
		if(l == r) {
			tr[k].w1+=w1, tr[k].w2+=w2, tr[k].w3+=w3;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			add(tr[k].ls, l, mid, to, w1, w2, w3);
		else 
			add(tr[k].rs, mid+1, r, to, w1, w2, w3);
		upup(k);
		return ;
	}
	LL ask(int k, int l, int r, int lq, int rq, int w1, int w2, int w3) {
		if(!k) return 0;
		if(lq <= l && r <= rq) 
			return 1LL*w1*tr[k].w1+w2*tr[k].w2+w3*tr[k].w3;
		int mid = ((l+r)>>1);
		LL ret = 0;
		if(lq <= mid)
			ret=ask(tr[k].ls, l, mid, lq, rq, w1, w2, w3);
		if(mid+1 <= rq)
			ret+=ask(tr[k].rs, mid+1, r, lq, rq, w1, w2, w3);
		return ret;
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
LL que(int l, int r, int lq, int rq, int w1, int w2, int w3) {
	return (r < l || rq < lq ? 0 : A.ask(rt[r], 1, n, lq, rq, w1, w2, w3)-(l == 1 ? 0 : A.ask(rt[l-1], 1, n, lq, rq, w1, w2, w3)));
}
LL F(int l, int r) {
	if(r < l) return inf;
	LL ret = 0;
	ret+=que(1, l, r, n, 1, 0, 0);
	ret+=que(l, n, 1, r, r-l, 1, -1);
	int mid=(l+r)>>1;
	ret+=que(mid+1, r, r+1, n, r+1, -1, 0);
	ret+=que(l+1, mid, r+1, n, -l, 1, 0);
	mid=(l+r+1)>>1;
	ret+=que(1, l-1, l, mid-1, -l+1, 0, 1);
	ret+=que(1, l-1, mid, r-1, r, 0, -1);
	return ret;
}

signed main() {
	File("block");
	read(n), read(q);
	--n;
	for(int i = 1; i <= q; ++i)
		read(u), read(v), --v, to[u].push_back(v);
	for(int i = 1; i <= n; ++i) {
		rt[i]=rt[i-1];
		for(int y : to[i])
			A.add(rt[i], 1, n, y, 1, i, y);
	}
	// for(int i = 1; i <= n; ++i)
	// 	for(int j = i; j <= n; ++j)
	// 		debug(i, j, "?", F(i, j), '\n');
	for(int i = 1; i <= n; ++i)
		dp[i]=inf;
	// debug(dp[1], '\n');
	zhan[++tot]=qwq {0, 1, n};
	int hd = 1;
	for(int i = 1; i <= n; ++i) {
		while(hd <= tot && zhan[hd].r < i) ++hd;
		zhan[hd].l=i;
		// debug(zhan[hd].l, zhan[hd].r, zhan[hd].q, '\n');
		dp[i]=dp[zhan[hd].q]+F(zhan[hd].q+1, i);
		while(hd <= tot && dp[zhan[tot].q]+F(zhan[tot].q+1, zhan[tot].l) >= dp[i]+F(i+1, zhan[tot].l))
			--tot;
		zhan[tot].r=n;
		if(dp[zhan[tot].q]+F(zhan[tot].q+1, zhan[tot].r) < dp[i]+F(i+1, zhan[tot].r)) continue;
		int ans = n-1;
		if(hd <= tot) {
			int l = zhan[tot].l, r = zhan[tot].r-1;
			while(l <= r) {
				int mid = ((l+r)>>1);
				if(dp[zhan[tot].q]+F(zhan[tot].q+1, mid) <= dp[i]+F(i+1, mid)) 
					ans=mid, l=mid+1;
				else 
					r=mid-1;
			}
			zhan[tot].r=ans;
		}
		++tot;
		zhan[tot].q=i, zhan[tot].l=ans+1, zhan[tot].r=n;
	}
	write(dp[n], '\n');
	write(clock(), '\n');
	FastIO::flusher.~Flusher();
	return 0;
}