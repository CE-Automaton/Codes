#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
const int N = 3e6+6;
int n, m, q, tre[N], tree[N], x, y;
set <int> s[N], t[N];
using u32 = unsigned;
struct IO_Tp {
    const static int _I_Buffer_Size = 30 << 21;
    char _I_Buffer[_I_Buffer_Size], *_I_pos = _I_Buffer;
    const static int _O_Buffer_Size = 8 << 21;
    char _O_Buffer[_O_Buffer_Size], *_O_pos = _O_Buffer;
    u32 m[10000];
    IO_Tp() {
         freopen("tmp.in","r",stdin);
         freopen("tmp.out","w",stdout);
        constexpr u32 e0 = '\0\0\0\1', e1 = '\0\0\1\0', e2 = '\0\1\0\0', e3 = '\1\0\0\0';
        int x = 0;
        for (u32 i = 0, c0 = '0000'; i != 10; ++i, c0 += e0)
            for (u32 j = 0, c1 = c0; j != 10; ++j, c1 += e1)
                for (u32 k = 0, c2 = c1; k != 10; ++k, c2 += e2)
                    for (u32 l = 0, c3 = c2; l != 10; ++l, c3 += e3) m[x++] = c3;
        fread(_I_Buffer, 1, _I_Buffer_Size, stdin);
    }
    ~IO_Tp() { fwrite(_O_Buffer, 1, _O_pos - _O_Buffer, stdout); }
    IO_Tp &operator>>(int &res) {
        while (!isdigit(*_I_pos)) ++_I_pos;
        res = *_I_pos++ - '0';
        while (isdigit(*_I_pos)) res = res * 10 + (*_I_pos++ - '0');
        return *this;
    }
} io;
inline int minn(int xx, int yy) {
	return (xx < yy ? xx : yy);
}
inline int maxn(int xx, int yy) {
	return (xx > yy ? xx : yy);
}
inline void add1(int xx, int y) {
	while(xx >= 1)
		tre[xx]=minn(tre[xx], y), xx=xx-(xx&(-xx));
}
inline int find1(int xx, int ret = inf) {
	while(xx >= 1 && xx <= m)
		ret=minn(ret, tre[xx]), xx=xx+(xx&(-xx));
	return ret;
}
inline void add2(int xx, int y) {
	while(xx >= 1 && xx <= m)
		tree[xx]=maxn(tree[xx], y), xx=xx+(xx&(-xx));
}
inline int find2(int xx, int ret = 0) {
	while(xx >= 1)
		ret=maxn(ret, tree[xx]), xx=xx-(xx&(-xx));
	return ret;
}
void cl1(int xx, int yy) {
	add1(yy+1, xx-1);
	t[xx].erase(yy);
	s[yy].erase(xx);
	auto it = s[yy+1].lower_bound(xx-1);
	if(it != s[yy+1].end() && (*it) <= find1(yy+2))
		cl1(*it, yy+1);
	it=t[xx-1].upper_bound(yy+1);
	if(it != t[xx-1].begin()) {
		--it;
		if(xx-1 <= find1((*it)+1))
			cl1(xx-1, *it);
	} 
}
void cl2(int xx, int yy) {
	add2(yy-1, xx+1);
	t[xx].erase(yy);
	s[yy].erase(xx);
	auto it = t[xx+1].lower_bound(yy-1);
	if(it != t[xx+1].end() && xx+1 <= find2(*it))
		cl2(xx+1, *it);
	it=s[yy-1].upper_bound(xx+1);
	if(it != s[yy-1].begin()) {
		--it;
		if((*it) >= find2(yy-2))
			cl2(*it, yy-1);
	} 
}
char solve(int xx, int yy) {
	int a = find1(yy), b = find1(yy+1), c = 0;
	c |= (a <= xx && xx <= b);
	a = find2(yy-1), b = find2(yy);
	c |= (a <= xx && xx <= b)*2;
	if(c == 3) 
		return '0';
	t[xx].insert(yy);
	s[yy].insert(xx);
	if(c&1) cl1(xx, yy);
	if(c&2) cl2(xx, yy);
	return '1';
}
int main() {
//	freopen("tmp.in", "r", stdin);
//	freopen("tmp.out", "w", stdout);
	io>>n>>m>>q;
	memset(tre, 0x3f, sizeof tre);
	add1(1, 1), add1(m, n);
	add2(1, 1), add2(m, n);
	for(int i = 1; i <= q; ++i)
		io>>x>>y, putchar(solve(x, y));
	return 0;
} 
