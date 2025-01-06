#include <bits/stdc++.h>
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
const int N=3e5+5,mod=998244353;
int n,a[N],b[N];
int ans;
const int P1=2333,P2=147744151;
map<pair<int,int>,bool> vis;

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
void dfs(int x){
	if(x == n+1){
		int v1 = 0, v2 = 0, mul = 1;
		for(int i = 1; i <= n; ++i) {
			int val=a[i]+b[(i==1?n:i-1)]-b[i];
			mul=1ll*mul*val%mod;
			v1=(1ll*v1*P1+val)%mod;
			v2=(1ll*v2*P2+val)%mod;
		}
		if(!vis[{v1,v2}]) {
			vis[{v1,v2}]=1;
			ans=(ans+mul)%mod;
		}
		return;
	}
	for(b[x] = 0; b[x] <= a[x]; ++b[x])
        dfs(x+1); 
}
signed main() {
    File("iv");
	read(n);
    int sub = 1;
	for(int i = 1; i <= n; ++i)
        read(a[i]), sub&=(a[i]<=1);
	if(sub) {
		ans = 1;
		for(int i = 1; i <= n; ++i) ans*=a[i];
		write(ans, '\n');
		return 0;
	}
	dfs(1);
	write(ans, '\n');
	return 0;
}