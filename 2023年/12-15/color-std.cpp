#include<algorithm>
#include<cstdio>
#define ll long long
#define MaxM 165
using namespace std;
const int mod=1000000007;
int m;
struct Matrix{
  int a[MaxM][MaxM];
  void I(){for (int i=1;i<=m;i++)a[i][i]=1;}
  void clear(){
    for (int i=1;i<=m;i++)
      for (int j=1;j<=m;j++)
        a[i][j]=0;
  }
};
Matrix operator * (const Matrix &A,const Matrix&B)
{
  Matrix C;C.clear();
  for (int i=1;i<=m;i++)
    for (int j=1;j<=m;j++)
      for (int k=1;k<=m;k++)
        C.a[i][k]=(C.a[i][k]+1ll*A.a[i][j]*B.a[j][k])%mod; 
  return C;
}
int buf[MaxM];
void mul(int *A,const Matrix &B)
{
  for (int i=1;i<=m;i++){buf[i]=A[i];A[i]=0;}
  for (int i=1;i<=m;i++)
    for (int j=1;j<=m;j++)
      A[j]=(A[j]+1ll*buf[i]*B.a[i][j])%mod;
}
// ±àºÅ 1~k+1 Îª g0[n-k] ~ g0[n] 
// ±àºÅ k+2~2k+2 Îª g1[n-k] ~ g1[n]
// ±àºÅ 2k+3 Îª g2[n-1]
int T,k,s[MaxM];
Matrix A[62];
void mul2(int *s,ll n){
  for (int i=0;i<60;i++)
    if (n>>i&1)mul(s,A[i]);
}
#define add(x,y) x=(x+y)%mod;
int main()
{
	scanf("%d%d",&T,&k);
  m=2*k+3;
  for (int i=1;i<=k;i++)A[0].a[i+1][i]=1;
  for (int i=k+2;i<=2*k+1;i++)A[0].a[i+1][i]=1;
  add(A[0].a[k+1][k+1],2);
  add(A[0].a[2][k+1],mod-1);
  add(A[0].a[k+2][k+1],1);
  add(A[0].a[2*k+2][2*k+2],2);
  add(A[0].a[k+2][2*k+2],mod-1);
  add(A[0].a[2][2*k+2],1);
  add(A[0].a[1][2*k+2],mod-1);
  add(A[0].a[2*k+2][2*k+3],1);
  add(A[0].a[2*k+3][2*k+3],1);
  for (int i=1;i<60;i++)A[i]=A[i-1]*A[i-1];
  while(T--){
    ll n;scanf("%lld",&n);
    for (int i=1;i<=m;i++)s[i]=0;s[k+1]=1;
    if (n<2*k+1){
      mul2(s,n-1);
      int sav=s[k+2];
      mul(s,A[0]);
      printf("%lld ",((long long)s[2*k+2]+mod-s[2*k+1]+2*sav)%mod);
    }else {
      mul2(s,n-2*k-1);int sav1=s[2*k+3];
      mul2(s,2*k);int sav2=s[k+2];
      mul(s,A[0]);
      printf("%lld ",((long long)s[2*k+2]+mod-s[2*k+1]+2*sav2+sav1)%mod);
    }
  }
  return 0;
}
