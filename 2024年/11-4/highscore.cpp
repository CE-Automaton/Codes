#include <bits/stdc++.h>
#define inf 1000000000000000007LL
#define File(xxx) freopen(xxx".in","r",stdin),freopen(xxx".out","w",stdout)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pii;
int sub, t, n;
LL a, k, b;
set<pii> qwq;

template <typename T> inline void debug(T x) { cerr<<x; }
template <typename T, typename ...T_> inline void debug(T x, T_ ...p) { cerr<<x<<' ', debug(p...); }
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

signed main() {
	File("highscore");
	read(sub);
	read(t);
	while(t--) {
		read(n);
		qwq.clear();
		k=1, b=0;
		int ans = 0;
		for(int i = 1; i <= n; ++i) {
			read(a);
			// debug(a, ":\n");
			// for(auto it : qwq)
			// 	debug(it.first*k+b, '-', it.second*k+b), debug("   ");
			// debug('\n');
			//先和{1,a-1}取交：
			if(k == 1) {
				auto it = qwq.lower_bound(pii {a-b, -inf});
				qwq.erase(it, qwq.end());
				if(!qwq.empty()) {
					pii op = *qwq.rbegin();
					if(op.second+b >= a) {
						qwq.erase(op);
						op.second=a-b-1;
						if(op.first > op.second) debug(op.first+b, op.second+b, a, b, "???\n");
						qwq.insert(op);
					}
				}
			}
			else {
				while(!qwq.empty()) {
					auto it = qwq.begin();
					if(b-(*it).second >= a)
						qwq.erase(it);
					else {
						pii op = (*it);
						if(b-op.first >= a) {
							qwq.erase(op);
							op.first=b-a+1;
							if(op.first > op.second) debug("???\n");
							qwq.insert(op);
						}
						break;
					}
				}
			}
			if(a&1) {
				if(!qwq.empty())
					++ans, k=-k, b=a-b/*, debug("opt1\n")*/;
				else
					ans+=2, qwq.clear(), qwq.insert(pii {1, a-1}), k=1, b=0/*, debug("opt2\n")*/;
			}
			else {
				LL tt = (a/2-b)/k;
				auto it = qwq.upper_bound(pii {tt+1, -inf});
				if(it != qwq.begin()) {
					--it;
					if(tt <= (*it).second) { 
						qwq.clear();
						qwq.insert(pii {a/2, a/2});
						k=1, b=0;
						// debug("opt3\n");
						continue;
					}
				}
				k=-k, b=a-b;
				tt=(a/2-b)/k;
				qwq.insert(pii {tt, tt});
				++ans;
				// debug("opt4\n");
			}
		}
		write(ans, '\n');
	}
	return 0;
}