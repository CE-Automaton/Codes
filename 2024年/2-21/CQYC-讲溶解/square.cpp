#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
const int N = 1e5+5, V = 1e6+5, M = 505, base = 1e8;
int n, vis[V], pri[V], tot, cnt, anl;
struct qwq {
	int a, b;
}ans[10000005];
LL ww[6/*5次*/][V], www[6][N];
unordered_map <LL, int> bb;
__int128 op[N];
vector <int> aa[V], cc[N];

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
struct gaojing {
	int b[M], len;
	void clear() { memset(b, 0, sizeof b), len = 1; }
	template <typename T> int getln(T x) {
		int ret=0;
		do ++ret, x/=10; while(x);
		return ret;
	}
	template <typename T> void get(T x) {
		len=0, memset(b,0,sizeof(b));
		T tmp;
		while(tmp=x/base) b[++len]=x%base, x=tmp;
		b[++len]=x;
	}
	void out() {
		int baselen=8;
		debug(b[len]);
		for(int i = len-1, tmp; i; --i) {
			tmp=baselen-getln(b[i]);
			while(tmp--) debug(0);
			debug(b[i]);
		}
		debug("out!\n");
	}
	bool operator == (const gaojing& x) const {
		if(len != x.len) return false;
		for(int i = len; i >= 1; --i) if(b[i] != x.b[i]) return false;
		return true;
	}
	bool operator > (const gaojing& x)const {
		if(len != x.len) return (len > x.len);
		for(int i = len; i >= 1; --i) if(b[i] != x.b[i]) return (b[i] > x.b[i]);
		return false;
	}
	bool operator < (const gaojing& x)const {
		if(len != x.len) return (len < x.len);
		for(int i = len; i >= 1; --i) if(b[i] != x.b[i]) return (b[i] < x.b[i]);
		return false;
	}
	bool operator <= (const gaojing& x) const { return !((*this) > x); }
	bool operator >= (const gaojing& x) const { return !((*this) < x); }
	gaojing operator + (const gaojing& x) const {
		gaojing ret; ret.clear();
		ret.len=max(len, x.len);
		for(int i=1;i <= ret.len;++i) {
			ret.b[i]+=b[i]+x.b[i];
			if(ret.b[i] >= base)
				ret.b[i]-=base, ++ret.b[i+1];
		}
		if(ret.b[ret.len+1]) ++ret.len;
		return ret;
	}
	template <typename T> gaojing operator + (const T& x) const {
		gaojing op; op.get(x);
		return (*this)+op;
	}
	gaojing operator - (const gaojing& x) const {
		gaojing ret; ret.clear();
		if(*this == x) return ret;
		ret.len=std::max(len,x.len);
		for(int i = 1; i <= ret.len; ++i) {
			ret.b[i]+=b[i]-x.b[i];
			if(ret.b[i] < 0) ret.b[i]+=base, --ret.b[i+1];
		}
		while(ret.len && !ret.b[ret.len]) --ret.len;
		return ret;
	}
	template <typename T> gaojing operator - (const T& x) const {
		gaojing op; op.get(x);
		return (*this)-op;
	}
	gaojing operator * (const gaojing& x) const {
		gaojing ret; ret.clear();
		// if((*this) == ret || x == ret) return ret;
		ret.len=len+x.len;
		uLL tmp;
		for(int i = 1; i <= len; ++i)
			for(int j = 1; j <= x.len; ++j) {
				tmp = 1uLL*b[i]*x.b[j]+ret.b[i+j-1];
				if(tmp>=base) 
					ret.b[i+j]+=tmp/base, ret.b[i+j-1]=tmp%base;
				else
					ret.b[i+j-1]=tmp;
			}
		while(!ret.b[ret.len])
			--ret.len;
		return ret;
	}
	template <typename T> gaojing operator * (const T& x) const {
		gaojing op; op.get(x);
		return (*this)*op;
	}
	gaojing operator / (const gaojing& x) const {
		gaojing now=(*this), tmp, ret, op=x;
		tmp.get(1); ret.clear();
		if((*this) == ret) return ret;
		// tmp.out();
		while(now >= op) op=op*2, tmp=tmp*2;
		while(tmp.len > 1 || tmp.b[1]) {
			if(now >= op) now=now-op, ret=ret+tmp;
			op=op/2, tmp=tmp/2;
		}
		while(ret.len && !ret.b[ret.len]) --ret.len;
		if(!ret.len) ret.clear();
		return ret;
	}
	template <typename T> gaojing operator / (const T& x) const {
		gaojing ret; ret.clear();
		if(len == 1 && x > b[1]) return ret;
		uLL res = 0; ret.len=len;
		for(int i = len; i; --i) 
			res=res*base+b[i], ret.b[i]=res/x, res%=x;
		while(ret.len > 1 && !ret.b[ret.len]) --ret.len;
		return ret;
	}
	gaojing operator % (const gaojing& x) const {
		gaojing now=(*this), tmp, op=x;
		tmp.get(1);
		while(now >= op) op=op*2, tmp=tmp*2;
		while(tmp.len > 1 || tmp.b[1]) {
			if(now >= op) now=now-op;
			op=op/2, tmp=tmp/2;
		}
		return now;
	}
	template <typename T> gaojing operator % (const T& x) const {
		gaojing op; op.get(x);
		return (*this)%op;
	}
}sum;
LL rd() {
	LL ret = 1LL*RAND_MAX*RAND_MAX*rand()+1LL*RAND_MAX*rand()+rand();
	return ret;
}

signed main() {
	File("square");
	srand(time(0));
	read(n);
	for(int i = 2; i <= 1000000; ++i) {
		if(!vis[i]) {
			aa[i].push_back(i);
			pri[++tot]=i;
			for(int j = 1; j <= 3; ++j)
				ww[j][i]=rand();
		}
		for(int j = 1; j <= tot && i <= 1000000/pri[j]; ++j) {
			aa[i*pri[j]]=aa[i];
			aa[i*pri[j]].push_back(pri[j]);
			vis[i*pri[j]]=1;
			if(i%pri[j] == 0) break;
		}
	}
	int pd = 1;
	for(int i = 1; i <= n; ++i) 
		read(op[i]), pd&=(op[i] <= 1000000);
	if(pd) {
		bb[0]=++cnt;
		cc[1].push_back(n+1);
		LL now = 0;
		for(int i = n; i >= 1; --i) {
			www[2][i]=www[2][i+1];
			www[3][i]=www[3][i+1];
			for(int j : aa[op[i]]) {
				now^=ww[1][j];
				www[2][i]^=ww[2][j];
				www[3][i]^=ww[3][j];
			}
			if(bb.find(now) == bb.end()) 
				bb[now]=++cnt;
			else
				for(int j : cc[bb[now]])
					if(www[2][j] == www[2][i] && www[3][j] == www[3][i])
						ans[++anl]=qwq {i, j-1};
			cc[bb[now]].push_back(i);
		}
		write(anl, '\n');
		for(int i = anl; i >= 1; --i)
			write(ans[i].a, ' '), write(ans[i].b, '\n');
		return 0;
	}
	else {
		debug("!\n");
		for(int i = 1; i <= n; ++i) {
			sum.get(1);
			for(int j = i; j <= n; ++j) {
				sum=sum*op[j];
				gaojing l, r, sqt;
				l.get(1), r=sum;
				sqt.get(0);
				while(l <= r) {
					gaojing mid = (l+r)/2;
					if(mid.len+mid.len <= sum.len && mid*mid <= sum)
						sqt=mid, l=mid+1;
					else
						r=mid-1;
				}
				if(sqt*sqt == sum)
					ans[++anl]=qwq {i, j};
			}
		}
		write(anl, '\n');
		for(int i = 1; i <= anl; ++i)
			write(ans[i].a, ' '), write(ans[i].b, '\n');
	}
	return 0;
}