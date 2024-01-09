#include <bits/stdc++.h>
using namespace std;
const int N = 2e6+5;
int n, cnt;
long long cc, a[N], to[N], vv;
struct qwq {
	long long w;
	int d;
}b[N];
struct tree {
	long long mn[N<<2]/*最小值*/, llzy[N<<2]/*加上原本值的lazy*/, lzyy[N<<2]/*加上一个数的lazy*/, lzzy[N<<2]/*赋值lazy*/;
	#define ls (k<<1)
	#define rs (ls|1)
	void upup(int k) {
		mn[k]=min(mn[ls], mn[rs]);
	}
	void ddown(int k) {
		if(lzzy[k] != 0) 
			mn[ls]=mn[rs]=mn[k], lzzy[ls]=lzzy[rs]=1, lzzy[k]=0, 
			llzy[ls]=lzyy[ls]=llzy[rs]=lzyy[rs]=0;
	}
	void down(int k, int l, int r) {
		int mid = ((l+r)>>1);
		ddown(k);
		ddown(ls);
		ddown(rs);
		if(llzy[k] != 0) {
			mn[ls]+=llzy[k]*to[mid];
			mn[rs]+=llzy[k]*to[r];
			llzy[ls]+=llzy[k];
			llzy[rs]+=llzy[k];
			llzy[k]=0;
		}
		if(lzyy[k] != 0) {
			mn[ls]+=lzyy[k];
			mn[rs]+=lzyy[k];
			lzyy[ls]+=lzyy[k];
			lzyy[rs]+=lzyy[k];
			lzyy[k]=0;
		}
	}
	void built(int k, int l, int r) {
		mn[k]=llzy[k]=lzyy[k]=lzzy[k]=0;
		if(l == r) return ;
		int mid = ((l+r)>>1);
		built(ls, l, mid);
		built(rs, mid+1, r);
	}
	void updt1(int k, int l, int r, int tt, long long v) {
		if(l != r)
			down(k, l, r);
		if(r <= tt) {
			ddown(k);
			++llzy[k];
			lzyy[k]+=v; 
			mn[k]=mn[k]+to[r]+v;
			if(r == tt)
				vv = mn[k];
			return ;
		}
		if(l > tt) {
			ddown(k);
			lzyy[k]+=cc; 
			mn[k]+=cc;
			return ;
		}
		int mid = ((l+r)>>1);
		updt1(ls, l, mid, tt, v);
		updt1(rs, mid+1, r, tt, v);
		upup(k);
		return ;
	}
	int updt2(int k, int l, int r, int tt) {
//		cout<<l<<" "<<r<<" "<<tt<<" "<<mn[k]<<" "<<vv<<"!!!\n";
		if(l != r)
			down(k, l, r);
		int mid = ((l+r)>>1);
		if(l > tt) {
			if(mn[k] > vv) {
				llzy[k]=lzyy[k]=0;
				mn[k]=vv;
				lzzy[k]=1;
				return 1;
			} 
			if(l != r) {
		        if(updt2(ls, l, mid, tt))//左边都赋值了,就去右边看 
					int ret = updt2(rs, mid+1, r, tt);
	        }
	        return 0;
	    }
	    if(l == r || r < tt)
	    	return 1;//返回 
	    if(tt < mid) {
	        if(updt2(ls, l, mid, tt))//左边都赋值了,就去右边看 
	            return updt2(rs, mid+1, r, tt);
	        return 0;//出现了未赋值的地方 
	    }
	    return updt2(rs, mid+1, r, tt);//不能走左边就走右边 
	}//不push up是因为全局最小值是没有变化的,可以暂时不用push up 
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
int comp(qwq A, qwq B) {
	return A.w > B.w;
}

signed main() {
	read(n), read(cc);
	for(int i = 1; i <= n; ++i) 
		read(a[i]), b[i]=qwq {a[i], i};
	sort(b+1, b+1+n, comp);
	for(int i = 1; i <= n; ++i) {
		if(i == 1 || b[i].w != b[i-1].w)
			to[++cnt]=b[i].w;
		a[b[i].d]=cnt;
	}
	A.built(1, 1, cnt);
	for(int i = 1; i <= n; ++i) {
		A.updt1(1, 1, cnt, a[i], -to[a[i]]);
		int ret=A.updt2(1, 1, cnt, a[i]);
	}
	write(A.mn[1], '\n');
	return 0;
}
