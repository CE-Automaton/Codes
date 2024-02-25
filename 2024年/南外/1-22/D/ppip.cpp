#include <bits/stdc++.h>
using namespace std;
using LL=long long;
constexpr LL N(1e5),inf(1e18);
int h[N+5],w[N+5];
int R(int i) {
	return min(h[i],h[i+1]);
}
int D(int i) {
	return w[i];
}
int U(int i) {
	return (h[i]+w[i])*2-R(i)-D(i)-R(i-1);
}
int main() {
	freopen("huffman.in","r",stdin);
	freopen("huffman.out","w",stdout);
	int n,q;cin>>n>>q;
	for (int i{1};i<=n;++i) cin>>h[i];
	for (int i{1};i<=n;++i) cin>>w[i];
	while (q--) {
		int l,r;cin>>l>>r;
		LL f[3][2];
		for (int i:{0,1,2})
			for (int j:{0,1}) f[i][j]=inf;
		f[0][0]=0;
		f[0][1]=R(l); // dp 初始状态
		for (int i{l+1};i<r;++i) {
			LL g[3][2];
			for (int i:{0,1,2})
				for (int j:{0,1}) g[i][j]=inf;
			for (int c:{0,1,2})
				for (int a:{0,1}) {
					int b{(c&1)^a}; // 上点和下点是否覆盖奇数次
					for (int x:{0,1})
					for (int y:{0,1}) { // 上下两条边是否添加
						if (a&&x||b&&y) continue; // 不会把已经覆盖奇数次的点再覆盖
						int nc{c+(!a&&!x)+(!b&&!y)};
						if (nc<=2) { // c必须不超过2否则不满足要求
							g[nc][x]=min(g[nc][x],f[c][a]+x*U(i)+y*D(i)); // 当前格子右边不选
							g[nc][!x]=min(g[nc][!x],f[c][a]+x*U(i)+y*D(i)+R(i)); // 当前格子右边选
						}
					}
				}
			memcpy(f,g,sizeof f);
		}
		LL ans{inf};
		for (int c:{0,1,2})
			for (int a:{0,1}) {
				int b{(c&1)^a};
				if (c+!a+!b<=2)
					ans=min(ans,f[c][a]); // 加上最后一列的未覆盖奇数次的点不超过2个才满足要求
			}
		for (int i{l};i<=r;++i) ans+=(h[i]+w[i])*2;
		for (int i{l};i<r;++i) ans-=R(i); // 初始所有边加一次
		cout<<ans<<"\n";
	}
	return 0;
}
