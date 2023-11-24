#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
int n, tot, zhan[75], haha, gs[75], pd[75][5];
long long a, b;

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
	freopen("island.in", "r", stdin);
	freopen("island.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) {
		read(a), read(b);
		haha = 0;
		while(a != 0) 
			gs[++haha]=a%2, a=(a-1)/2;
		gs[++haha]=0;
		while(b != 0)
			zhan[++tot]=b%2, b=(b-1)/2;
		while(tot)
			gs[++haha]=zhan[tot], --tot;
		for(int i = haha; i >= 1; --i) 
			pd[i][0]=pd[i][1]=pd[i][2]=pd[i][3]=pd[i][4]=inf;
		if(gs[1] == 1)
			pd[i][1]=pd[i][2]=pd[i][4]=1;
		if(gs[1] == 0)
			pd[i][0]=pd[i][2]=pd[i][3]=1;
		for(int i = 1; i <= haha; ++i) {
			for(int j = 0; j <= 4; ++j)	
				for(int k = 0; k <= 4; ++k)
					pd[i][j]=min(pd[i][j], pd[i][k]+1);
			int j = i;
			while(j+1 <= haha && gs[j+1] == gs[i])
				++j, pd[j][0]=min(pd[j][0], pd[i][0]);
			++j, pd[j][1]=min(pd[j][1], pd[i][0]);
			++j, pd[j][2]=min(pd[j][2], pd[i][0]);
			if(j+1 <= haha && gs[j+1] == gs[i]) {
				++j;
				pd[j][3]=min(pd[j][3], pd[i][0]);
				while(j+1 <= haha && gs[j+1] != gs[i])
					++j, pd[j][4]=min(pd[j][4], pd[i][0]);
			}
			
			j = i;
			++j, pd[j][2]=min(pd[j][2], pd[i][1]);
			if(j+1 <= haha && gs[j+1] == 0) {
				++j;
				pd[j][3]=min(pd[j][3], pd[i][1]);
				while(j+1 <= haha && gs[j+1] == gs[i])
					++j, pd[j][4]=min(pd[j][4], pd[i][1]);
			}
			
			j = i;
			if(j+1 <= haha && gs[j+1] == 0) {
				++j;
				pd[j][3]=min(pd[j][3], pd[i][2]);
				while(j+1 <= haha && gs[j+1] == 1)
					++j, pd[j][4]=min(pd[j][4], pd[i][2]);
			}
			
			j = i; 
			while(j+1 <= haha && gs[j+1] == 1)
				++j, pd[j][4]=min(pd[j][4], pd[i][4]);
		}
		write(min(pd[haha][0], min(pd[haha][1], min(pd[haha][2], min(pd[haha][3], pd[haha][4]))))-1, '\n');
	}
	return 0;
}
