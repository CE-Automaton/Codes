#include<cstdio>
namespace IO{
	const int ARR_SIZE=1<<20;
	#define gc() ((IO::si!=IO::ti||(IO::ti=(IO::si=IO::input)+fread(IO::input,1,IO::ARR_SIZE,stdin))),IO::si!=IO::ti?*(IO::si++):EOF)
	#define pc(ch) ((IO::o.so!=IO::o.to||(fwrite(IO::o.output,1,IO::ARR_SIZE,stdout),IO::o.so=IO::o.output)),*(IO::o.so++)=ch)
	char input[ARR_SIZE],*si=input,*ti=input;
	struct Output_Stream{
		char output[ARR_SIZE],*so=output,*to=output+ARR_SIZE;
		~Output_Stream(){
			if(so==output)return;
			fwrite(output,1,so-output,stdout);
			so=output;
		}
	}o;
	template<typename T>
	void read(T&num){
		int ch=gc();
		num=0;
		while(ch<48||ch>57)ch=gc();
		while(ch>=48&&ch<=57)num=(num<<3)+(num<<1)+(ch^48),ch=gc();
	}
	template<typename T>
	void write(T a){
		static int ch[50],cnt=0;
		if(a==0)pc('0');
		while(a)ch[++cnt]=a%10|48,a/=10;
		while(cnt)pc(ch[cnt--]);
	}
}
using IO::read;
using IO::write;
typedef long long ll;
const int maxn=100000,maxk=8,P=1000000007;
ll qpow(ll a,ll x){
	ll ans=1;
	for(;x;a=a*a%P,x>>=1)
		if(x&1)
			ans=ans*a%P;
	return ans;
}
inline void qmod(int&x){
	x>=P&&(x-=P);
}
int n,m,k,coef,a[maxn+1];
struct BIT{
	int tr[maxn+1];
	inline int lowbit(const int x){
		return x&-x;
	}
	void modify(int pos,const int val){
		for(;pos<=n;pos+=lowbit(pos))qmod(tr[pos]+=val);
	}
	void build(int*arr){
		for(int i=1;i<=n;i++)qmod(arr[i]+=arr[i-1]);
		for(int i=1;i<=n;i++)qmod(tr[i]=P+arr[i]-arr[i-lowbit(i)]);
		for(int i=n;i>=1;i--)qmod(arr[i]+=P-arr[i-1]);
	}
	int query(int pos){
		int ans=0;
		for(;pos;pos-=lowbit(pos))qmod(ans+=tr[pos]);
		return ans;
	}
}bit[maxk];
int poly[maxk];
int main(){
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	read(n),read(m),read(k);
	coef=1;
	for(int i=1;i<k;i++)coef=(ll)coef*i%P;
	coef=qpow(coef,P-2);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int t=0;t<k;t++){
		bit[t].build(a);
		for(int i=1;i<=n;i++)a[i]=(ll)a[i]*i%P;
	}
	for(int i=1,opt,x,y,ans;i<=m;i++){
		read(opt),read(x),read(y);
		if(opt==1)
			for(int t=0;t<k;t++){
				bit[t].modify(x,y);
				y=(ll)y*x%P;
			}
		else{
			poly[0]=1;
			for(int t=1;t<k;t++)poly[t]=0;
			for(int t=1;t<k;t++)
				for(int s=t-1;s>=0;s--){
					qmod(poly[s+1]+=P-poly[s]);
					poly[s]=(ll)poly[s]*(y+t)%P;
				}
			ans=0;
			for(int t=0;t<k;t++)ans=(ans+ll(P+bit[t].query(y)-bit[t].query(x-1))*poly[t])%P;
			write((ll)ans*coef%P),pc('\n');
		}
	}
	return 0;
}
