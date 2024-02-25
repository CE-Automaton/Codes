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
		f[0][1]=R(l); // dp ��ʼ״̬
		for (int i{l+1};i<r;++i) {
			LL g[3][2];
			for (int i:{0,1,2})
				for (int j:{0,1}) g[i][j]=inf;
			for (int c:{0,1,2})
				for (int a:{0,1}) {
					int b{(c&1)^a}; // �ϵ���µ��Ƿ񸲸�������
					for (int x:{0,1})
					for (int y:{0,1}) { // �����������Ƿ����
						if (a&&x||b&&y) continue; // ������Ѿ����������εĵ��ٸ���
						int nc{c+(!a&&!x)+(!b&&!y)};
						if (nc<=2) { // c���벻����2��������Ҫ��
							g[nc][x]=min(g[nc][x],f[c][a]+x*U(i)+y*D(i)); // ��ǰ�����ұ߲�ѡ
							g[nc][!x]=min(g[nc][!x],f[c][a]+x*U(i)+y*D(i)+R(i)); // ��ǰ�����ұ�ѡ
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
					ans=min(ans,f[c][a]); // �������һ�е�δ���������εĵ㲻����2��������Ҫ��
			}
		for (int i{l};i<=r;++i) ans+=(h[i]+w[i])*2;
		for (int i{l};i<r;++i) ans-=R(i); // ��ʼ���б߼�һ��
		cout<<ans<<"\n";
	}
	return 0;
}
