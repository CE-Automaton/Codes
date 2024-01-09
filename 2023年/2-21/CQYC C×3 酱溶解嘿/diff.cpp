#include <bits/stdc++.h>
using namespace std;
int t, n, m, a[100005], cnt, sum, c[100005], d[100005], vis[100005];
struct qwq {
	int s, gs;
}b[100005];
unordered_map <int, int> to;
queue <int> ppp;
int ksm(int x, int y, int ret = 1) {
	while(y) {
		if(y&1) ret=1LL*ret*x%m;
		y>>=1; x=1LL*x*x%m;
	}
	return ret;
}
int main() {
	freopen("diff.in", "r", stdin);
	freopen("diff.out", "w", stdout);
	scanf("%d", &t);
	while(t--) {
		sum=0; to.clear();
		scanf("%d%d", &m, &n);
		int pd1 = 0, pd2 = 0;
		for(int i = 1; i <= n; ++i)
			scanf("%d", &a[i]), pd1 |= (a[i] == m), pd2 |= (a[i] == 0);
		sort(a+1, a+1+n);
		
		if(n == 1) {
			printf("%d %d\n", a[1], 0);
			continue;
		}
		if(n == 2) {
			if(a[2] == m) a[2]=0; 
			printf("%d %d\n", a[1], a[2]-a[1]);
			continue;
		}
		if(m == n && a[n] != m) {//特殊判断+1,且为环的情况 
			printf("%d %d\n", a[1], 1);
			continue;
		}
		if(m+1 == n) {
			printf("%d %d\n", a[1], 1);
			continue;
		}
		if(pd1 && pd2) {//有0,有m,在上面的时候没输出,那么就不行 
			puts("-1");
			continue;
		}
		for(int i = 1; i <= n; ++i)
			sum=(sum+a[i])%m, to[a[i]]=i;
		sum=1LL*sum*2%m*ksm(n, m-2)%m;
//		printf("%d\n", sum);
		
		int az = ksm(n-1, m-2), ans = 0;
		for(int i = 1; i <= n; ++i) {
			int o = (sum-a[i]+m)%m;
			if(to.find(o) == to.end()) {
				ans=-1;
				break;
			}
			c[i]=1LL*(o-a[i]+m)%m*az%m;
		}
		if(ans == -1) {
			puts("-1");
			continue;
		}
//		for(int i = 1; i <= n; ++i) 
//			printf("%d ", c[i]); putchar('\n');
		//现在就是链一样的情况,找到最左端,一直跳,看能不能满足 
		for(int i = 1; i <= n; ++i)
			vis[i]=0;
		int lll = 1;
		for(int i = 1; i <= n; ++i) {//暴力跳应该不会被卡吧? 
			int st = a[i], ooo = 1, gc = c[i];
			if((sum-st+m)%m == st || to.find((st-gc+m)%m) != to.end() || to.find((st+gc)%m) == to.end())
				continue;//找到最左端 
			ppp.push(i); vis[i]=1;
			while(1) {
				int nxt = (st+gc)%m;
				if(to.find(nxt) == to.end()) break;
//				if(a[i] == 727427844)
//				cout<<ooo<<" "<<nxt<<" "<<vis[to[nxt]]<<"?\n";
				if(vis[to[nxt]]) break;
				st=nxt, ++ooo, vis[to[nxt]]=1, ppp.push(to[nxt]);
			}
			while(!ppp.empty())
				vis[ppp.front()]=0, ppp.pop();
			if(ooo == n) {
				printf("%d %d\n", a[i], gc);
				lll=0;
				break;
			}
		}
		if(lll) {
			puts("-1");
			continue;
		}
	}
	return 0;
} 
