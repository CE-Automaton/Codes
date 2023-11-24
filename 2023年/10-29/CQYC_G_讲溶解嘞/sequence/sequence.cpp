#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e7+5;
int t, n, A, B, C, D, len1, len2, ans, tot, az[N];
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
inline void exgcd(int a, int b, int &x, int &y) {
	if(!b) { 
		x=1, y=0;
		return ;
	} 
	exgcd(b,a%b,y,x);
	y-=x*(a/b);
}

signed main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
    read(t);
	while(t--) {
		memset(az, 0, sizeof az);
		ans = 0;
	    read(n), read(A), read(B), read(C), read(D), ++n;
		int res = 1;
	    A%=C, B%=D;
	    if((A == 0 && B == 0) || (A == 1 && B == 1)) {
			write(n-1, '\n');
			continue;
		}
	    else 
			if(!A || !B) {
				write(0, '\n');
				continue;
			}
	    for(int i = 0; i <= C; ++i) {
	        if(!az[res]) 
				az[res] = i+1;
	        if(res == 1 && i) {
				len1 = i;
				break ;
			}
	        res=res*A%C;
	    }
	    res = 1 ;
	    for(int i = 0; i <= D; ++i) {
	        if(res == 1 && i) {
				len2 = i;
				break ;
			}
	        res=res*B%D;
	    }
	    int gd = __gcd(len1,len2), p = len1*len2/gd;
	    res = 1;
		int x, y, xx, yy;
		exgcd(len1, len2, xx, yy); 
	    if(len1*xx+len2*yy != gd)
			xx*=-1, yy*=-1;
	    for(int i = 0; i <= D; ++i) {
	        if(res == 1 && i) 
				break;
	        if(az[res]) {
	            int a = az[res], b=i+1;
				x=xx, y=yy;
	            if((b-a)%gd == 0) {
	                x*=(b-a)/gd;
					x=x*len1+a;
	                if(x <= 0)
						x+=(-x/p)*p; 
	                if(x <= 0)
						x+=p;
	                x%=p;
					x+=(x<=0)*p;
	                if(x <= n) 
						ans+=1+(n-x)/p;
	            }
	        }
	        res=res*B%D;
	    }
	    write(ans-1, '\n');
	}
    return 0 ;
}
