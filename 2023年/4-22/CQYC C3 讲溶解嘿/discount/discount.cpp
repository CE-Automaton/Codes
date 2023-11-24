#include <bits/stdc++.h>
#define int long long
using namespace std;
bool st;
const int N = 6e3+5;
int k, n, a[N], rt[N], ans;
struct zhuxi {
	struct node {
		int ls, rs, w;
	}tr[N*15];
	int gs;
	void updt(int &k, int l, int r, int to) {
		++gs, tr[gs]=tr[k], k=gs;
		if(l == r) {
			++tr[k].w;
			return ;
		}
		int mid = ((l+r)>>1);
		if(to <= mid)
			updt(tr[k].ls, l, mid, to);
		else
			updt(tr[k].rs, mid+1, r, to);
		tr[k].w=tr[tr[k].ls].w+tr[tr[k].rs].w;
	}
	int ask(int k1, int k2, int l, int r, int kk) {
		if(l == r) 
			return l;
		int mid = ((l+r)>>1), ll = tr[tr[k2].ls].w-tr[tr[k1].ls].w;
		if(ll < kk)
			return ask(tr[k1].rs, tr[k2].rs, mid+1, r, kk-ll);
		else
			return ask(tr[k1].ls, tr[k2].ls, l, mid, kk);
	}
}A;
struct qwq {
	int w, id;
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
int comp(qwq& C, qwq& B) {
	return C.w > B.w;
} 
bool fn;

signed main() {
	freopen("discount.in", "r", stdin);
	freopen("discount.out", "w", stdout);
//	cerr<<(&st-&fn)*1.0/1024/1024<<"\n";
	read(k), read(n);
	for(int i = 1; i <= k-1; ++i)
		read(a[i]), b[i]=qwq {a[i], i};
	for(int i = 1; i <= n; ++i)
		read(a[i+k-1]), b[i+k-1]=qwq {a[i+k-1], i+k-1};
	sort(b+1, b+n+k, comp);
	for(int j = 1; j <= k+n-1; ++j)
		a[b[j].id]=j;
	for(int i = 1; i <= k+n-1; ++i)
		rt[i]=rt[i-1], A.updt(rt[i], 1, n+k-1, a[i]);
//	cout<<b[A.ask(rt[1-1], rt[2], 1, n+k-1, 2)].w<<"\n"; 
	
	for(int i = 1; i <= n; ++i) {
		for(int j = i; j >= 1; --j) {
			int u = A.ask(rt[j-1], rt[i+k-1], 1, n+k-1, k), o = 0;
//			cout<<j<<"-"<<i+k-1<<" "<<b[u].w<<"!?\n";
			for(int kk = j; kk <= i+k-1; ++kk)
				o=max(o, (b[a[kk]].w^b[u].w));
			ans=max(ans, o);
		}
		write(ans, '\n');
	}
	return 0;
}
