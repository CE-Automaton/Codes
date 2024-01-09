#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<bool> bitset;
typedef std::pair<valueType, valueType> ValuePair;
typedef std::vector<ValuePair> PairVector;
typedef std::string string;
typedef std::vector<string> StringVector;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        string S;

        std::cin >> S;

        valueType A = 0, B = 0;

        valueType pos = 1;

        while (pos < S.size() && S[pos] == '0')
            ++pos;

        for (valueType i = 0; i < pos; ++i)
            A = A * 10 + (S[i] - '0');

        for (valueType i = pos; i < S.size(); ++i)
            B = B * 10 + (S[i] - '0');

        if (A < B) {
            std::cout << A << ' ' << B << std::endl;
        } else {
            std::cout << -1 << std::endl;
        }
    }

    return 0;
}