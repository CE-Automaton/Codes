#include <bits/stdc++.h>
#define io cin
using namespace std;
int n, ttt, r, ans = 2000000007;
struct ooo {
	int a, b;
}a[10000007], b[10000007];
multiset<int> sss;
//struct ios{
//   inline char gc(){
//       static const int IN_LEN=1<<18|1;
//       static char buf[IN_LEN],*s,*t;
//       return (s==t)&&(t=(s=buf)+fread(buf,1,IN_LEN,stdin)),s==t?-1:*s++;
//   }
//   template <typename _Tp> inline ios & operator >> (_Tp&x){
//       static char ch,sgn; ch = gc(), sgn = 0;
//       for(;!isdigit(ch);ch=gc()){if(ch==-1)return *this;sgn|=ch=='-';}
//       for(x=0;isdigit(ch);ch=gc())x=x*10+(ch^'0');
//       sgn&&(x=-x); return *this;
//   }
//}io;
inline int comp(ooo A, ooo B) { return ((A.a == B.a) ? (A.b < B.b) : (A.a > B.a)); }
signed main() {
//	freopen("after.in", "r", stdin);
//	freopen("after.out", "w", stdout);
	io>>n;
	for(int i = 1; i <= n; ++i)
		io>>a[i].a>>a[i].b;
	sort(a+1, a+1+n, comp);
	for(int i = 1; i <= n; ++i)
		b[i]=ooo{a[i].b, i};
	sort(b+1, b+1+n, [](ooo A, ooo B){
		return A.a < B.a;
	});
	r=n;
	for(int i = 1; i < n; ++i) {
		while(r && (b[r].b <= i || b[r].a >= a[i].a)) --r;
		if(b[r+1].b > i)
			ans=min(ans, abs(a[i].a-max(b[r+1].a, ttt)));
		if(r)
			ans=min(ans, abs(a[i].a-max(b[r].a, ttt)));
		ttt=max(ttt, a[i].b);
	}
	ans=min(ans, abs(a[n].a-ttt));
	printf("%d\n", ans);
	return 0;
}
