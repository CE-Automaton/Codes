#include <bits/stdc++.h>
#define inf 1000000007
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N = 4e3+5;
int t, n, l[N], r[N], cnt, mn[N], ans;
char a[N], b[N];
struct pnt {
	int l, r;
}op[N];

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
int comp(pnt A, pnt B) {
	return A.r < B.r;
}

signed main() {
	File("ring");
	read(t);
	while(t--) {
		scanf("%s\n%s", a+1, b+1);
		n=strlen(a+1);
		ans=inf;
		int pd = 0, pdd = 1;
		for(int i = 1; i <= n; ++i)
			pd|=(a[i] == '1'), pdd&=(b[i] == '0'), b[i+n]=b[i];
		if(pd && pdd) {
			putchar('-'), putchar('1'), putchar('\n');
			continue;
		}
		l[0]=r[n+1]=0;
		for(int i = 1; i <= n; ++i)
			l[i]=(b[i] == '1' ? i : l[i-1]);
		for(int i = n; i >= 1; --i)
			r[i]=(b[i] == '1' ? i : r[i+1]);
		for(int st = 0; st < n; ++st) {
			cnt=0;
			// debug(st, "!!!\n");
			for(int i = 1; i <= n; ++i)
				if(a[i] != b[(i+st-1)%n+1])
					// debug(i, "!", (l[i] == 0 ? n-l[n]+i : i-l[i]), (r[i] == 0 ? n-i+r[1] : r[i]-i), "\n"), 
					op[++cnt]=pnt {(l[i] == 0 ? n-l[n]+i : i-l[i]), (r[i] == 0 ? n-i+r[1] : r[i]-i)};
			if(!cnt) {
				ans=min(ans, st);
				continue;
			}
			sort(op+1, op+1+cnt, comp);
			mn[cnt+1]=0;
			mn[cnt]=op[cnt].l;
			for(int i = cnt-1; i >= 1; --i)
				mn[i]=max(mn[i+1], op[i].l);
			for(int pp = 0; pp <= n; ++pp) {
				int l = 1, r = cnt, ppp = cnt+1;
				while(l <= r) {
					int mid = ((l+r)>>1);
					if(st+pp < op[mid].r)
						ppp=mid, r=mid-1;
					else
						l=mid+1;
				}
				ans=min(ans, st+pp+pp+mn[ppp]+mn[ppp]+cnt);
				// debug(pp, ":", st+pp+pp+mn[ppp]+mn[ppp]+cnt, "\n");
			}
		}
		for(int i = 1; i < n-i+1; ++i)
			swap(a[i], a[n-i+1]), swap(b[i], b[n-i+1]);
		l[0]=r[n+1]=0;
		for(int i = 1; i <= n; ++i)
			l[i]=(b[i] == '1' ? i : l[i-1]);
		for(int i = n; i >= 1; --i)
			r[i]=(b[i] == '1' ? i : r[i+1]);
		for(int st = 0; st < n; ++st) {
			cnt=0;
			for(int i = 1; i <= n; ++i)
				if(a[i] != b[(i+st-1)%n+1])
					op[++cnt]=pnt {(l[i] == 0 ? n-l[n]+i : i-l[i]), (r[i] == 0 ? n-i+r[1] : r[i]-i)};
			if(!cnt) {
				ans=min(ans, st);
				continue;
			}
			sort(op+1, op+1+cnt, comp);
			mn[cnt+1]=0;
			mn[cnt]=op[cnt].l;
			for(int i = cnt-1; i >= 1; --i)
				mn[i]=max(mn[i+1], op[i].l);
			for(int pp = 0; pp <= n; ++pp) {
				int l = 1, r = cnt, ppp = cnt+1;
				while(l <= r) {
					int mid = ((l+r)>>1);
					if(st+pp < op[mid].r)
						ppp=mid, r=mid-1;
					else
						l=mid+1;
				}
				ans=min(ans, st+pp+pp+mn[ppp]+mn[ppp]+cnt);
			}
		}
		write(ans, '\n');
	}
	return 0;
}