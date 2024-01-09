#include <bits/stdc++.h>
#define TPLT template <typename T>
#define mod 998244353
using namespace std;
//bool st;
int n, m, A, B, c, op, x, y, vis[200005];
bitset<50004> a[50004], b;//’‚......÷ª”–300MB!? 
vector <int> az[200005];
TPLT void read(T& x) {
	x=0; char c=getchar(); while(c < '0' || c > '9') c=getchar();
	while(c >= '0' && c <= '9') x=(x<<1)+(x<<3)+(c^48), c=getchar();
}
int len; char put[105];
TPLT void write(T x) {
	if(x < 0) putchar('-'), x=-x;
	do { put[++len]=x%10, x/=10; }while(x);
	while(len) putchar(put[len--]^48);
}
//bool fn;
int main() {
//	cerr<<(double) ((&st-&fn)*1.0/1024/1024)<<"\n";
	freopen("plasticmemories.in", "r", stdin);
	freopen("plasticmemories.out", "w", stdout);
	read(n), read(m), read(A), read(B);
	if(B == 0 && n > 50000) {
		for(int i = 1; i <= n; ++i)
			read(c), az[i].push_back(c);
		for(int i = 1; i <= m; ++i) {
			read(op), read(x), read(y);
			if(op == 1) {
//				if(az[x].find(y)) continue;
				az[x].insert(lower_bound(az[x].begin(), az[x].end(), y, [](const int C, const int B){
					return C < B;
				}), y);
			}
			if(op == 2) {
				for(int i = 0; i < az[y].size(); ++i) {
//					if(az[x].find(az[y][i])) continue;
					az[x].insert(lower_bound(az[x].begin(), az[x].end(), az[y][i], [](const int C, const int B){
						return C < B;
					}), az[y][i]);
				}
			}
			if(op == 3) {
				long long sum = 0;
				for(auto it : az[x])
					vis[it]=1;
				for(auto it : az[y])
					if(vis[it]) {
						sum=1;
						break;
					}
				for(auto it : az[x])
					vis[it]=0;
				write(sum), putchar('\n');
			}
		}
		return 0;
	}
	for(int i = 1; i <= n; ++i)
		read(c), a[i][c]=1;
	for(int i = 1; i <= m; ++i) {
		read(op), read(x), read(y);
		if(op == 1)
			a[x][y]=1;
		if(op == 2)
			a[x]=(a[x]|a[y]);
		if(op == 3) {
			b=(a[x]&a[y]);
			long long sum = 0;
			if(A == 0)
				sum=b.count();
			else 
				for(int i = b._Find_first(); i <= n; i=b._Find_next(i)) 
					sum+=1LL*i;
			if(B == 0)
				sum=(sum == 0 ? 0 : 1);
			write(sum), putchar('\n');
		}
	}
	return 0;
}
