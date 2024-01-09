#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 100010;
const int mod = 1e9 + 7;

template<typename T> inline void read(T &x) {
    char ch = getchar(); x = 0;
    for (; ch < '0'; ch = getchar());
    for (; ch >= '0'; ch = getchar()) x = x * 10 + ch - '0';
}

int n, m, k;
int c[45][MAXN];

int mul(LL a, int b)
{
    return a * b >= mod ? a * b % mod : a * b;
}

int add(int a, int b)
{
    return a + b >= mod ? a + b - mod : a + b;
}

int qpow(int a, int b)
{
    int ans = 1;
    for(; b; b >>= 1){
        if(b & 1) ans = mul(ans, a);
        a = mul(a, a);
    }
    return ans;
}

int fac[MAXN], ni[MAXN];

void init()
{
    fac[0] = 1;
    for(int i = 1; i < MAXN; i ++)
        fac[i] = mul(fac[i - 1], i);
    ni[MAXN - 1] = qpow(fac[MAXN - 1], mod - 2);
    for(int i = MAXN - 1; i >= 1; i --)
        ni[i - 1] = mul(ni[i], i);
}

int comb(int a, int b)
{
    int ans = 1;
    if(a < 0){
        ans = mul(fac[b - a - 1], ni[b]);
        ans = mul(ans, ni[- a - 1]);
        if(b & 1) ans = mul(ans, mod - 1);
    }
    else{
        if(a < b) return 0;
        if(a == b) return 1;
        ans = mul(fac[a], ni[b]);
        ans = mul(ans, ni[a - b]);
    }
    return ans;
}

void upd(int p, int x, int y)
{
    for(int i = x; i <= n; i += i & -i)
        c[p][i] = add(c[p][i], mul(comb(k - x, k - p), y));
}

int ask(int p, int x)
{
    int ans = 0;
    for(int i = x; i; i -= i & -i) ans = add(ans, c[p][i]);
    return ans;
}

int main()
{
    init();
    read(n); read(m); read(k);
    k --;
    while(m --){
        int op; read(op);
        if(op == 0){
            int x, y; read(x); read(y);
            for(int i = 0; i <= k; i ++) upd(i, x, y);
        }
        else{
            int x; read(x);
            int ans = 0;
            for(int i = 0; i <= k; i ++)
                ans = add(ans, mul(comb(x, i), ask(i, x)));
            printf("%d\n", ans);
        }
    }
    return 0;
}
