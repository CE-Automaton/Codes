#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 5e5+5;
int t, n, q, ll[N], rr[N], kk[N], tot, zhan[N], tp[N], l[N], r[N], anss[N];
char s[N];

struct node {
	int w, pd[2];
};
struct tree {
	node tr[N<<2];
	#define ls (k<<1)
	#define rs (ls|1)
	node upup(node l, node r) {
		node ret;
		ret.w=l.w+r.w-(l.pd[1] == r.pd[0]);
		ret.pd[0]=l.pd[0], ret.pd[1]=r.pd[1];
		return ret;
	}
	void built(int k, int l, int r) {
		if(l == r) {
			tr[k] = {1, {(s[l] == 'L' ? 0 : 1), (s[l] == 'L' ? 0 : 1)}};
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		tr[k]=upup(tr[ls], tr[rs]);
	}
	node ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq)
			return tr[k];
		int mid = ((l+r)>>1);
		if(lq <= mid && mid+1 <= rq)
			return upup(ask(ls, l, mid, lq, rq), ask(rs, mid+1, r, lq, rq));
		if(lq <= mid)
			return ask(ls, l, mid, lq, rq);
		else
			return ask(rs, mid+1, r, lq, rq);
	}
}A;
template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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
	File("dream");
	read(t);
	while(t--) {
		read(n);
		scanf("%s", s+1);
		read(q);
		int pd = 1, pdb = 1, gs = 0;
		for(int i = 1; i < n; ++i)
			if(s[i] != s[i+1])
				++gs;
		for(int i = 1; i <= q; ++i) {
			read(ll[i]), read(rr[i]), read(kk[i]);
			pd&=(ll[i] == 1 && rr[i] == n);
			pdb&=(kk[i] == 1);
		}
		if(gs == 0) {//C
			// debug("C!!\n");
			for(int i = 1; i <= q; ++i) 
				write(max(rr[i]-ll[i]+1-kk[i], 0), ' ');
			putchar('\n');
			continue;
		}
		if(gs == 1) {//D
			// debug("D!!\n");
			int fj = 0;
			for(int i = 1; i < n; ++i)
				if(s[i] != s[i+1])
					fj=i;
			for(int i = 1; i <= q; ++i) {
				if(ll[i] <= fj && fj < rr[i])
					write(max(rr[i]-ll[i]+1-min(kk[i], fj-ll[i]+1)-min(kk[i], rr[i]-fj), 0), ' ');
				else
					write(max(rr[i]-ll[i]+1-kk[i], 0), ' ');
			}
			putchar('\n');
			continue;
		}
		if(pdb) {//B
			// debug("B!!\n");
			A.built(1, 1, n);
			for(int i = 1; i <= q; ++i) 
				write(rr[i]-ll[i]+1-A.ask(1, 1, n, ll[i], rr[i]).w, ' ');
			putchar('\n');
			continue;
		}
		if(pd) {//A
			// debug("A!!\n");
			tot=0;
			for(int j = 1; j <= n; ++j) {
				int k = j;
				while(k+1 <= n && s[k+1] == s[j]) ++k;
				zhan[++tot]=k-j+1;
				tp[tot]=(s[j] == 'L' ? 0 : 1);
				j=k;
			}
			for(int j = 0; j <= tot; ++j)
				l[j]=j-1, r[j]=j+1;
			l[0]=tot, r[tot]=0;
			int sum = n;
			for(int k = 0; k <= n; ) {
				if(r[0] == 0) break;
				int mn = 0x3f3f3f3f, gs = 0;
				for(int j = r[0]; j; j=r[j])
					mn=min(mn, zhan[j]), ++gs;
				for(int op = k; op <= k+mn; ++op)
					anss[op]=sum-gs*(op-k);
				for(int j = r[0]; j; j=r[j])
					zhan[j]-=mn, sum-=mn;
				for(int j = r[0]; j; j=r[j])
					if(!zhan[j]) 
						r[l[j]]=r[j], l[r[j]]=l[j];
				for(int j = r[0]; j; j=r[j])
					if(r[j] && tp[j] == tp[r[j]])
						zhan[r[j]]+=zhan[j], r[l[j]]=r[j], l[r[j]]=l[j];
				k+=mn;
			}
			for(int i = 1; i <= q; ++i)
				write(anss[kk[i]], ' ');
			putchar('\n');
			continue;
		}
		for(int i = 1; i <= q; ++i) {
			tot=0;
			for(int j = ll[i]; j <= rr[i]; ++j) {
				int k = j;
				while(k+1 <= rr[i] && s[k+1] == s[j]) ++k;
				zhan[++tot]=k-j+1;
				tp[tot]=(s[j] == 'L' ? 0 : 1);
				j=k;
			}
			for(int j = 0; j <= tot; ++j)
				l[j]=j-1, r[j]=j+1;
			l[0]=tot, r[tot]=0;
			while(kk[i]) {
				if(r[0] == 0) break;
				int mn = 0x3f3f3f3f;
				for(int j = r[0]; j; j=r[j])
					mn=min(mn, zhan[j]);
				if(kk[i] <= mn) 
					mn=kk[i];
				for(int j = r[0]; j; j=r[j])
					zhan[j]-=mn;
				kk[i]-=mn;
				for(int j = r[0]; j; j=r[j])
					if(!zhan[j]) 
						r[l[j]]=r[j], l[r[j]]=l[j];
				for(int j = r[0]; j; j=r[j])
					if(r[j] && tp[j] == tp[r[j]])
						zhan[r[j]]+=zhan[j], r[l[j]]=r[j], l[r[j]]=l[j];
			}
			int sum = 0;
			for(int j = r[0]; j; j=r[j])
				sum+=zhan[j];
			write(sum, ' ');
		}
		putchar('\n');
	}
	debug(clock());
	return 0;
}