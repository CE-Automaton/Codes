#include <bits/stdc++.h>
//#define mod 1000000007 or 998244353//Ҫȡģ�� 
//#define inf 1000000007//��ֵ������ 
//#define int long long//Ҫ��long long�� 
using namespace std;
//��Ŀ��������,�ռ��г���,���鿪�Ĺ�����,�±���Ǹ�����,operator������� 
template <typename T> 
inline void read(T& x) {
	x=0; int f=1; char c=getchar(); while(c<'0' || c>'9') f=(c == '-' ? -1 : f), c=getchar();
	while('0'<=c && c<='9') x=(x<<1)+(x<<3)+(c^48), c=getchar(); x=x*f;
}
char ot[32]; int ln;
template <typename T> 
inline void write(T x) {
	ln=0; if(x < 0) x=-x, putchar('-');
	do { ot[++ln]=x%10, x/=10; }while(x);
	while(ln) putchar(ot[ln]+'0'), --ln; putchar('\n');
}
//int upd(int x) { return (x >= mod ? x-mod :x); }//�ӷ��ж���upd��,������+mod��,��һ������,�˷���*1LL%mod�� 
signed main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	
	return 0;
}
