#include <bits/stdc++.h>
using namespace std;
const int N = 1e7+5;
int n, len, r, mx, www[15];
long long ans;
char lst[N], a[15];
signed main() {
	freopen("dance.in", "r", stdin);
	freopen("dance.out", "w", stdout);
	scanf("%d", &n);
	www[0]=1;
	for(int i = 1; i <= 9; ++i) www[i]=www[i-1]*10;
	for(int i = 1; i <= n; ++i) {
		char c = getchar();
		int l = 0;
		while(c < '0' || c > '9') c=getchar();
		while(c >= '0' && c <= '9')
			a[++l]=c, c=getchar();
		if(len < l) {
			for(int j = 1; j <= l; ++j)
				lst[j]=a[j];
			len=r=mx=l;//mx表示最右边第一个可能不为'0'的位置,优化时间复杂度,反正大样例都能过哈哈哈哈 
		}
		else {
			int pd = 1;
			for(int j = 1; j <= l; ++j)
				if(lst[j] != a[j]) {
					r=l;
					if(lst[j] < a[j]) {
						for(int k = j; k <= l; ++k)
							lst[k]=a[k];
						for(int k = l+1; k <= mx; ++k)
							lst[k]='0';
						mx=l;
					}
					else {
						++len;
						lst[len]='0';//多了一个'0'就手动赋值,不然会WA 
						for(int k = j; k <= l; ++k)
							lst[k]=a[k];
						for(int k = l+1; k <= mx; ++k)
							lst[k]='0';
						mx=l;
					}
					pd=0;
					break;
				}
			if(pd) {
				int haha = 0;
				r=l;
				if(mx != len) haha = 1;
				else
					for(int k = r+1; k <= len; ++k) 
						if(lst[k] != '9') {
							haha=1;
							break;
						}
				if(haha) {
					++lst[len];
					mx=len;
					for(int k = len; k >= r+1; --k)
						if(lst[k] > '9')
							++lst[k-1], lst[k]-=10;
						else
							break;
				}
				else {
					++len;
					lst[len]='0';//多了一个'0'就手动赋值,不然会WA
					for(int k = r+1; k <= mx; ++k) 
						lst[k]='0';
					mx=r;
				}
			}
		}
//		cout<<lst+1<<"!\n";
		ans+=1LL*(len-l);
	}
	printf("%lld\n", ans);
	return 0;
}
