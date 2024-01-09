#include <bits/stdc++.h>
using namespace std;

const int Maxn = 1000005;
int n, m, cnt, deg[Maxn], head[Maxn], e[Maxn];
bool vis[Maxn][2];
queue <int> Qu;
struct edg
{
	int nxt, to;
	bool dir;
} edge[4 * Maxn];
void add(int x, int y)
{
	edge[++cnt] = (edg){head[x], y};
	head[x] = cnt;
	deg[x]++;
}
void dfs(int u)
{
	for (int & i = head[u]; i; i = edge[i].nxt)
	{
		int to = edge[i].to;
		if (!edge[i].dir && !edge[((i - 1) ^ 1) + 1].dir)
		{
			deg[u]--, deg[to]--;
			vis[u][1] = vis[to][0] = false;
			edge[i].dir = true;
			dfs(to);
		}
	}
}
void End(void)
{
	puts("-1");
	exit(0);
}
void read(int &x)
{
	x = 0;
	char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
}
int main()
{
	freopen("degree.in", "r", stdin);
	freopen("degree.out", "w", stdout);
	read(n), read(m);
	for (int i = 1, x; i <= n; i++) read(x), vis[i][0] = x;
	for (int i = 1, x; i <= n; i++) read(x), vis[i][1] = x;
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		read(x), read(y);
		add(x, y), e[i] = cnt, add(y, x);
	}
	for (int i = 1; i <= n; i++)
		if (deg[i] == 1 && (vis[i][0] || vis[i][1])) Qu.push(i);
	while (!Qu.empty())
	{
		int u = Qu.front();
		Qu.pop();
		if (vis[u][0] && vis[u][1]) End();
		for (int i = head[u]; i; i = edge[i].nxt)
		{
			int to = edge[i].to;
			if (!edge[i].dir && !edge[((i - 1) ^ 1) + 1].dir)
			{
				if (vis[u][1])
					vis[u][1] = vis[to][0] = false, edge[i].dir = 1;
				else
					vis[u][0] = vis[to][1] = false, edge[((i - 1) ^ 1) + 1].dir = 1;
				deg[u]--, deg[to]--;
				if (deg[to] == 1 && (vis[to][0] || vis[to][1])) Qu.push(to);
			}
		}
	}
	for (int i = 1; i <= n; i++)
		if (deg[i] & 1) add(0, i), add(i, 0);
	for (int i = 0; i <= n; i++)
		while (deg[i]) dfs(i);
	for (int i = 1; i <= n; i++)
		if (vis[i][0] || vis[i][1]) End();
	for (int i = 1; i <= m; i++)
		putchar(edge[e[i]].dir + '0'), putchar(" \n"[i == m]);
	return 0;
}
