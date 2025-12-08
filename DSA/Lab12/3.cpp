void preprocessBadChar(const string& pattern, vector<int>& badCharTable) {
    int M = pattern.length();

    badCharTable.assign(256, M); 

    
    for (int i = 0; i < M - 1; i++) {
        badCharTable[pattern[i]] = M - 1 - i; 
    }
}

void preprocessGoodSuffix(const string& pattern, vector<int>& suffix, vector<int>& goodSuffixTable) {
    int M = pattern.length();
    suffix.assign(M, 0);
    goodSuffixTable.assign(M, 0);

    int f = 0, g = 0;
    for (int i = M - 2; i >= 0; --i) {
        if (i > g && suffix[i + M - 1 - f] < i - g) {
            suffix[i] = suffix[i + M - 1 - f];
        } else {
            if (i < g) g = i;
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + M - 1 - f]) --g;
            suffix[i] = f - g;
        }
    }

    for (int i = 0; i < M; ++i) {
        goodSuffixTable[i] = M;
    }
    for (int i = M - 1; i >= 0; --i) {
        if (suffix[i] == i + 1) {
            for (int j = 0; j < M - 1 - i; ++j) {
                if (goodSuffixTable[j] == M) {
                    goodSuffixTable[j] = M - 1 - i;
                }
            }
        }
    }

    for (int i = 0; i < M - 1; ++i) {
        goodSuffixTable[M - 1 - suffix[i]] = M - 1 - i;
    }
}


vector<int> boyerMooreSearch(const string& text, const string& pattern) {
    int N = text.length();
    int M = pattern.length();
    vector<int> indices;
    
    if (M == 0 || N < M) return indices;

    vector<int> badCharTable;
    preprocessBadChar(pattern, badCharTable);

    
    int s = 0;
    while (s <= (N - M)) {
        int j = M - 1;

        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            indices.push_back(s);
            
            s += (s + M < N) ? badCharTable[text[s + M]] : 1; 
            
        } else {
            int shift = badCharTable[text[s + j]]; 
            s += max(1, shift);
        }
    }
    
    return indices;
}
