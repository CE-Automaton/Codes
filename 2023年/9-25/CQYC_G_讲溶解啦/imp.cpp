#include <bits/stdc++.h>
#define int long long
#define inf 100000000000000000LL
using namespace std;
const int N = 5e5+5;
int n, xx[N], yy[N], cc[N], cnt, to[N], ans;
struct qwq {
	int w, t, op;
}zhan[N];
struct tree {
	int tr[N<<2]/*dp的最大值*/, ww[N<<2]/*w+min(x,y)的最大值*/, mx[N<<2]/*max(x,y)*/, lzy[N<<2], pd[N<<2], lzyad[N<<2];
	#define ls (k<<1)
	#define rs ((k<<1)|1)
	void upup(int k) {
		tr[k]=max(tr[ls], tr[rs]);
		ww[k]=max(ww[ls], ww[rs]);
		mx[k]=max(mx[ls], mx[rs]);
	} 
	void down(int k) {
		if(lzyad[k] != 0) {
			ww[ls]+=lzyad[k];
			tr[ls]+=lzyad[k];
			lzyad[ls]+=lzyad[k];
			
			ww[rs]+=lzyad[k];
			tr[rs]+=lzyad[k];
			lzyad[rs]+=lzyad[k];
			
			lzyad[k]=0;
		}
		if(pd[k]) {
			mx[ls]=lzy[k];
			tr[ls]=ww[ls]-mx[ls];
			lzy[ls]=lzy[k];
			pd[ls]=1;
			
			mx[rs]=lzy[k];
			tr[rs]=ww[rs]-mx[rs];
			lzy[rs]=lzy[k];
			pd[rs]=1;
			
			lzy[k]=-inf;
			pd[k]=0;
		}
	}
	void built(int k, int l, int r) {
		pd[k]=0;
		lzyad[k]=0;
		if(l == r) {
			tr[k]=to[l]-inf;
			mx[k]=-inf;
			ww[k]=to[l];
			return ;
		}
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
		upup(k); 
	}
	void updt(int k, int l, int r, int lq, int rq, int mxx) {
		if(lq <= l && r <= rq) {
			lzy[k]=mx[k]=mxx;
			tr[k]=ww[k]-mx[k];
			pd[k]=1;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updt(ls, l, mid, lq, rq, mxx);
		if(mid+1 <= rq)
			updt(rs, mid+1, r, lq, rq, mxx);
		upup(k);
	}
	void updtad(int k, int l, int r, int lq, int rq, int ad) {
		if(lq <= l && r <= rq) {
			tr[k]+=ad;
			ww[k]+=ad;
			lzyad[k]+=ad;
			return ;
		}
		down(k);
		int mid = ((l+r)>>1);
		if(lq <= mid)
			updtad(ls, l, mid, lq, rq, ad);
		if(mid+1 <= rq)
			updtad(rs, mid+1, r, lq, rq, ad);
		upup(k);
	}
	int ask(int k, int l, int r, int lq, int rq) {
		if(lq <= l && r <= rq) 
			return tr[k];
		down(k);
		int mid = ((l+r)>>1), ret = -inf;
		if(lq <= mid)
			ret=max(ret, ask(ls, l, mid, lq, rq));
		if(mid+1 <= rq)
			ret=max(ret, ask(rs, mid+1, r, lq, rq));
		upup(k);
		return ret;
	}
}A;

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
int comp(qwq AA, qwq BB) {
	if(AA.w == BB.w)
		return AA.op < BB.op;
	return AA.w < BB.w;
}

signed main() {
	freopen("imp.in", "r", stdin);
	freopen("imp.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) 
		read(xx[i]), read(yy[i]), read(cc[i]), zhan[i*2-1]=qwq{xx[i], i, 0}, zhan[i*2]=qwq{yy[i], i, 1};
	sort(zhan+1, zhan+1+n+n, comp);
	for(int i = 1; i <= 2*n; ++i) {
		if(i == 1 || zhan[i].w != zhan[i-1].w)
			++cnt, to[cnt]=zhan[i].w;
		if(zhan[i].op)
			yy[zhan[i].t]=cnt;
		else
			xx[zhan[i].t]=cnt;
	}
//	for(int j = 1; j <= cnt; ++j)
//		cout<<to[j]<<" ";
//	puts("!");
	A.built(1, 1, cnt);
//	for(int j = 1; j <= cnt; ++j)
//		write(A.ask(1, 1, cnt, j, j), ' ');
//	puts("");
	for(int i = 1; i <= n; ++i) 
		zhan[i].w=max(xx[i], yy[i]), zhan[i].t=min(xx[i], yy[i]), zhan[i].op=cc[i];
	sort(zhan+1, zhan+1+n, comp);
	for(int i = 1; i <= n; ++i) {
//		cout<<zhan[i].t<<" "<<zhan[i].w<<" "<<zhan[i].op<<"\n";
		A.updt(1, 1, cnt, 1, zhan[i].t, to[zhan[i].w]);
		A.updtad(1, 1, cnt, 1, zhan[i].t, zhan[i].op);
		ans=max(A.tr[1], ans);
//		for(int j = 1; j <= cnt; ++j)
//			write(A.ask(1, 1, cnt, j, j), ' ');
//		puts("");
	}
	write(ans, '\n');
	return 0;
}
