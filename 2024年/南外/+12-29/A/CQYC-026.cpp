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
int n,m,a[500011];
int f[500011],tag[1011],mn[1011];
int s[1011][11];
int nans;
typedef struct{
	int x,id;
}AD;
AD val[1011][1011];
int top[1011];
int lk[1011],rk[1011],idx,srt;
int L,R;
void Split(int k)
{
	for(int i = 1;i <= top[k];i++)
		val[k][i].x -= tag[k];
	tag[k] = 0;
}
void Merge(int k)
{
	mn[k] = INT_MAX;
	for(int i = 1;i <= top[k];i++)
		mn[k] = min(mn[k],val[k][i].x);
	for(int i = 0;i <= m;i++)
		s[k][i] = 0;
	for(int i = 1;i <= top[k];i++)
		if(val[k][i].x - mn[k] <= m)
			s[k][val[k][i].x - mn[k]]++;
	for(int i = 1;i <= m;i++)
		s[k][i] += s[k][i - 1];
}
void addr(int x)
{
	int k = x / srt;
	for(int i = 0;i < k;i++)
		tag[i]--;
	if(x == rk[k])
		return tag[k]--,void();
	for(int i = 1;val[k][i].id <= x;i++)
		val[k][i].x++;
}
void addcnt(int x)
{
	int k = x / srt;
	for(int i = 0;i < k;i++)
		tag[i]++;
	if(x == rk[k])
		return tag[k]++,void();
	if(k < L || R == rk[L])
		Split(k);
	for(int i = 1;val[k][i].id <= x;i++)
		val[k][i].x--;
	if(k < L || R == rk[L])
		Merge(k);
}
void Calc()
{
	nans = 0;
	for(int i = 0;i < L;i++) if(m + tag[i] - mn[i] >= 0)
			nans += s[i][min(m + tag[i] - mn[i],m)];
	if(rk[L] == R)
		nans += s[L][min(m + tag[L] - mn[L],m)];
	else
		for(int i = 1;val[L][i].id <= R;i++) if(val[L][i].x <= m)
			nans++;
}
double srtf;
vector<int> v[500011];
int x,y;
long long ans;
int main()
{
	freopen("shovel.in","r",stdin);
	freopen("shovel.out","w",stdout);
	cin >> n >> m;
	srtf = sqrt(n);
	srt = srtf;
	if(srt < srtf)
		srt++;
	idx = -1;
	for(int l = 0,r;l < n;l = r + 1)
	{
		r = l + srt - 1;
		if(r >= n)
			r = n - 1;
		idx++,lk[idx] = l,rk[idx] = r;
		for(int j = l;j <= r;j++)
			val[idx][++top[idx]].id = j;
	}
	for(int i = 0;i < n;i++)
		cin >> a[i],a[i]--;
	for(int i = 1;i < n;i++)
	{
		cin >> x >> y;
		x--,y--;
		int l = a[x],r = a[y];
		if(l > r)
			swap(l,r);
		v[r].push_back(l);
	}
	for(int r = 0;r < n;r++)
	{
		R = r;
		L = r / srt;
		if(R == rk[L])
			Merge(L);
		addr(r);
		for(auto l:v[r])
			addcnt(l);
		Calc();
		ans += nans;
	}
	printf("%lld",ans);
	return 0;
}
