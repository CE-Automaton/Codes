#include <bits/stdc++.h>
#define op first
#define po second
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int N = 2e5+5;
int t, n, k, a[N], vis[N], pri[N], cnt;
set <pii> p;

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
int check(int xx) {
	int sum = 0, nw = 0;
	p.clear();
	p.insert(pii {0, 0});
	for(int i = 1; i <= n && nw < k; ++i) {
		sum+=a[i];
		int gs = 0;
		for(set<pii>::iterator j = p.begin(); j != p.end(); ++j) {
			++gs;
			if(sum-(*j).op < xx) break;
			if(sum-(*j).op >= xx && !vis[i-(*j).po]) {
				++nw;
				p.clear();
				sum=0;
				break;
			}
			if(gs >= 20) break;
		}
		p.insert(pii {sum, i});
	}
	return (nw >= k);
}

signed main() {
	// File("1003");
	vis[1]=1;
	for(int i = 2; i <= 200000; ++i) {
		if(!vis[i])
			pri[++cnt]=i;
		for(int j = 1; j <= cnt && 200000/pri[j] >= i; ++j) {
			vis[i*pri[j]]=1;
			if(i%pri[j] == 0) break;
		}
	}
	read(t);
	while(t--) {
		read(n), read(k);
		// debug(n, '\n');
		int l = 0, r = 0, ans = 0, pp=0;
		for(int i = 1; i <= n; ++i) {
			read(a[i]);
			if(a[i] > 0) r+=a[i]; else l+=a[i];
		}
		while(l <= r) {
			int mid = ((l+r)>>1);
			if(check(mid))
				pp=1, ans=mid, l=mid+1;
			else
				r=mid-1;
		}
		if(!pp) {
			puts("impossible");
			continue;
		}
		write(ans, '\n');
	}
	// debug(clock(), '\n');
	return 0;
}