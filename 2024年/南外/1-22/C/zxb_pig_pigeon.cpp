//期待2.9（） 
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
const int inf=0x3f3f3f3f;
int L[maxn],f[maxn][20],sum[maxn][20];
//开始学习notepad画图（） 
//f[i][j]表示从i出发走2^j步最远能走到哪里
//sum[i][j]表示f[i][j]~(i-1)范围内所有点到i的距离和
//fij         fi,j-1      i
//-|------------|---------|------
//              ----------> 
//              (  sij-1  )
// ------------->
// (sfij-1,j-1)
//    [fij,fij-1 -1]的点从fi,j-1到i需要另外计算 
//    距离为2^(j-1) 总共有fij-1-fij个 
int calc(int l,int x)
{
	if(L[x]<=l)
		return x-l;
	//初始化 先把x走到l[x]强制往左走一步  就可以避免出现对于lx≤i且x>i的x，也是能够到达的情况 
	//tot=1表示接下来所有点到初始x的距离都要加上1 
	int ans=x-L[x],tot=1;  
	x=L[x];
	
	//我认为以下这一段很想二进制拆分/分块的思想 把整的处理掉 散的单独处理 
	//枚举i表示前进2^i 
	for(int i=19;i>=0;i--)
	{
		if(f[x][i]>l)
		{
			//[fxi,x-1]到x的距离就是sum[x][i] 离初始的x还要加上tot 共有x-fxi个点，所以加上tot*(x-fxi)
			//然后更新x  并更新tot 
			ans+=sum[x][i]+(x-f[x][i])*tot;
			x=f[x][i];
			tot+=(1<<i);
		}
	}
	//最后剩余的一些到x的距离 
	return ans+(x-l)*(tot+1);  
}
int main()
{
	int n;
	scanf("%d",&n);
	L[1]=1;
	for(int i=2;i<=n;i++)
		scanf("%d",&L[i]);
	f[n+1][0]=inf;
	for(int i=n;i>=1;i--)
	{ 
		f[i][0]=min(f[i+1][0],L[i]);
		sum[i][0]=i-f[i][0];
	}
	for(int j=1;j<=19;j++)
	{
		for(int i=1;i<=n;i++)
		{
			if(f[i][j-1]!=0)
			{
				f[i][j]=f[f[i][j-1]][j-1];
				sum[i][j]=sum[i][j-1]+sum[f[i][j-1]][j-1]+((f[i][j-1]-f[i][j])<<(j-1));
			}
		}
	}
	int q;
	cin>>q;
	while(q--)
	{
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		int fz=calc(l,x)-calc(r+1,x);
		int fm=r-l+1;
		int gcd=__gcd(fz,fm);
		fz/=gcd;fm/=gcd;
		printf("%d/%d\n",fz,fm);
	}
	return 0;
}
//反思 考场的时候想到了设fij表示从i出发走j步到达最远的点 预计70pts 但是写挂了（） 
//但是没有想到 在已确定当前能到达的编号最小的点的情况下，下一步能到达的编号最小的点是唯一确定的 所以没有想出倍增 
