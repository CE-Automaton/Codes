#include <bits/stdc++.h>
#define mod 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
int t, tp;
LL n, p;
struct matx {
	int a[2][2];
}C, aa, bb, cc, dd;
struct matxx {
	int a[3][3];
}CC, aaa, bbb;
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
matx mul(matx A, matx B) {
	C.a[0][0]=upd(1LL*A.a[0][0]*B.a[0][0]%mod+1LL*A.a[0][1]*B.a[1][0]%mod);
	C.a[0][1]=upd(1LL*A.a[0][0]*B.a[0][1]%mod+1LL*A.a[0][1]*B.a[1][1]%mod);
	C.a[1][0]=upd(1LL*A.a[1][0]*B.a[0][0]%mod+1LL*A.a[1][1]*B.a[1][0]%mod);
	C.a[1][1]=upd(1LL*A.a[1][0]*B.a[0][1]%mod+1LL*A.a[1][1]*B.a[1][1]%mod);
	return C;
}
matxx mull(matxx A, matxx B) {
	CC.a[0][0]=upd(1LL*A.a[0][0]*B.a[0][0]%mod+upd(1LL*A.a[0][1]*B.a[1][0]%mod+1LL*A.a[0][2]*B.a[2][0]%mod));
	CC.a[0][1]=upd(1LL*A.a[0][0]*B.a[0][1]%mod+upd(1LL*A.a[0][1]*B.a[1][1]%mod+1LL*A.a[0][2]*B.a[2][1]%mod));
	CC.a[0][2]=upd(1LL*A.a[0][0]*B.a[0][2]%mod+upd(1LL*A.a[0][1]*B.a[1][2]%mod+1LL*A.a[0][2]*B.a[2][2]%mod));
	CC.a[1][0]=upd(1LL*A.a[1][0]*B.a[0][0]%mod+upd(1LL*A.a[1][1]*B.a[1][0]%mod+1LL*A.a[1][2]*B.a[2][0]%mod));
	CC.a[1][1]=upd(1LL*A.a[1][0]*B.a[0][1]%mod+upd(1LL*A.a[1][1]*B.a[1][1]%mod+1LL*A.a[1][2]*B.a[2][1]%mod));
	CC.a[1][2]=upd(1LL*A.a[1][0]*B.a[0][2]%mod+upd(1LL*A.a[1][1]*B.a[1][2]%mod+1LL*A.a[1][2]*B.a[2][2]%mod));
	CC.a[2][0]=upd(1LL*A.a[2][0]*B.a[0][0]%mod+upd(1LL*A.a[2][1]*B.a[1][0]%mod+1LL*A.a[2][2]*B.a[2][0]%mod));
	CC.a[2][1]=upd(1LL*A.a[2][0]*B.a[0][1]%mod+upd(1LL*A.a[2][1]*B.a[1][1]%mod+1LL*A.a[2][2]*B.a[2][1]%mod));
	CC.a[2][2]=upd(1LL*A.a[2][0]*B.a[0][2]%mod+upd(1LL*A.a[2][1]*B.a[1][2]%mod+1LL*A.a[2][2]*B.a[2][2]%mod));
	return CC;
}

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
	File("spt");
	read(t), read(tp);
	if(tp == 1) {
		while(t--) {
			read(n), read(p);
			if(n == 1) {
				write(1, '\n');
				continue;
			}
			--n;
			dd.a[0][0]=1, dd.a[0][1]=0, dd.a[1][0]=0, dd.a[1][1]=1;
			if(n%p != 0) {
				if(n%p > 1) {
					bb.a[0][0]=1;
					bb.a[0][1]=(n%p-1)%mod;
					bb.a[1][0]=0;
					bb.a[1][1]=1;
					dd=mul(dd, bb);
				}
				aa.a[0][0]=1;
				aa.a[0][1]=1;
				aa.a[1][0]=1;
				aa.a[1][1]=2;
				dd=mul(dd, aa);
			}
			aa.a[0][0]=1;
			aa.a[0][1]=1;
			aa.a[1][0]=1;
			aa.a[1][1]=2;
			bb.a[0][0]=1;
			bb.a[0][1]=(p-1)%mod;
			bb.a[1][0]=0;
			bb.a[1][1]=1;
			aa=mul(bb, aa);
			LL y = n/p;
			while(y) {
				if(y&1) dd=mul(dd, aa);
				aa=mul(aa, aa);
				y=(y>>1);
			}
			write(dd.a[1][0], '\n');
		}
	}
	else {
		while(t--) {
			read(n), read(p);
			if(n == 1) {
				write(1, '\n');
				continue;
			}
			--n;
			if(n <= p) {
				write(n%mod, '\n');
				continue;
			}
			dd.a[0][0]=1, dd.a[0][1]=0, dd.a[1][0]=0, dd.a[1][1]=1;
			bbb.a[0][0]=1;
			bbb.a[0][1]=0;
			bbb.a[0][2]=0;
			bbb.a[1][0]=0;
			bbb.a[1][1]=1;
			bbb.a[1][2]=0;
			bbb.a[2][0]=0;
			bbb.a[2][1]=0;
			bbb.a[2][2]=1;
			if(n%p != 0) {
				if(n%p > 1) {
					bb.a[0][0]=1;
					bb.a[0][1]=(n%p-1)%mod;
					bb.a[1][0]=0;
					bb.a[1][1]=1;
					dd=mul(dd, bb);
				}
				aa.a[0][0]=1;
				aa.a[0][1]=1;
				aa.a[1][0]=1;
				aa.a[1][1]=2;
				dd=mul(dd, aa);
				bbb.a[0][0]=dd.a[0][0];
				bbb.a[0][1]=dd.a[0][1];
				bbb.a[0][2]=0;
				bbb.a[1][0]=dd.a[1][0];
				bbb.a[1][1]=dd.a[1][1];
				bbb.a[1][2]=0;
				bbb.a[2][0]=dd.a[1][0];
				bbb.a[2][1]=dd.a[1][1];
				bbb.a[2][2]=1;
			}
			aa.a[0][0]=1;
			aa.a[0][1]=1;
			aa.a[1][0]=1;
			aa.a[1][1]=2;
			bb.a[0][0]=1;
			bb.a[0][1]=(p-1)%mod;
			bb.a[1][0]=0;
			bb.a[1][1]=1;
			aa=mul(bb, aa);
			aaa.a[0][0]=aa.a[0][0];
			aaa.a[0][1]=aa.a[0][1];
			aaa.a[0][2]=0;
			aaa.a[1][0]=aa.a[1][0];
			aaa.a[1][1]=aa.a[1][1];
			aaa.a[1][2]=0;
			aaa.a[2][0]=aa.a[1][0];
			aaa.a[2][1]=aa.a[1][1];
			aaa.a[2][2]=1;
			LL y = n/p;
			while(y) {
				if(y&1) bbb=mull(bbb, aaa);
				aaa=mull(aaa, aaa);
				y=(y>>1);
			}
			// debug(bbb.a[0][0], bbb.a[1][0], bbb.a[2][0], "!!!\n");
			// debug(bbb.a[2][0], bbb.a[2][1], bbb.a[2][2], bbb.a[1][0], bbb.a[0][0], "???\n");
			write(upd(1LL*upd(bbb.a[2][0]-bbb.a[1][0]+mod)*(p%mod)%mod+upd(bbb.a[1][0]+upd(bbb.a[0][0]-1+mod))), '\n');
		}
	}
	return 0;
}