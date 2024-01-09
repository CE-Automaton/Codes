#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#define meow(args...) fprintf(stderr, args)
template<class T>
bool cmax(T &a, T b) {return a<b ? (a=b, true) : false;}
typedef unsigned uint32_t;
typedef unsigned long long uint64_t;
const uint32_t P=1e9+7;
int n, head[50], to[100], next[100], coef[51], dep[50], height[50], size[50], ans=0, root;
uint32_t f[51][2], per[51][51], com[51][51];
bool only(int u, int fa, int dis) {
	if(dis==0) return u==root;
	for(int i=head[u]; i; i=next[i])
		if(to[i]!=fa&&!only(to[i], u, dis-1)) return false;
	return true;
}
void dp(int u, int fa, int d) {
	size[u]=1;
	dep[u]=d;
	height[u]=0;
	for(int i=head[u]; i; i=next[i])
		if(to[i]!=fa) {
			dp(to[i], u, d+1);
			cmax(height[u], height[to[i]]+1);
			size[u]+=size[to[i]];
		}
	if(u==root||only(fa, u, dep[u]-1)) {
		f[0][0]=f[1][1]=1;
		size[u]=1;
		for(int i=head[u]; i; i=next[i])
			if(to[i]!=fa) {
				for(int j=size[u]; j>=1; --j) {
					for(int k=1; k<=size[to[i]]; ++k)
						f[j+k][1]=(f[j+k][1]+(uint64_t)(f[j][0]+f[j][1])*per[size[to[i]]][k]%P*com[j+k][j])%P;
					if(u!=root&&height[to[i]]+1>=dep[u]) f[j][0]=f[j][1]=0;
				}
				if(f[0][0]) for(int j=1; j<=size[to[i]]; ++j) f[j][0]=(f[j][0]+per[size[to[i]]][j])%P;
				if(u!=root&&height[to[i]]+1>=dep[u]) f[0][0]=0;
				size[u]+=size[to[i]];
			}
		for(int i=1; i<=size[u]; ++i) ans=(ans+(uint64_t)coef[i]*f[i][1])%P;
		memset(f, 0, (size[u]+1)*8);
	}
}
int main() {
	int i, j;
	assert(freopen("detector.in", "r", stdin));
	assert(freopen("detector.out", "w", stdout));
	assert(scanf("%d", &n)==1);
	if(n==1) {
		puts("0");
		return 0;
	}
	for(i=1, j=2; i<n; ++i) {
		assert(scanf("%d", to+j)==1);
		to[j+1]=i;
		next[j]=head[to[j^1]], head[to[j^1]]=j, ++j;
		next[j]=head[to[j^1]], head[to[j^1]]=j, ++j;
	}
	for(i=0; i<=n; ++i) {
		per[i][0]=1;
		for(j=0; j<i; ++j) per[i][j+1]=(uint64_t)per[i][j]*(i-j)%P;
	}
	for(i=0; i<=n; ++i) {
		com[i][0]=com[i][i]=1;
		for(j=1; j<i; ++j) com[i][j]=(com[i-1][j-1]+com[i-1][j])%P;
	}
	coef[n]=n;
	coef[n-1]=P-1;
	for(i=n-2; i>=1; --i) coef[i]=(uint64_t)coef[i+1]*(n-i)%P;
	for(i=0; i<n; ++i) dp(root=i, -1, 0);
	printf("%u\n", ans);
	return 0;
}
