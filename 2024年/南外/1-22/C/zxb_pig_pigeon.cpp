//�ڴ�2.9���� 
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
const int inf=0x3f3f3f3f;
int L[maxn],f[maxn][20],sum[maxn][20];
//��ʼѧϰnotepad��ͼ���� 
//f[i][j]��ʾ��i������2^j����Զ���ߵ�����
//sum[i][j]��ʾf[i][j]~(i-1)��Χ�����е㵽i�ľ����
//fij         fi,j-1      i
//-|------------|---------|------
//              ----------> 
//              (  sij-1  )
// ------------->
// (sfij-1,j-1)
//    [fij,fij-1 -1]�ĵ��fi,j-1��i��Ҫ������� 
//    ����Ϊ2^(j-1) �ܹ���fij-1-fij�� 
int calc(int l,int x)
{
	if(L[x]<=l)
		return x-l;
	//��ʼ�� �Ȱ�x�ߵ�l[x]ǿ��������һ��  �Ϳ��Ա�����ֶ���lx��i��x>i��x��Ҳ���ܹ��������� 
	//tot=1��ʾ���������е㵽��ʼx�ľ��붼Ҫ����1 
	int ans=x-L[x],tot=1;  
	x=L[x];
	
	//����Ϊ������һ�κ�������Ʋ��/�ֿ��˼�� �����Ĵ���� ɢ�ĵ������� 
	//ö��i��ʾǰ��2^i 
	for(int i=19;i>=0;i--)
	{
		if(f[x][i]>l)
		{
			//[fxi,x-1]��x�ľ������sum[x][i] ���ʼ��x��Ҫ����tot ����x-fxi���㣬���Լ���tot*(x-fxi)
			//Ȼ�����x  ������tot 
			ans+=sum[x][i]+(x-f[x][i])*tot;
			x=f[x][i];
			tot+=(1<<i);
		}
	}
	//���ʣ���һЩ��x�ľ��� 
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
//��˼ ������ʱ���뵽����fij��ʾ��i������j��������Զ�ĵ� Ԥ��70pts ����д���ˣ��� 
//����û���뵽 ����ȷ����ǰ�ܵ���ı����С�ĵ������£���һ���ܵ���ı����С�ĵ���Ψһȷ���� ����û��������� 
