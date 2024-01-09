#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 1e7+5, K = 5e3+5;
int n, p[K], pri[N], cnt, vis[N], len[K], sum[K], dp[K][K], k;

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
int gs(int x) {
	return (x%2 == 0 ? 2 : (!vis[x] ? 1 : 3));
}

signed main() {
	freopen("crazy.in", "r", stdin);
	freopen("crazy.out", "w", stdout);
	vis[1]=1;
	for(int i = 2; i <= 10000000; ++i) {
		if(vis[i] == 0) 
			pri[++cnt]=i;
		for(int j = 1; j <= cnt && 1LL*i*pri[j] <= 10000000; ++j) {
			vis[i*pri[j]]=1;
			if(i%pri[j] == 0) break;
		}
	}
	read(n);
	for(int i = 1; i <= n; ++i)
		read(p[i]);
	sort(p+1, p+1+n);
	for(int i = 1; i <= n; ++i) {
		if(i == 1 || p[i] != p[i-1]+1) {
			if(i != 1)
				len[++k]=p[i]-p[i-1]-1;
			len[++k]=1;
		}
		else 
			++len[k];
	}
//	cout<<k<<":\n";
//	for(int i = 1; i <= k; ++i)
//		write(len[i], ' ');
//	puts("");
	for(int i = 1; i <= k; ++i)
		dp[i][i]=gs(len[i]), sum[i]=sum[i-1]+len[i];
	for(int len = 3; len <= k; len+=2)
		for(int i = 1, j = len; j <= k; ++i, ++j) {
			dp[i][j]=inf;
			for(int o = i; o+2 <= j; o+=2)
				dp[i][j]=min(dp[i][j], dp[i][o]+dp[o+2][j]);
			dp[i][j]=min(dp[i][j], gs(sum[j]-sum[i-1])+dp[i+1][j-1])/*ȫ���������м�ļ�϶*/;
//			cout<<i<<" "<<j<<" "<<dp[i][j]<<'\n';
		} 
	write(dp[1][k], '\n');
	return 0;
}
/*
��2��4��ż�������Ա�ʾΪ������������� (��°ͺղ���?)
2��4���ܱ�ʾΪһ������������һ�������� 
�������޷���ʾΪ������������ӻ�һ������������һ��������
����: 
ż�����ȵ����������۾�Ϊ2
���������ȵ�����������Ϊ1
�������������ȵ�����������Ϊ3 

ϣ��dp�ܹ�,���챣��\|/ 
    			   [_] 
*/
