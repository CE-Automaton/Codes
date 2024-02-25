#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define debug(x) cerr<<#x<<" "<<x<<endl
const int N = 2e5 + 10;

int n, m, l[N] , A ,B;
vector<int> G[N];
bool in[N];
int d[N],F[N],tmp[N];
const int inf = 1e9+1;
queue<int> Q;
priority_queue<pair<int,int> >q;
void qr(int &x) {scanf("%d",&x);}
inline int dd(int x)
{
	return (x<0)?0:x/(A-B)+1;
}
void ext(int x)
{
	for(int y:G[x])if(!in[y])
	{
		in[y] = 1;
		q.push({-d[y],y});
	}
}
int main() {
	freopen("easy.in", "r", stdin);
	freopen("easy.out", "w", stdout); 
	int T = 1;
	scanf("%d",&T);
	map<pair<int,int>,int>mp;
	while(T--) {
		scanf("%d%d%d%d",&n,&m,&A,&B);
//		debug((A>B));
		mp.clear();
		for(int i=1,x,y;i<=m;i++)
		{
			scanf("%d%d",&x,&y),G[x].push_back(y),G[y].push_back(x);
			if(mp.find({x,y})!=mp.end()) return -1;
			mp[{x,y}]=mp[{y,x}]=1;
		}
		for(int i=1;i<=n;i++)qr(l[i]);
		if(A>B)
		{
			for(int i=1;i<=n;i++)d[i] = dd(l[i]+B-l[1]);
			int s = 1;F[1] = 0;ext(1);in[1]=1;
			for(int t=1;t<=n;t++)
			{
				int cnt = 0;
				while(q.size() && -q.top().first <= min(s-1,t-1) )
				{
					int u = q.top().second;q.pop();
//					debug(u);
					tmp[++cnt] = u;
					F[u] = t;
				}				
				for(int i=1;i<=cnt;i++)ext(tmp[i]),++s;
			}
			while(!q.empty())q.pop();
			if(!F[n]) printf("-1\n");
			else printf("%d\n",F[n]);
			for(int i=1;i<=n;i++)F[i] = in[i] = 0,G[i].clear();
		}
		else 
		{
			Q.push(1);
			F[1] = 0;
			for(int i=2;i<=n;i++)l[i]+=B;
			while(!Q.empty())
			{
				int u = Q.front();Q.pop();
				for(int v:G[u])
					if(!F[v] && 1ll*F[u]*A+l[1] > 1ll*F[u]*B+l[v] && v>1) 
						F[v]  = F[u] + 1 , Q.push(v);
			}
			if(!F[n])printf("-1\n");
			else printf("%d\n",F[n]);
			for(int i=1;i<=n;i++)G[i].clear(),F[i]=0;
		}
	
	}
	return 0;
}

/*
1
5 4 10 5
1 2
1 3
1 4
4 5
10 4 4 4 19

*/
