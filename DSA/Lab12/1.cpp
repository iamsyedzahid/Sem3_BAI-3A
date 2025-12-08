struct SearchResult {
    vector<int> indices;
    int totalComparisons = 0;
};

SearchResult bruteForceSearch(const string& text, const string& pattern) {
    SearchResult result;
    int N = text.length();
    int M = pattern.length();
    
    if (M == 0) return result;

    for (int i = 0; i <= N - M; i++) {
        int j = 0;
        
        while (j < M) {
            result.totalComparisons++;
            if (text[i + j] != pattern[j]) {
                break;
            }
            j++;
        }
        
        if (j == M) {
            result.indices.push_back(i);
        }
    }
    return result;
}
