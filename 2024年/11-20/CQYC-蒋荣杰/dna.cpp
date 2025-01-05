#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 1e6+5;
// bool st;
int n, gs, rt, opt, ll, rr, lll, rrr, fa[N], cnt[N], tot;
vector<int> dd[N*23];//牛魔,空间开不下了,千万别似啊QAQ

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
struct node {
	int ls, rs;
}tr[N*23];//牛魔,空间开不下了,千万别似啊QAQ
int find(int x) {
	return (x == fa[x] ? x : fa[x]=find(fa[x]));
}
void merge(int x, int y) {
	x=find(x), y=find(y);
	if(x == y) return ;
	if(cnt[x] > cnt[y]) swap(x, y);
	cnt[y]+=cnt[x];
	fa[x]=y;
}
struct qwq {
	int blt() {
		++gs;
		tr[gs].ls=tr[gs].rs=0;
		return gs;
	}
	void updt(int &k, int l, int r, int lq, int rq, int op) {
		if(!k) k=blt();
		// debug(l, r, dd[k].size(), lq, rq, op, "?????\n");
		if((tr[k].ls == 0 && tr[k].rs == 0 && dd[k].size()/*和之前的操作合并*/) || (lq <= l && r <= rq)) {
			// debug("!!!!\n");
			if(!dd[k].size())
				dd[k].push_back(op);
			else {
				for(int y = 0; y < dd[k].size(); ++y)
					merge(dd[k][y], op);
				dd[k].clear();//保证时间复杂度?
				dd[k].push_back(op);
			}
			tr[k].ls=tr[k].rs=0;//把下面的操作都覆盖掉
			return ;
		}
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(tr[k].ls, l, mid, lq, rq, op);
		if(mid+1 <= rq)
			updt(tr[k].rs, mid+1, r, lq, rq, op);
		dd[k].push_back(op);//直接push一个op,没必要把修改过的点找出来clear掉,感觉可能时间复杂度是真的
	}
	int ask(int k, int l, int r, int to) {
		if(!k) return 0;
		// debug(l, r, tr[k].ls, tr[k].rs, dd[k].size(), to, "?\n");
		if(tr[k].ls == 0 && tr[k].rs == 0 && dd[k].size()) 
			return dd[k][0];//找到最下面一个操作到了to的区间
		if(l == r)
			return (dd[k].size() ? dd[k][0] : 0);
		int mid = ((l+r)>>1);
		if(to <= mid)
			return ask(tr[k].ls, l, mid, to);
		else
			return ask(tr[k].rs, mid+1, r, to);
	}
}A;
// bool fn;
signed main() {
	File("dna");
	// debug((double) (&fn-&st)*1.0/1024/1024, '\n');
	for(int i = 1; i <= 1000001; ++i)
		fa[i]=i, cnt[i]=1;
	read(n);
	for(int i = 1; i <= n; ++i) {
		read(opt), read(ll), read(rr);
		if(opt == 1) {
			read(lll), read(rrr);
			++tot;
			A.updt(rt, 1, 1000000000, ll, rr, tot);
			A.updt(rt, 1, 1000000000, lll, rrr, tot);
		}
		else {
			ll=A.ask(rt, 1, 1000000000, ll);
			rr=A.ask(rt, 1, 1000000000, rr);
			// debug(ll, rr, "???\n");
			ll=find(ll), rr=find(rr);
			if(ll && rr && ll == rr)
				puts("Yes");
			else
				puts("No");
		}
	}
	// debug(clock(), '\n');
	FastIO::flusher.~Flusher();
	return 0;
}