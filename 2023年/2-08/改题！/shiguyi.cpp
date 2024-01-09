#include <bits/stdc++.h> 
using namespace std;
int n, k, f[25][2100000], to[2100000][2], len[2000006];
char haha[2000006];
int main() {
	freopen("shiguyi.in", "r", stdin);
	freopen("shiguyi.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for(int i = 0; i <= n; ++i) {
		scanf("%s", haha);
		for(int j = 0; j < (1<<i); ++j) {
			if(haha[j] == '1') ++f[0][(1<<i)|j];
			for(int cl = 0; cl <= 1; ++cl) {
				int pd = 1;
				for(int k = i-1, o = j; k >= 0; --k) {
					o-=o&(1<<k);
					if(((j&(1<<k)) != 0) == cl) {
						to[(1<<i)|j][cl]=(1<<k)+o, pd=0;
						break;
					}
				}
				if(pd) to[(1<<i)|j][cl]=-1;
			}
		}
	}
	len[0]=0, len[1]=1;
	for(int i = 1; i <= (1<<(n-1)); ++i) len[(i<<1)]=len[i]+1;
//	for(int i = 1; i <= (1<<n)-1; ++i)妈的输出个to数组就要这么多行了,还调试你大爷呢? 
//		for(int j = n; j >= 0; --j) {
//			if((i>>j)&1) break;
//			if(f[0][(1<<j)+i] == 0) continue;
//			int qwq = to[(1<<j)+i][0];
//			for(int o = j-1; o >= 0; --o)
//				cout<<((i>>o)&1);cout<<": \n";
//			if(qwq == -1) cout<<"-1";
//			else for(int o = n-1; o >= 0; --o) {
//				if((qwq>>o)&1) {
//					for(int oo = o-1; oo >= 0; --oo)
//						cout<<((qwq>>oo)&1);break;
//				}
//			}cout<<"\n";
//			qwq = to[(1<<j)+i][1];
//			if(qwq == -1) cout<<"-1";
//			else for(int o = n-1; o >= 0; --o) {
//				if((qwq>>o)&1) {
//					for(int oo = o-1; oo >= 0; --oo)
//						cout<<((qwq>>oo)&1);break;
//				}
//			}cout<<"\n";
//		}
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j < (1<<i); ++j) 
			for(int k = 0; k <= n-i; ++k) 
				for(int l = 0; l < (1<<k); ++l) {
					int o = ((1<<k)|l), m=((o<<i)|j);
					for(int cl = 0; cl <= 1; ++cl) {
						if(to[o][cl] == -1) continue; 
						f[i+1][(((to[o][cl]<<i)|j)<<1)|cl]+=f[i][m];
					}
				}
//	for(int i = 0; i <= n; ++i)
//		for(int j = 0; j < (1<<i); ++j)
//			for(int k = 0; k <= n-i; ++k) 
//				for(int l = 0; l < (1<<k); ++l) {
//					for(int o = i-1; o >= 0; --o)
//						cout<<((j>>o)&1);cout<<" ";
//					for(int o = k-1; o >= 0; --o)
//						cout<<((l>>o)&1);cout<<" ";
//					int o = ((1<<k)|l), m=((o<<i)|j);
//					cout<<f[i][m]<<"\n";
//				}
	for(int i = n; i >= 0; --i)
		for(int j = 0; j < (1<<i); ++j) {
			int sum = 0;
			for(int k = 0; k <= n-i; ++k) 
				for(int l = 0; l < (1<<k); ++l)
					sum+=f[i][(((1<<k)|l)<<i)|j];
			if(sum >= k) {
				for(int o = i-1; o >= 0; --o)
					printf("%d", (j>>o)&1);
				return 0;
			}
		} 
	return 0;
}
