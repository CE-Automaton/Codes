#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
const int N = 4e3+4;
int n, gs, ans, pw[N*N], inn[N], outt[N], wzz[N], qwq;
char g[N][N];
bitset<N> in[N], out[N], wz[N], s;

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
int upd(int x) {
	return (x >= mod ? x-mod : x);
}
void summ(int x/*in*/, int y/*out*/, int ww) {
	if(ww) {
		s=(wz[x]&wz[y]);
		ans=upd(ans-1LL*s.count()*qwq%mod+mod);
	}
	else {
		s=(in[x]&out[y]);
		ans=upd(ans-1LL*s.count()*qwq%mod+mod);
		s=(in[y]&out[x]);
		ans=upd(ans-1LL*s.count()*pw[gs-1]%mod+mod);
	}
}

signed main() {
	freopen("random.in", "r", stdin);
	freopen("random.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i)
		scanf("%s", g[i]+1);
	for(int i = 1; i <= n; ++i)
		for(int j = i+1; j <= n; ++j) 
			if(g[i][j] == '1') 
				in[j][i]=out[i][j]=1, ++inn[j], ++outt[i];
			else
				if(g[j][i] == '1')
					in[i][j]=out[j][i]=1, ++inn[i], ++outt[j];
				else
					wz[i][j]=wz[j][i]=1, ++wzz[i], ++wzz[j], ++gs;
	if(gs == 0) {
		for(int i = 1; i <= n; ++i)
			ans=upd(ans+inn[i]*outt[i]), 
			ans=upd(ans-(inn[i]*(inn[i]-1)/2)+mod);
		write(332748118LL*ans%mod, '\n');
		return 0;
	}
	pw[0]=1;
	for(int i = 1; i <= gs; ++i)
		pw[i]=upd(pw[i-1]+pw[i-1]);
	for(int i = 1; i <= n; ++i)
		ans=upd(ans+1LL*pw[gs-2]*(wzz[i]*(wzz[i]-1)/2)%mod), 
		ans=upd(ans+1LL*pw[gs-1]*inn[i]%mod*outt[i]%mod);
	qwq=332748118LL*pw[gs-1]%mod;
	for(int i = 1; i <= n; ++i)
		for(int j = i+1; j <= n; ++j) 
			if(g[i][j] == '1')
				summ(i, j, 0);
			else
				if(g[j][i] == '1')
					summ(j, i, 0);
				else
					summ(i, j, 1);
	write(ans, '\n');
	return 0;
}
