#include <stdio.h>
#include <string.h>
const char pattern[][7] = { "a",      "ab",     "abc",    "aabbc",  "aabcc", "abacc",
                            "abbac",  "abbca",  "abbcc",  "abcba",  "abcca", "abccb",
                            "aabbcc", "aabccb", "abbacc", "abbcca", "abccba" };
const int len[] = { 1, 2, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6 },
          hub[][3] = { { 0, 1, 2 }, { 0, 2, 1 }, { 1, 0, 2 }, { 1, 2, 0 }, { 2, 0, 1 }, { 2, 1, 0 } };
char s[100005];
int next[100005][3], *last = next[0];
void work() {
    register int n, i, j, k, t, cnt;
    register long long ans = 0, now;
    !scanf("%d%s", &n, s + 1);
    last[0] = last[1] = last[2] = n + 1;
    for (i = n; i >= 1; --i) {
        memcpy(next[i], last, 3 * sizeof(int));
        last[s[i] - 'a'] = i;
    }
    for (t = 0; t < 6; ++t) {
        for (i = 0; i < 17; ++i) {
            register const char *P = pattern[i];
            j = k = cnt = 0;
            while (1) {
                k = next[k][hub[t][P[j] - 'a']];
                if (k > n)
                    break;
                if (++j == len[i])
                    j = 0, ++cnt;
            }
            now = (long long)cnt * cnt * len[i];
            if (now > ans)
                ans = now;
        }
    }
    printf("%lld\n", ans);
}
int main() {
    freopen("city.in", "r", stdin);
    freopen("city.out", "w", stdout);
    register int t;
    !scanf("%d", &t);
    while (t--) work();
    return 0;
}
