#include<bits/stdc++.h>
struct ios{
    inline char gc(){
        static const int IN_LEN=1<<18|1;
        static char buf[IN_LEN],*s,*t;
        return (s==t)&&(t=(s=buf)+fread(buf,1,IN_LEN,stdin)),s==t?-1:*s++;
    }
    template <typename _Tp> inline ios & operator >> (_Tp&x){
        static char ch,sgn; ch = gc(), sgn = 0;
        for(;!isdigit(ch);ch=gc()){if(ch==-1)return *this;sgn|=ch=='-';}
        for(x=0;isdigit(ch);ch=gc())x=x*10+(ch^'0');
        sgn&&(x=-x); return *this;
    }
}io;
#define cin io
using namespace std;
const int mod = 1000000007;
long long qmi(long long a,int b)
{
	long long res = 1;
	while(b)
	{
		if(b & 1) (res *= a) %= mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return res;
}
long long fac[110011],exfac[110011];
int s[11][100011],a[100011];
int k,m,n;
const int N = 110000;
void Init()
{
	fac[0] = 1;
	for(int i = 1;i <= N;i++)
		fac[i] = fac[i - 1] * i % mod;
	exfac[N] = qmi(fac[N],mod - 2);
	for(int i = N;i;i--)
		exfac[i - 1] = exfac[i] * i % mod;
}
long long C(int n,int m)
{
	return fac[n] * exfac[m] % mod * exfac[n - m] % mod;
}
void Clac()
{
	for(int i = 1;i <= n;i++)
		s[0][i] = a[i];
	for(int K = 1;K <= k;K++)
		for(int i = 1;i <= n;i++)
			s[K][i] = (s[K - 1][i] + s[K][i - 1]) % mod;
}
int pl[100011],x[100011],lst,idx;
int srt = 888;
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	Init();
	cin >> n >> m >> k;
	for(int i = 1;i <= n;i++)
		cin >> a[i];
	Clac();
	for(int t = 1;t <= m;t++)
	{
		int opt;
		cin >> opt;
		if(opt == 1)
		{
			idx++;
			cin >> pl[idx] >> x[idx];
			(a[pl[idx]] += x[idx]) %= mod;
		}else{
			int l,r;
			cin >> l >> r;
			long long res = s[k][r];
			for(int i = 1;i <= k;i++)
				res += mod - s[i][l - 1] * C(r - l + k - i,r - l) % mod;
			res %= mod;
			for(int i = lst + 1;i <= idx;i++) if(l <= pl[i] && pl[i] <= r)
				(res += x[i] * C(r - pl[i] + k - 1,k - 1)) %= mod;
			printf("%lld\n",res);
		}
		if(idx - lst >= srt)
			lst = idx,Clac();
	}
	return 0;
}
