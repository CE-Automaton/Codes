#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, q, ans, sum[N], cnt[N], opt[N], m[N], k[N], az[N], ha[N]; 
vector<int> qwq[N];

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
int find(int tt, int ww) {
	int l = 0, r = cnt[tt]-1, ret = q+1;
	while(l <= r) {
		int mid = ((l+r)>>1);
		if(ha[qwq[tt][mid]] >= ww) 
			l=mid+1, ret=qwq[tt][mid];
		else 
			r=mid-1;
	}
	return ret;
}
int ask(int mm, int kk) {
	int tt = mm, ret = q+1;
	#define ooo (tt-mm)*(tt-mm)+kk
	while(tt >= 1 && ooo < N)//平方最大值为1e5,可以直接暴搜 
		ret=min(find(tt, ooo), ret), --tt;
	tt=mm+1;
	while(tt < N && ooo < N) 
		ret=min(find(tt, ooo), ret), ++tt;
	#undef ooo
	return ret;
}

signed main() {
	freopen("two.in", "r", stdin);
	freopen("two.out", "w", stdout);
	read(n), read(q);
	for(int i = 1; i <= n; ++i)
		read(m[i]), read(k[i]);
	for(int i = 1; i <= q; ++i) 
		read(opt[i]), read(az[i]), read(ha[i]);
	for(int i = n; i >= 1; --i)
		if(opt[i] == 1) //加二次函数 
			++sum[i], --sum[ask(az[i], ha[i])];//找到被删的位置,用前缀和存答案 
		else {//加删除操作 
			while(cnt[az[i]] && ha[qwq[az[i]][cnt[az[i]]-1]] <= ha[i])
				--cnt[az[i]]; 
			if(qwq[az[i]].size() <= cnt[az[i]])
				qwq[az[i]].push_back(i);
			else
				qwq[az[i]][cnt[az[i]]]=i;
			++cnt[az[i]];
		}
	for(int i = 1; i <= n; ++i) //对于本来有的二次函数往后找
		++sum[1], --sum[ask(m[i], k[i])];
	for(int i = 1; i <= q; ++i) 
		sum[i]+=sum[i-1], write(sum[i], '\n');
	FastIO::flusher.~Flusher(); 
	return 0 ;
}
