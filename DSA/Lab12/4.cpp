vector<int> computeLPSArray(const string& pattern) {
    int M = pattern.length();
    vector<int> lps(M, 0);
    int len = 0;
    int i = 1;

    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else { 
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> kmpSearch(const string& text, const string& pattern, vector<int>& lps) {
    int N = text.length();
    int M = pattern.length();
    
    if (M == 0 || N < M) return {};

    lps = computeLPSArray(pattern);
    
    vector<int> indices;
    int i = 0;
    int j = 0;

    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if (j == M) {
            indices.push_back(i - j);
            j = lps[j - 1];
        } 
        
        else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return indices;
}
