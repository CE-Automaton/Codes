#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned long long ull;
const int N = 1e5+3, M = 2e4+2;
int t, n, m, c[N], pw[N], ans;

ull mi[200];
struct Bit {
	ull bit[1566]; int len = 1566;
	#define I inline 
	I void reset() {memset(bit, 0, sizeof(bit));}
	Bit() {memset(bit, 0, sizeof(bit));}
	I void set1(int x) { bit[x>>6] |= mi[x&63];}
	I void set0(int x) { bit[x>>6] &= ~mi[x&63];}
	I void flip(int x) { bit[x>>6] ^= mi[x&63];}
	bool operator [](int x) { 
		return (bit[x>>6] >> (x&63)) & 1;
	}
	
	#define re register
	Bit operator ~ (void) const {
		Bit res;
		for (re int i = 0;i < len; i++) res.bit[i] = ~bit[i];
		return res;
	}
	
	Bit operator & (const Bit &b) const {
		Bit res;
		for (re int i = 0;i < len; i++) res.bit[i] = bit[i] & b.bit[i];
		return res;
	}
	
	Bit operator | (const Bit &b) const {
		Bit res;
		for (re int i = 0;i < len; i++) res.bit[i] = bit[i] | b.bit[i];
		return res;
	}	
	
	Bit operator ^ (const Bit &b) const {
		Bit res;
		for (re int i = 0;i < len; i++) res.bit[i] = bit[i] ^ b.bit[i];
		return res;
	}
	
	void operator &= (const Bit &b)  {
		for (re int i = 0;i < len; i++) bit[i] &= b.bit[i];
	}
	
	void operator |= (const Bit &b)  {
		for (re int i = 0;i < len; i++) bit[i] |= b.bit[i];
	}
	
	void operator ^= (const Bit &b)  {
		for (re int i = 0;i < len; i++) bit[i] ^= b.bit[i];
	}
	
	Bit operator << (const int t) const {
		Bit res; int high = t >> 6, low = t & 63;
		ull last = 0;
		for (register int i = 0;i + high < len; i++) {
			res.bit[i + high] = (last | (bit[i] << low));
			if (low) last = (bit[i] >> (64 - low));
		}
		return res;
	}
	
	Bit operator >> (const int t) const {
		Bit res; int high = t >> 6, low = t & 63;
		ull last = 0;
		for (register int i = len - 1;i >= high; i--) {
			res.bit[i - high] = last | (bit[i] >> low);
			if (low) last = bit[i] << (64 - low);
		}
		return res;
	}
	
	void operator <<= (const int t) {
		int high = t >> 6, low = t & 63;
		for (register int i = len - high - 1; ~i; i--) {
			bit[i + high] = (bit[i] << low);
			if (low && i) bit[i + high] |= bit[i - 1] >> (64 - low);
		}
		for (register int i = 0;i < high; i++) bit[i] = 0;
	}
	
}qwq[M], all, s;

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
	// File("color");
	for(int i = 1; i <= 100000; ++i)
		pw[i]=pw[i-1]+__lg(i&(-i));
	read(t);
	while(t--) {
		read(n), read(m);
		all.reset();
		for(int i = 1; i <= m; ++i)
			qwq[i].reset();
		for(int i = 1; i <= n; ++i) {
			read(c[i]);
			all=(all^qwq[c[i]]);
			qwq[c[i]]=(all<<1);
			if(qwq[c[i]].bit[0]%2 == 1)
				--qwq[c[i]].bit[0];
			else
				++qwq[c[i]].bit[0];
			all=(all^qwq[c[i]]);
			// for(int j = 1; j <= n; ++j)
			// 	cout<<qwq[c[i]][j]<<" ";
			// cout<<"\n";
		}
		ans=0;
		for(int i = 1; i <= n; ++i) 
			ans^=(pw[n-1]-pw[n-i]-pw[i-1] == 0 && all[i-1] == 1);
		putchar('0'+ans);
	}
	return 0;
}