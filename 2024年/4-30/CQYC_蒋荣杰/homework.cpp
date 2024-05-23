#include <bits/stdc++.h>
#define mod 998244353
#define inv2 499122177
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 8e5+55, base = 131, aaa = 1e9+7;
int n, rk[N], b[N], sa[N], cnt, len, hs[N], bs[N], ans, sum;
char s[N];
vector <int> ha, hb, hc, hd;

int upd(int x) {
	return (x >= mod ? x-mod : x);
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
namespace MUL {
	const int g=3, ng=332748118; 
	int ksm(int base, int tim) {
		int ret=1;
		while(tim) {
			if(tim&1) ret=1ll*ret*base%mod;
			base=1ll*base*base%mod;
			tim>>=1;
		}
		return ret;
	}
	void NTT(vector <int> &num, int lim, int op) {
		vector <int> rev(lim);
		for(int i = 0; i < lim; ++i)
			rev[i]=(rev[i>>1]>>1)|((lim>>1)*(i&1));
		for(int i = 0; i < lim; ++i)
			if(i < rev[i])
				swap(num[i], num[rev[i]]);
		for(int i = 2; i <= lim; i<<=1) {
			int wn = ksm((op==1 ? g : ng), (mod-1)/i);
			for(int j = 0; j < lim; j+=i) {
				int w = 1;
				for(int k = j; k < j+(i>>1); ++k) {
					int x = num[k], y = num[k+(i>>1)];
					num[k]=(x+1ll*w*y%mod)%mod, num[k+(i>>1)]=(x-1ll*w*y%mod)%mod;
					w=1ll*w*wn%mod;
				}
			}
		}
	}
	vector <int> Mul(vector <int> &x, vector <int> &y) {
		int lim = 1, len=x.size()+y.size();
		while(lim < (len<<1))
			lim<<=1;
		while(x.size() < lim)
			x.push_back(0);
		while(y.size() < lim)
			y.push_back(0);
		NTT(x, lim, 1), NTT(y, lim, 1);
		for(int i = 0; i < lim; ++i)
			x[i]=1ll*x[i]*y[i]%mod;
		NTT(x, lim, -1);
		int inv = ksm(lim, mod-2);
		vector <int> ret(len-1);
		for(int i = 0; i < len-1; ++i)
			ret[i]=(1ll*x[i]*inv%mod+mod)%mod;
		return ret;
	}
}

signed main() {
	File("homework");
	read(n);
	scanf("%s", s+1);
	ha.resize(8*n+2);
	hb.resize(8*n+2);
	bs[0]=1;
	int nnow = 0;
	++ha[nnow+2*n];
	for(int i = 1; i <= n; ++i) {
		sa[i]=i, bs[i]=1LL*bs[i-1]*base%aaa, 
		nnow+=(s[i]-'a'-2);
		for(int j = 0; j <= 4*n; ++j) {
			if(ha[j])
				sum=upd(sum+1LL*hb[nnow+6*n-j]*ha[j]%mod);
			if(ha[j] >= 2)
				sum=upd(sum+(1LL*ha[j]*(ha[j]-1)/2%mod));
		}
		for(int j = 0; j <= 4*n; ++j) 
			if(ha[j])
				hb[nnow+6*n-j]=upd(hb[nnow+6*n-j]+ha[j]);
		++ha[nnow+2*n];
	}
	for(int i = n; i >= 1; --i)
		hs[i]=(1LL*hs[i+1]*base%aaa+s[i])%aaa;
	for(int i = 1; i <= n; ++i) 
		for(int j = i+1; j <= n; ++j) {
			int l = 1, r = min(i, j), ll = 0;
			while(l <= r) {
				int mid = ((l+r)>>1);
				if((hs[i-mid+1]-1LL*hs[i+1]*bs[mid]%aaa+aaa)%aaa == (hs[j-mid+1]-1LL*hs[j+1]*bs[mid]%aaa+aaa)%aaa)
					l=mid+1, ll=mid;
				else
					r=mid-1;
			}
			ans=upd(ans+ll);
		}
	write(upd(sum-ans)*2LL%mod, '\n');
	return 0;
}