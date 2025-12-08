struct RKResult {
    vector<int> indices;
    vector<int> falsePositives;
};

RKResult rabinKarpSearch(const string& text, const string& pattern) {
    RKResult result;
    int N = text.length();
    int M = pattern.length();
    
    if (M == 0 || N < M) return result;

    const int Q = 101;
    const int R = 256;

    
    long long h = 1;
    for (int i = 0; i < M - 1; i++) {
        h = (h * R) % Q;
    }

    long long pHash = 0;
    long long tHash = 0;

    
    for (int i = 0; i < M; i++) {
        pHash = (R * pHash + text[i]) % Q;
        tHash = (R * tHash + pattern[i]) % Q;
    }
    
    
    for (int i = 0; i <= N - M; i++) {
        if (pHash == tHash) {
            
            if (text.substr(i, M) == pattern) {
                result.indices.push_back(i);
            } else {
                
                result.falsePositives.push_back(i);
            }
        }

        if (i < N - M) {
            
            tHash = (R * (tHash - text[i] * h) + text[i + M]) % Q;
            
            
            if (tHash < 0) {
                tHash = (tHash + Q);
            }
        }
    }
    return result;
}
