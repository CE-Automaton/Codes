#include <bits/stdc++.h>
#define int long long
#define mod 1000000007 
using namespace std;
const int N = 5e5+5;
int n, p[45], m, sum[45], inv[45], ans;
struct qwq {
	int s, z;
};
vector <qwq> L, R;

template <typename T> inline void read(T& x) {
	x=0; char c = getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
}
int lne; char put[105];
template <typename T> inline void write(T x) {
	lne = 0; if(x < 0) putchar('-'), x=-x;
	do { put[++lne]=x%10, x/=10; } while(x);
	while(lne) putchar(put[lne]^48), --lne;
}
void instL(int x) {
	int sz = L.size();
	for(int i = 0; i < sz; ++i)
		L.push_back(qwq{L[i].s+x, -L[i].z});
}
void instR(int x) {
	int sz = R.size();
	for(int i = 0; i < sz; ++i)
		R.push_back(qwq{R[i].s+x, -R[i].z});
}
int comp1(qwq A, qwq B) {
	return A.s < B.s;
}
int comp2(qwq A, qwq B) {
	return A.s > B.s;
}
int operator *(const int A, const int B) {
	return (A*B%mod+mod)%mod;
}

signed main() {
//	freopen("sakura.in", "r", stdin);
//	freopen("sakura.out", "w", stdout);
	read(n);
	L.push_back(qwq{0, 1});
	R.push_back(qwq{0, 1});
	inv[0]=inv[1]=1;
	for(int i = 2; i <= n; ++i)
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i = 1; i <= n; ++i)
		read(p[i]), m+=p[i];
	for(int i = 1; i <= n/2; ++i)
		instL(p[i]);
	for(int i = n/2+1; i <= n; ++i)
		instR(p[i]);
	m=(m+n)/2;
	sort(L.begin(), L.end(), comp2);
	sort(R.begin(), R.end(), comp1);
	int c = 0, r = 0, sz = R.size();
	for(qwq l : L) {
		while(r < sz && l.s+R[r].s <= m-1) {
			c = (R[r].z+mod)%mod;
			for(int i = 1; i <= n; ++i)
				sum[n-i]=(sum[n-i]+c)%mod, c=(c*((mod+mod-R[r].s-i+1)%mod)%mod*inv[i]%mod+mod)%mod;
			++r;
		}
		c = (l.z+mod)%mod;
		for(int i = 0; i <= n-1; ++i)
			ans=(ans+c*sum[i]%mod)%mod, c=((c*(m-1-l.s-i)%mod*inv[i+1]%mod)%mod+mod)%mod;
	}
	write(ans);
	return 0;
}
